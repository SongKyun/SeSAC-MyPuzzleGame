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

void ATileGrid::InitializeGrid()
{
	//// for���� ���� Ÿ�� �׸��� �׸���
	//for (int32 x = 0; x < GridWidth; ++x)
	//{
	//	for (int32 y = 0; y < GridHeight; ++y)
	//	{
	//		// Ÿ�� ����
	//		ATile* NewTile = GetWorld()->SpawnActor<ATile>(ATile::StaticClass());
	//		SetTileAt(x, y, NewTile);
	//	}
	//}

	//// ����ó��
	//ParallelFor(GridWidth * GridHeight, [this] (int32 Index)
	//	{
	//		int32 x = Index % GridWidth;
	//		int32 y = Index / GridWidth;

	//		// Ÿ���� �����ϰ�, 1���� �迭�� ����
	//		ATile* NewTile = GetWorld()->SpawnActor<ATile>(ATile::StaticClass());
	//		SetTileAt(x, y, NewTile);
	//	});

	for (int32 x = 0; x < GridWidth; ++x)
	{
		for (int32 y = 0; y < GridHeight; ++y)
		{
			// �񵿱������� Ÿ���� ����
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
		return nullptr; // ��ȿ���� �ʴ� ��ǥ ó��
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
