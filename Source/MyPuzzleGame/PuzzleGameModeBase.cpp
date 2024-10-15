#include "PuzzleGameModeBase.h"
#include "MyGameInstance.h"
#include "TileGrid.h"
#include "Kismet/GameplayStatics.h"

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
}
