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

void ATileGrid::CreateGrid(int32 Size)
{
	GridSize = Size;
	FVector TileLocation(0.0f, 0.0f, 0.0f);
	// 타일 간격
	float TileSpacing = 200.0f;
	
	for (int32 Row = 0; Row < GridSize; ++Row)
	{
		for (int32 Col = 0; Col < GridSize; ++Col)
		{
			// 타일 생성
			ATile* NewTile = GetWorld()->SpawnActor<ATile>(ATile::StaticClass(), TileLocation, FRotator::ZeroRotator);

			if (NewTile)
			{
				Tiles.Add(NewTile);
			}

			// 타일 위치 업데이트 ( Y 축 방향으로 타일을 나열)
			TileLocation.Y += TileSpacing;
		}
		// 다음 행으로 넘어가기 위해 X축 이동, Y 축 초기화
		TileLocation.X += TileSpacing;
		TileLocation.Y = 0.0f;
	}
}