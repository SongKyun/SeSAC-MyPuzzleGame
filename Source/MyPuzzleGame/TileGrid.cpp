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
	TArray<FName> TileTypes = 
	{ FName("Cone"), FName("Cube") , FName("Cylinder") , FName("Sphere") , FName("Capsule") , FName("Pyramid") };

	for (int32 x = 0; x < GridWidth; ++x)
	{
		for (int32 y = 0; y < GridHeight; ++y)
		{
			// ��׶��忡�� Ÿ�� Ÿ���� �����ϴ� �۾��� �񵿱�� ����
			AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, x, y, TileTypes]()
				{
					// Ÿ�� Ÿ���� �����ϰ� ���� (�񵿱� �۾�)
					FName RandomTileType = TileTypes[FMath::RandRange(0, TileTypes.Num() - 1)];

					//  ���� �����忡�� Ÿ�� ���� �� Array�� ����
					AsyncTask(ENamedThreads::GameThread, [this, x, y, RandomTileType]()
					{
						if (!TileClass)
						{
							UE_LOG(LogTemp, Error, TEXT("TileClass is not set in TileGrid"));
							return;
						}

						// Ÿ�� ����
						FActorSpawnParameters SpawnParams;
						ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, SpawnParams);

						if (NewTile)
						{
							// ���� Ÿ�� Ÿ��
							NewTile->TileType = RandomTileType;

							// Ÿ�� �Ӽ� ����
							NewTile->TileGrid = this; // Ÿ�� �׸��� ����

							// Ÿ�� �׸��� ��ġ ����
							NewTile->TilePosition = FVector2D(x, y);

							// Ÿ�� ���� ������Ʈ
							NewTile->UpdateTileAppearance();

							// Ÿ���� TileGrid�� �ڽ����� ����
							NewTile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

							// ������� ��ġ�� Ÿ���� ��ġ
							FVector RelativeLocation = FVector(x * TileSpacing, y * TileSpacing, 0.0f);
							NewTile->SetActorRelativeLocation(RelativeLocation);

							// �׸��忡 Ÿ�� ����
							SetTileAt(x, y, NewTile);

							// ����� ���
							UE_LOG(LogTemp, Warning, TEXT("Tile created at [%d, %d]"), x, y, *RelativeLocation.ToString());
						}
					});
				});

			/*
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
				}); */
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

TArray<ATile*> ATileGrid::CheckForMatches()
{
	// ��Ī�� �� Ÿ�ϵ�
	TArray<ATile*> AllMatchedTiles;

	// Grid�� �ٵ������� for������ Ȯ��
	// ���� ��Ī Ȯ��
	for (int32 X = 0; X < GridWidth; ++X)
	{
		for (int32 Y = 0; Y < GridHeight; ++Y)
		{
			ATile* CurrentTile = GetTileAt(X, Y);
			if (!CurrentTile) continue;

			// ��Ī�� Ÿ�� ã��
			TArray<ATile*> HorizontalMatches =
				CheckHorizontalMatches(X, Y);

			if (HorizontalMatches.Num() >= 3)
			{
				AllMatchedTiles.Append(HorizontalMatches);
			}
		}
	}

	// ���� ��Ī Ȯ��
	for (int32 X = 0; X < GridWidth; ++X)
	{
		for (int32 Y = 0; Y < GridHeight; ++Y)
		{
			ATile* CurrentTile = GetTileAt(X, Y);
			if (!CurrentTile) continue;

			// ��Ī�� Ÿ�� ã��
			TArray<ATile*> VerticalMatches =
				CheckVerticalMatches(X, Y);

			if (VerticalMatches.Num() >= 3)
			{
				AllMatchedTiles.Append(VerticalMatches);
			}
		}
	}

	return AllMatchedTiles;
}

void ATileGrid::SwapTiles(ATile* FirstTile, ATile* SecondTile)
{
	int32 X1, Y1, X2, Y2;
	if (GetTileGridPosition(FirstTile, X1, Y1) && GetTileGridPosition(SecondTile, X2, Y2))
	{
		// Ÿ�� �迭 ������Ʈ
		SetTileAt(X1, Y1, SecondTile);
		SetTileAt(X2, Y2, FirstTile);

		// Ÿ���� �׸��� ��ǥ�� ������Ʈ
		FVector2D TempPosition = FirstTile->TilePosition;
		FirstTile->TilePosition = SecondTile->TilePosition;
		SecondTile->TilePosition = TempPosition;

		// Ÿ�� ��ġ�� ����
		FVector TempLocation = FirstTile->GetActorLocation();
		FirstTile->SetActorLocation(SecondTile->GetActorLocation());
		SecondTile->SetActorLocation(TempLocation);
	}
}

TArray<ATile*> ATileGrid::CheckHorizontalMatches(int32 StartX, int32 StartY)
{
	TArray<ATile*> HorizontalMatches;
	ATile* StartTile = GetTileAt(StartX, StartY);

	if (!StartTile) return HorizontalMatches;

	HorizontalMatches.Add(StartTile);

	// ���������� 2ĭ���� ���� Ÿ���� �ִ��� Ȯ��
	for (int32 X = StartX + 1; X < GridWidth; ++X)
	{
		ATile* NextTile = GetTileAt(X, StartY);
		if (NextTile && NextTile->TileType == StartTile->TileType)
		{
			HorizontalMatches.Add(NextTile);
		}
		else
		{
			break;
		}
	}

	return HorizontalMatches;
}

