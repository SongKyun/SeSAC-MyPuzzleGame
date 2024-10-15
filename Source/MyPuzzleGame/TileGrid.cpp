// Ÿ�ϵ��� �׸��带 �����ϰ�, Ÿ�� ����, Ÿ�� ��Ī Ž��, Ÿ�� �̵��� ó���ϴ� ������ ���

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
	// Ÿ�� ����
	float TileSpacing = 200.0f;
	
	for (int32 Row = 0; Row < GridSize; ++Row)
	{
		for (int32 Col = 0; Col < GridSize; ++Col)
		{
			// Ÿ�� ����
			ATile* NewTile = GetWorld()->SpawnActor<ATile>(ATile::StaticClass(), TileLocation, FRotator::ZeroRotator);

			if (NewTile)
			{
				Tiles.Add(NewTile);
			}

			// Ÿ�� ��ġ ������Ʈ ( Y �� �������� Ÿ���� ����)
			TileLocation.Y += TileSpacing;
		}
		// ���� ������ �Ѿ�� ���� X�� �̵�, Y �� �ʱ�ȭ
		TileLocation.X += TileSpacing;
		TileLocation.Y = 0.0f;
	}
}