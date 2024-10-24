#include "PuzzleGameModeBase.h"
#include "MyGameInstance.h"
#include "TileGrid.h"
#include "Kismet/GameplayStatics.h"
#include "GameStateSubject.h"
#include "GameWidgetObserver.h"

void APuzzleGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 게임 인스턴스 초기화
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->ResetGameState(); // 게임 상태 초기화
	}

	// Observer 주체 생성
	UGameStateSubject* ObserverGameState = NewObject<UGameStateSubject>();

	// GameInstance에 Observer 주체 설정
	if (GameInstance)
	{
		GameInstance->SetGameStateSubject(ObserverGameState);
	}

	if (MainWidgetClass)
	{
		UGameWidgetObserver* ScoreWidget
			= CreateWidget<UGameWidgetObserver>(GetWorld(), MainWidgetClass);
		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
			// 위젯을 옵저버로 등록
			ObserverGameState->RegisterObserver(ScoreWidget);
		}
	}


	//// 타일 그리드 초기화
	//ATileGrid* TileGrid = GetWorld()->SpawnActor<ATileGrid>(ATileGrid::StaticClass());
	//if (TileGrid)
	//{
	//	TileGrid->InitializeGrid();
	//}

	////위젯 생성 및 화면에 표시
	//UGameWidgetObserver* ScoreWidget = CreateWidget<UGameWidgetObserver>(GetWorld(), LoadClass<UGameWidgetObserver>(nullptr, TEXT("/Game/UI/ScoreWidget")));

	//if (ScoreWidget)
	//{
	//	ScoreWidget->AddToViewport();

	//	// 위젯을 옵저버로 등록
	//	ObserverGameState->RegisterObserver(ScoreWidget);
	//}

	//// 5초마다 점수 증가
	//FTimerHandle TimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, [ObserverGameState]()
	//	{
	//		ObserverGameState->IncreaseScore(10);
	//	}, 5.0f, true);
}
