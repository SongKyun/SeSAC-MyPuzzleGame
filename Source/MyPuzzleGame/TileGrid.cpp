// Ÿ�ϵ��� �׸��带 �����ϰ�, Ÿ�� ����, Ÿ�� ��Ī Ž��, Ÿ�� �̵��� ó���ϴ� ������ ���

#include "TileGrid.h"
#include "Tile.h"
#include "Camera/CameraActor.h"

ATileGrid::ATileGrid()
{
	PrimaryActorTick.bCanEverTick = false;

	GridWidth = 8;
	GridHeight = 8;
	TileSpacing = 100.0f;
	TileArray.SetNum(GridWidth * GridHeight);
}

void ATileGrid::BeginPlay()
{
	Super::BeginPlay();
	InitializeGrid();

	/*// �÷��̾� ��Ʈ�ѷ� ��������
	//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//if (PlayerController)
	//{
	//	// ���콺 Ŀ�� ǥ��
	//	PlayerController->bShowMouseCursor = true;

	//	// ���콺�θ� ��Ʈ�� �����ϰ� ����
	//	PlayerController->bEnableClickEvents = true; // ���콺 Ŭ�� �̺�Ʈ Ȱ��ȭ
	//	PlayerController->bEnableMouseOverEvents = true; // ���콺 ���� �̺�Ʈ Ȱ��ȭ
	//	PlayerController->bEnableTouchEvents = false; // ��ġ �̺�Ʈ ��Ȱ��ȭ

	//	// ī�޶� ���� ����
	//	ACameraActor* CameraActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass());

	//	// ī�޶� ��ġ �� ȸ�� ����
	//	FVector CameraLocation(GridWidth * 100.0f / 2, GridHeight * 100.0f / 2, 400.0f); // �׸��� �߾� �� 1000 ����
	//	FRotator CameraRotation(-90.0f, 0.0f, 0.0f); // ������ �����ٺ��� ���� (Pitch = -90��)

	//	CameraActor->SetActorLocation(CameraLocation);
	//	CameraActor->SetActorRotation(CameraRotation);

	//	// �÷��̾� ��Ʈ�ѷ��� �� ī�޶� ����ϵ��� ����
	//	PlayerController->SetViewTargetWithBlend(CameraActor, 0.0f);
	//} */
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

	/* //�迭 ũ�� �ʱ�ȭ
	TileArray.SetNum(GridWidth * GridHeight);

	//Ÿ�� ũ��
	const float TileSize = 100.0f;

	for (int32 x = 0; x < GridWidth; ++x)
	{
		for (int32 y = 0; y < GridHeight; ++y)
		{
			// �񵿱������� Ÿ���� ����
			AsyncTask(ENamedThreads::GameThread, [this, x, y, TileSize]
				{
					ATile* NewTile = GetWorld()->SpawnActor<ATile>(ATile::StaticClass());

					// Ÿ���� ���� ��ġ ����
					FVector TileLocation(x * TileSize, y * TileSize, 0.0f);
					NewTile->SetActorLocation(TileLocation);

					// �迭�� Ÿ�� ����
					SetTileAt(x, y, NewTile);
				});
		}
	}*/

	// ������ TileType ����Ʈ
	TArray<FName> TileTypes = { FName("Cone"), FName("Cube") , FName("Cylinder") , FName("Sphere") , FName("Capsule") , FName("Pyramid") };

	for (int32 x = 0; x < GridWidth; ++x)
	{
		for (int32 y = 0; y < GridHeight; ++y)
		{
			// ��׶��忡�� Ÿ�� Ÿ���� �����ϴ� �۾��� �񵿱�� ����
			AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, x, y, TileTypes]()
				{
					// Ÿ�� Ÿ���� �����ϰ� ���� (�񵿱� �۾�)
					FName RandomTileType = TileTypes[FMath::RandRange(0, TileTypes.Num() - 1)];

					// ���� �����忡�� Ÿ�� ������ ���� ������ ó��
					AsyncTask(ENamedThreads::GameThread, [this, x, y, RandomTileType]()
						{
							if (!TileClass)
							{
								UE_LOG(LogTemp, Error, TEXT("TIleClass is not set in TileGrid"));
								return;
							}

							// Ÿ�� ���� (���� �����忡�� ����)
							FActorSpawnParameters SpawnParams;
							ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, SpawnParams); // ���� Ÿ�� Ŭ���� ���
							if (NewTile)
							{
								// ������ Ÿ���� Ÿ�� ����
								NewTile->TileType = RandomTileType;

								// Ÿ�� ���� ������Ʈ
								NewTile->UpdateTileAppearance();

								// Ÿ���� TileGrid�� �ڽ����� ����
								NewTile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

								// ������� ��ġ�� Ÿ���� ��ġ
								FVector RelativeLocation = FVector(x * TileSpacing, y * TileSpacing, 0.0f);
								NewTile->SetActorRelativeLocation(RelativeLocation);

								// Ÿ���� �׸��忡 ��ġ (���� ��ǥ ���)
								//FVector TileLocation = FVector(x * TileSpacing, y * TileSpacing, 0.0f);
								//NewTile->SetActorLocation(TileLocation);

								// �׸��忡 Ÿ�� ����
								SetTileAt(x, y, NewTile);

								// ����� ���
								UE_LOG(LogTemp, Warning, TEXT("Tile created at [%d, %d]"), x, y, *RandomTileType.ToString(), * RelativeLocation.ToString());
							}
							else
							{
								UE_LOG(LogTemp, Error, TEXT("Failed to spawn title at [%d, %d]"), x, y);
							}
						});
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
		TileArray[y * GridWidth + x] = Tile; // Ÿ�� �迭�� ����
	}
}

