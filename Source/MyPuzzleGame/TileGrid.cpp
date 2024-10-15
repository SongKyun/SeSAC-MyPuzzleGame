// 타일들의 그리드를 관리하고, 타일 생성, 타일 매칭 탐색, 타일 이동을 처리하는 역할을 담당

#include "TileGrid.h"
#include "Tile.h"

ATileGrid::ATileGrid()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATileGrid::BeginPlay()
{
	Super::BeginPlay();
}

void ATileGrid::InitializeGrid()
{
	//// for문을 돌며 타일 그리드 그리기
	//for (int32 x = 0; x < GridWidth; ++x)
	//{
	//	for (int32 y = 0; y < GridHeight; ++y)
	//	{
	//		// 타일 생성
	//		ATile* NewTile = GetWorld()->SpawnActor<ATile>(ATile::StaticClass());
	//		SetTileAt(x, y, NewTile);
	//	}
	//}

	//// 병렬처리
	//ParallelFor(GridWidth * GridHeight, [this] (int32 Index)
	//	{
	//		int32 x = Index % GridWidth;
	//		int32 y = Index / GridWidth;

	//		// 타일을 생성하고, 1차원 배열에 저장
	//		ATile* NewTile = GetWorld()->SpawnActor<ATile>(ATile::StaticClass());
	//		SetTileAt(x, y, NewTile);
	//	});

	for (int32 x = 0; x < GridWidth; ++x)
	{
		for (int32 y = 0; y < GridHeight; ++y)
		{
			// 비동기적으로 타일을 생성
			AsyncTask(ENamedThreads::GameThread, [this, x, y]
				{
					ATile* NewTile = GetWorld()->SpawnActor<ATile>(ATile::StaticClass());
					SetTileAt(x, y, NewTile);
				});
		}
	}
}

ATile* ATileGrid::GetTileAt(int32 x, int32 y) const
{
	if (x < 0 || x >= GridWidth || y < 0 || y >= GridHeight)
	{
		return nullptr; // 유효하지 않는 좌표 처리
	}
	return TileArray[y * GridWidth + x];
}

void ATileGrid::SetTileAt(int32 x, int32 y, ATile* Tile)
{
	if (x >= 0 && x < GridWidth && y >= 0 && y < GridHeight)
	{
		TileArray[y * GridWidth + x];
	}
}
