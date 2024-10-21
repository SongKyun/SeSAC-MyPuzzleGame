// �÷��̾� �Է� �޾� ��� ����, ����� ����� ����� �ǵ�����(Undo) ��� ����

#include "APlayerController.h"
#include "Tile.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "SwapTilesCommand.h"
#include "TileCommandInvoker.h"

AAPlayerController::AAPlayerController()
{
	// ���� ������ Ÿ���� ���� (ó������ �ƹ� �͵� ���õ��� ���� ����)
	FirstSelectedTile = nullptr;
	SecondSelectedTile = nullptr;
}

void AAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ���콺 Ŀ�� ���̱� ����
	bShowMouseCursor = true;

	// Enhanced Input ����
	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		// Enhanced Input ���� �ý����� �߰��Ͽ� InputMappingContext�� Ȱ��ȭ
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
		// ���콺 Ŭ�� �Է� ���ε�
		EnhancedInputComp->BindAction(SelectTileAction, ETriggerEvent::Triggered, this, &AAPlayerController::SelectTile);
	}
}

void AAPlayerController::SelectTile(const FInputActionValue& Value)
{
	// ���콺 Ŭ�� ��ġ�� ������
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		ATile* ClickedTile = Cast<ATile>(Hit.GetActor());
		if (ClickedTile)
		{
			// ù ��° Ÿ���� �����ϴ� ���
			if (!FirstSelectedTile.IsValid())
			{
				// ù ��° Ÿ�� ����
				FirstSelectedTile = ClickedTile;
				FirstSelectedTile -> SetSelected(true); // ù ��° Ÿ�� ����
				UE_LOG(LogTemp, Warning, TEXT("First tile selected: %s"), *FirstSelectedTile->GetName());
			}
			// �� ��° Ÿ���� �����ϴ� ���
			else if (!SecondSelectedTile.IsValid() && ClickedTile != FirstSelectedTile)
			{
				// �� ��° Ÿ�� ����
				SecondSelectedTile = ClickedTile;
				SecondSelectedTile -> SetSelected(true);
				UE_LOG(LogTemp, Warning, TEXT("Second tile selected: %s"), *SecondSelectedTile->GetName());

				// �� Ÿ�� ���� �Ϸ� �� ó��
				ProcessSelectedTiles();
			}
		}
	}
}

void AAPlayerController::ProcessSelectedTiles()
{
	if (FirstSelectedTile.IsValid() && SecondSelectedTile.IsValid())
	{
		// �� ���� ���õ� Ÿ���� ó���ϴ� ����
		UE_LOG(LogTemp, Warning, TEXT("Processing thiles : %s and %s"), *FirstSelectedTile->GetName(), *SecondSelectedTile->GetName());

		// ��ȯ ��� ����
		USwapTilesCommand* SwapCommand = NewObject <USwapTilesCommand>();
		SwapCommand->Initialize(FirstSelectedTile.Get(), SecondSelectedTile.Get());

		//  Ŀ�ǵ� ����
		ATileCommandInvoker* CommandInvoker = GetWorld()->SpawnActor <ATileCommandInvoker>();
		CommandInvoker->ExecuteCommand(SwapCommand);

		// �� Ÿ���� ���� ����
		FirstSelectedTile->SetSelected(false);
		SecondSelectedTile->SetSelected(false);

		// Ÿ�� ó�� ���� (��ȯ, ��Ī Ȯ�� ��)

		// ���� �ʱ�ȭ
		FirstSelectedTile = nullptr;
		SecondSelectedTile = nullptr;
	}
}

