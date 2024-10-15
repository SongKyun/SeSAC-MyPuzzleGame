#include "PuzzleGameModeBase.h"
#include "MyGameInstance.h"
#include "TileGrid.h"
#include "Kismet/GameplayStatics.h"

void APuzzleGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 게임 인스턴스 초기화
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->ResetGameState(); // 게임 상태 초기화
	}

	// 타일 그리드 초기화
	ATileGrid* TileGrid = GetWorld()->SpawnActor<ATileGrid>(ATileGrid::StaticClass());
	if (TileGrid)
	{
		TileGrid->InitializeGrid();
	}
}