TArray<ATile*> ATileGrid::CheckVerticalMatches(int32 StartX, int32 StartY)
{
	TArray<ATile*> VerticalMatches;
	ATile* StartTile = GetTileAt(StartX, StartY);

	if (!StartTile) return VerticalMatches;

	VerticalMatches.Add(StartTile);

	// ���������� 2ĭ���� ���� Ÿ���� �ִ��� Ȯ��
	for (int32 Y = StartY + 1; Y < GridHeight; ++Y)
	{
		ATile* NextTile = GetTileAt(StartX, Y);
		if (NextTile && NextTile->TileType == StartTile->TileType)
		{
			VerticalMatches.Add(NextTile);
		}
		else
		{
			break;
		}
	}

	return VerticalMatches;
}

bool ATileGrid::GetTileGridPosition(ATile* Tile, int32& OutX, int32& OutY) const
{
	for (int32 Index = 0; Index < TileArray.Num(); ++Index)
	{
		if (TileArray[Index] == Tile)
		{
			OutX = Index % GridWidth;
			OutY = Index / GridWidth;
			return true;
		}
	}
	return false;
}

void ATileGrid::RemoveMatchingTiles(const TArray<ATile*>& MatchingTiles)
{
	for (ATile* Tile : MatchingTiles)
	{
		if (Tile)
		{
			int32 X, Y;
			if (GetTileGridPosition(Tile, X, Y))
			{
				SetTileAt(X, Y, nullptr);
				// Ÿ�� �����ϱ� ���� �ִϸ��̼� ������ �� ����
				// ���� : Tile->PlayDeleteAnimation(); /// 0.5�� ���� Scale�� 0���� ���̱�
				Tile->Destroy();
			}
		}
	}

	// ��Ī�� Ÿ�� ���� ���� ���� �߰� ����
	// AddScore(NumMatchedTiles * 100); 

	// �� ������ ä��� ���� Ÿ���� �Ʒ��� ���
	DropDownTiles();

	// ���� ��Ī ���� ó��
	ProcessMatchingLoop(); // ��Ī ���� ����
}

void ATileGrid::DropDownTiles()
{
	for (int32 X = 0; X < GridWidth; X++)
	{
		for (int32 Y = GridHeight - 1; Y >= 0; --Y) // �Ʒ����� ���� Ȯ��
		{
			if (!GetTileAt(X, Y)) // �� ĭ�� ���
			{
				for (int32 AboveY = Y - 1; AboveY >= 0; --AboveY)
				{
					ATile* AboveTile = GetTileAt(X, AboveY);
					if (AboveTile)
					{
						// Ÿ�� �迭 ������Ʈ

						SetTileAt(X, Y, AboveTile);
						SetTileAt(X, AboveY, nullptr);

						//Ÿ���� �׸��� ��ǥ ����
						AboveTile->TilePosition = FVector2D(X, Y);

						// Ÿ���� �̵� (����� ��ġ��)
						FVector RelativeLocation = FVector(X * TileSpacing, Y * TileSpacing, 0);
						AboveTile->SetActorRelativeLocation(RelativeLocation);

						break;
					}
				}
			}
		}

		// �� ĭ�� ���ο� Ÿ�Ϸ� ä���
		RefillGrid();
	}
}

void ATileGrid::RefillGrid()
{
	for (int32 x = 0; x < GridWidth; ++x)
	{
		for (int32 y = 0; y < GridHeight; ++y)
		{
			// x,y ��ǥ��ġ �׸��忡 Ÿ���� ���ٸ�,
			if (!GetTileAt(x, y))
			{
				// ���ο� Ÿ�� ����
				ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass);

				if (NewTile)
				{
					NewTile->TileType = GenerateRandomTileType();

					// Ÿ�� �Ӽ� ����
					NewTile->TileGrid = this; // Ÿ�� �׸��� ����

					// Ÿ�� �׸��� ��ġ ����
					NewTile->TilePosition = FVector2D(x, y);

					// Ÿ�� ���� ������Ʈ
					NewTile->UpdateTileAppearance();

					// Ÿ���� TileGrid�� �ڽ����� ����
					NewTile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

					// ������� ��ġ�� Ÿ���� ��ġ
					FVector RelativeLocation = FVector(x * TileSpacing, y * TileSpacing, 0.0f);
					NewTile->SetActorRelativeLocation(RelativeLocation);

					// �׸��忡 Ÿ�� ����
					SetTileAt(x, y, NewTile);
				}
			}
		}
	}

	// ���ο� Ÿ���� ������ �� ��Ī ���� ó��
	ProcessMatchingLoop(); // ��Ī ���� ����
}

FName ATileGrid::GenerateRandomTileType()
{
	TArray<FName> TileTypes =
	{ FName("Cone"), FName("Cube") , FName("Cylinder") , FName("Sphere") , FName("Capsule") , FName("Pyramid") };

	return TileTypes[FMath::RandRange(0, TileTypes.Num() - 1)];
}

void ATileGrid::ProcessMatchingLoop()
{
	// ��Ī�� �ִ��� Ȯ��
	TArray<ATile*> MatchingTiles = CheckForMatches();

	if (MatchingTiles.Num() > 0)
	{
		// ��Ī�� Ÿ���� ���� ��� ����
		RemoveMatchingTiles(MatchingTiles);

		// Ÿ���� �� �������� �̵�
		DropDownTiles();

		// �� ������ ���ο� Ÿ���� ä���
		RefillGrid();

		// ��� �۾��� ���� �� �ٽ� ��Ī�� Ȯ���ϱ� ���� ��� ȣ��( ��Ī�� �� �̻� ���� ������ �ݺ�)
		ProcessMatchingLoop(); // ��� ȣ��
	}
	else
	{
		// �� �̻� ��Ī�� ������ ���� ����
		UE_LOG(LogTemp, Display, TEXT("No more matches, puzzle stabilized."));
	}
}







