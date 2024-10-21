// 플레이어 입력 받아 명령 실행, 실행된 명령을 기록해 되돌리기(Undo) 기능 제공

#include "APlayerController.h"
#include "Tile.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "SwapTilesCommand.h"
#include "TileCommandInvoker.h"

AAPlayerController::AAPlayerController()
{
	// 약한 참조로 타일을 관리 (처음에는 아무 것도 선택되지 않은 상태)
	FirstSelectedTile = nullptr;
	SecondSelectedTile = nullptr;
}

void AAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 마우스 커서 보이기 설정
	bShowMouseCursor = true;

	// Enhanced Input 설정
	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		// Enhanced Input 하위 시스템을 추가하여 InputMappingContext를 활성화
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

void AAPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// 마우스 클릭 입력 바인딩
		EnhancedInputComp->BindAction(SelectTileAction, ETriggerEvent::Triggered, this, &AAPlayerController::SelectTile);
	}
}

void AAPlayerController::SelectTile(const FInputActionValue& Value)
{
	// 마우스 클릭 위치를 가져옴
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		ATile* ClickedTile = Cast<ATile>(Hit.GetActor());
		if (ClickedTile)
		{
			// 첫 번째 타일을 선택하는 경우
			if (!FirstSelectedTile.IsValid())
			{
				// 첫 번째 타일 선택
				FirstSelectedTile = ClickedTile;
				FirstSelectedTile -> SetSelected(true); // 첫 번째 타일 강조
				UE_LOG(LogTemp, Warning, TEXT("First tile selected: %s"), *FirstSelectedTile->GetName());
			}
			// 두 번째 타일을 선택하는 경우
			else if (!SecondSelectedTile.IsValid() && ClickedTile != FirstSelectedTile)
			{
				// 두 번째 타일 선택
				SecondSelectedTile = ClickedTile;
				SecondSelectedTile -> SetSelected(true);
				UE_LOG(LogTemp, Warning, TEXT("Second tile selected: %s"), *SecondSelectedTile->GetName());

				// 두 타일 선택 완료 후 처리
				ProcessSelectedTiles();
			}
		}
	}
}

void AAPlayerController::ProcessSelectedTiles()
{
	if (FirstSelectedTile.IsValid() && SecondSelectedTile.IsValid())
	{
		// 두 개의 선택된 타일을 처리하는 로직
		UE_LOG(LogTemp, Warning, TEXT("Processing thiles : %s and %s"), *FirstSelectedTile->GetName(), *SecondSelectedTile->GetName());

		// 교환 명령 생성
		USwapTilesCommand* SwapCommand = NewObject <USwapTilesCommand>();
		SwapCommand->Initialize(FirstSelectedTile.Get(), SecondSelectedTile.Get());

		//  커맨드 실행
		ATileCommandInvoker* CommandInvoker = GetWorld()->SpawnActor <ATileCommandInvoker>();
		CommandInvoker->ExecuteCommand(SwapCommand);

		// 두 타일의 선택 해제
		FirstSelectedTile->SetSelected(false);
		SecondSelectedTile->SetSelected(false);

		// 타일 처리 로직 (교환, 매칭 확인 등)

		// 선택 초기화
		FirstSelectedTile = nullptr;
		SecondSelectedTile = nullptr;
	}
}

