#include "PuzzleGameModeBase.h"
#include "MyGameInstance.h"
#include "TileGrid.h"
#include "Kismet/GameplayStatics.h"
#include "GameStateSubject.h"
#include "GameWidgetObserver.h"

void APuzzleGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// ���� �ν��Ͻ� �ʱ�ȭ
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->ResetGameState(); // ���� ���� �ʱ�ȭ
	}

	// Ÿ�� �׸��� �ʱ�ȭ
	ATileGrid* TileGrid = GetWorld()->SpawnActor<ATileGrid>(ATileGrid::StaticClass());
	if (TileGrid)
	{
		TileGrid->InitializeGrid();
	}

	// Observer ��ü ����
	UGameStateSubject* ObserverGameState = NewObject<UGameStateSubject>();

	//���� ���� �� ȭ�鿡 ǥ��
	UGameWidgetObserver* ScoreWidget = CreateWidget<UGameWidgetObserver>(GetWorld(), LoadClass<UGameWidgetObserver>(nullptr, TEXT("/Game/UI/ScoreWidget")));

	if (ScoreWidget)
	{
		ScoreWidget->AddToViewport();

		// ������ �������� ���
		ObserverGameState->RegisterObserver(ScoreWidget);
	}

	// 5�ʸ��� ���� ����
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [ObserverGameState]()
		{
			ObserverGameState->IncreaseScore(10);
		}, 5.0f, true);
}
