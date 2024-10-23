// 타일들의 그리드를 관리하고, 타일 생성, 타일 매칭 탐색, 타일 이동을 처리하는 역할을 담당

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

	/*// 플레이어 컨트롤러 가져오기
	//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//if (PlayerController)
	//{
	//	// 마우스 커서 표시
	//	PlayerController->bShowMouseCursor = true;

	//	// 마우스로만 컨트롤 가능하게 설정
	//	PlayerController->bEnableClickEvents = true; // 마우스 클릭 이벤트 활성화
	//	PlayerController->bEnableMouseOverEvents = true; // 마우스 오버 이벤트 활성화
	//	PlayerController->bEnableTouchEvents = false; // 터치 이벤트 비활성화

	//	// 카메라 액터 생성
	//	ACameraActor* CameraActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass());

	//	// 카메라 위치 및 회전 설정
	//	FVector CameraLocation(GridWidth * 100.0f / 2, GridHeight * 100.0f / 2, 400.0f); // 그리드 중앙 위 1000 유닛
	//	FRotator CameraRotation(-90.0f, 0.0f, 0.0f); // 위에서 내려다보는 각도 (Pitch = -90도)

	//	CameraActor->SetActorLocation(CameraLocation);
	//	CameraActor->SetActorRotation(CameraRotation);

	//	// 플레이어 컨트롤러가 이 카메라를 사용하도록 설정
	//	PlayerController->SetViewTargetWithBlend(CameraActor, 0.0f);
	//} */
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

	/* //배열 크기 초기화
	TileArray.SetNum(GridWidth * GridHeight);

	//타일 크기
	const float TileSize = 100.0f;

	for (int32 x = 0; x < GridWidth; ++x)
	{
		for (int32 y = 0; y < GridHeight; ++y)
		{
			// 비동기적으로 타일을 생성
			AsyncTask(ENamedThreads::GameThread, [this, x, y, TileSize]
				{
					ATile* NewTile = GetWorld()->SpawnActor<ATile>(ATile::StaticClass());

					// 타일의 월드 위치 설정
					FVector TileLocation(x * TileSize, y * TileSize, 0.0f);
					NewTile->SetActorLocation(TileLocation);

					// 배열에 타일 저장
					SetTileAt(x, y, NewTile);
				});
		}
	}*/

	// 가능한 TileType 리스트
	TArray<FName> TileTypes = 
	{ FName("Cone"), FName("Cube") , FName("Cylinder") , FName("Sphere") , FName("Capsule") , FName("Pyramid") };

	for (int32 x = 0; x < GridWidth; ++x)
	{
		for (int32 y = 0; y < GridHeight; ++y)
		{
			// 백그라운드에서 타일 타입을 결정하는 작업을 비동기로 수정
			AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, x, y, TileTypes]()
				{
					// 타일 타입을 랜덤하게 결정 (비동기 작업)
					FName RandomTileType = TileTypes[FMath::RandRange(0, TileTypes.Num() - 1)];

					//  게임 스레드에서 타일 생성 및 Array에 저장
					AsyncTask(ENamedThreads::GameThread, [this, x, y, RandomTileType]()
					{
						if (!TileClass)
						{
							UE_LOG(LogTemp, Error, TEXT("TileClass is not set in TileGrid"));
							return;
						}

						// 타일 생성
						FActorSpawnParameters SpawnParams;
						ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, SpawnParams);

						if (NewTile)
						{
							// 랜덤 타일 타입
							NewTile->TileType = RandomTileType;

							// 타일 속성 설정
							NewTile->TileGrid = this; // 타일 그리드 참조

							// 타일 그리드 위치 설정
							NewTile->TilePosition = FVector2D(x, y);

							// 타일 외형 업데이트
							NewTile->UpdateTileAppearance();

							// 타일을 TileGrid의 자식으로 부착
							NewTile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

							// 상대적인 위치로 타일을 배치
							FVector RelativeLocation = FVector(x * TileSpacing, y * TileSpacing, 0.0f);
							NewTile->SetActorRelativeLocation(RelativeLocation);

							// 그리드에 타일 저장
							SetTileAt(x, y, NewTile);

							// 디버그 출력
							UE_LOG(LogTemp, Warning, TEXT("Tile created at [%d, %d]"), x, y, *RelativeLocation.ToString());
						}
					});
				});

			/*
			// 백그라운드에서 타일 타입을 결정하는 작업을 비동기로 수정
			AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, x, y, TileTypes]()
				{
					// 타일 타입을 랜덤하게 결정 (비동기 작업)
					FName RandomTileType = TileTypes[FMath::RandRange(0, TileTypes.Num() - 1)];

					// 게임 스레드에서 타일 생성과 외형 설정을 처리
					AsyncTask(ENamedThreads::GameThread, [this, x, y, RandomTileType]()
						{
							if (!TileClass)
							{
								UE_LOG(LogTemp, Error, TEXT("TIleClass is not set in TileGrid"));
								return;
							}

							// 타일 생성 (게임 스레드에서 실행)
							FActorSpawnParameters SpawnParams;
							ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, SpawnParams); // 블프 타일 클래스 사용
							if (NewTile)
							{
								// 생성된 타일의 타입 설정
								NewTile->TileType = RandomTileType;

								// 타일 외형 업데이트
								NewTile->UpdateTileAppearance();

								// 타일을 TileGrid의 자식으로 부착
								NewTile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

								// 상대적인 위치로 타일을 배치
								FVector RelativeLocation = FVector(x * TileSpacing, y * TileSpacing, 0.0f);
								NewTile->SetActorRelativeLocation(RelativeLocation);

								// 타일을 그리드에 배치 (월드 좌표 계산)
								//FVector TileLocation = FVector(x * TileSpacing, y * TileSpacing, 0.0f);
								//NewTile->SetActorLocation(TileLocation);

								// 그리드에 타일 저장
								SetTileAt(x, y, NewTile);

								// 디버그 출력
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
		return nullptr; // 유효하지 않는 좌표 처리
	}
	return TileArray[y * GridWidth + x];
}

void ATileGrid::SetTileAt(int32 x, int32 y, ATile* Tile)
{
	if (x >= 0 && x < GridWidth && y >= 0 && y < GridHeight)
	{
		TileArray[y * GridWidth + x] = Tile; // 타일 배열에 저장
	}
}

TArray<ATile*> ATileGrid::CheckForMatches()
{
	// 매칭이 된 타일들
	TArray<ATile*> AllMatchedTiles;

	// Grid를 바둑판으로 for문으로 확인
	// 가로 매칭 확인
	for (int32 X = 0; X < GridWidth; ++X)
	{
		for (int32 Y = 0; Y < GridHeight; ++Y)
		{
			ATile* CurrentTile = GetTileAt(X, Y);
			if (!CurrentTile) continue;

			// 매칭된 타일 찾기
			TArray<ATile*> HorizontalMatches =
				CheckHorizontalMatches(X, Y);

			if (HorizontalMatches.Num() >= 3)
			{
				AllMatchedTiles.Append(HorizontalMatches);
			}
		}
	}

	// 세로 매칭 확인
	for (int32 X = 0; X < GridWidth; ++X)
	{
		for (int32 Y = 0; Y < GridHeight; ++Y)
		{
			ATile* CurrentTile = GetTileAt(X, Y);
			if (!CurrentTile) continue;

			// 매칭된 타일 찾기
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
		// 타일 배열 업데이트
		SetTileAt(X1, Y1, SecondTile);
		SetTileAt(X2, Y2, FirstTile);

		// 타일의 그리드 좌표도 업데이트
		FVector2D TempPosition = FirstTile->TilePosition;
		FirstTile->TilePosition = SecondTile->TilePosition;
		SecondTile->TilePosition = TempPosition;

		// 타일 위치를 스왑
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

	// 오른쪽으로 2칸까지 같은 타일이 있는지 확인
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

	// 오른쪽으로 2칸까지 같은 타일이 있는지 확인
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
				// 타일 삭제하기 전에 애니메이션 적용할 수 있음
				// 예시 : Tile->PlayDeleteAnimation(); /// 0.5초 동안 Scale을 0으로 줄이기
				Tile->Destroy();
			}
		}
	}

	// 매칭된 타일 수에 따라 점수 추가 예시
	// AddScore(NumMatchedTiles * 100); 

	// 빈 공간을 채우기 위해 타일을 아래로 드랍
	DropDownTiles();

	// 이후 매칭 루프 처리
	ProcessMatchingLoop(); // 매칭 루프 시작
}

void ATileGrid::DropDownTiles()
{
	for (int32 X = 0; X < GridWidth; X++)
	{
		for (int32 Y = GridHeight - 1; Y >= 0; --Y) // 아래에서 위로 확인
		{
			if (!GetTileAt(X, Y)) // 빈 칸인 경우
			{
				for (int32 AboveY = Y - 1; AboveY >= 0; --AboveY)
				{
					ATile* AboveTile = GetTileAt(X, AboveY);
					if (AboveTile)
					{
						// 타일 배열 업데이트

						SetTileAt(X, Y, AboveTile);
						SetTileAt(X, AboveY, nullptr);

						//타일의 그리드 좌표 갱신
						AboveTile->TilePosition = FVector2D(X, Y);

						// 타일을 이동 (상대적 위치로)
						FVector RelativeLocation = FVector(X * TileSpacing, Y * TileSpacing, 0);
						AboveTile->SetActorRelativeLocation(RelativeLocation);

						break;
					}
				}
			}
		}

		// 빈 칸을 새로운 타일로 채우기
		RefillGrid();
	}
}

void ATileGrid::RefillGrid()
{
	for (int32 x = 0; x < GridWidth; ++x)
	{
		for (int32 y = 0; y < GridHeight; ++y)
		{
			// x,y 좌표위치 그리드에 타일이 없다면,
			if (!GetTileAt(x, y))
			{
				// 새로운 타일 생성
				ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass);

				if (NewTile)
				{
					NewTile->TileType = GenerateRandomTileType();

					// 타일 속성 설정
					NewTile->TileGrid = this; // 타일 그리드 참조

					// 타일 그리드 위치 설정
					NewTile->TilePosition = FVector2D(x, y);

					// 타일 외형 업데이트
					NewTile->UpdateTileAppearance();

					// 타일을 TileGrid의 자식으로 부착
					NewTile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

					// 상대적인 위치로 타일을 배치
					FVector RelativeLocation = FVector(x * TileSpacing, y * TileSpacing, 0.0f);
					NewTile->SetActorRelativeLocation(RelativeLocation);

					// 그리드에 타일 저장
					SetTileAt(x, y, NewTile);
				}
			}
		}
	}

	// 새로운 타일이 생성된 후 매칭 루프 처리
	ProcessMatchingLoop(); // 매칭 루프 시작
}

FName ATileGrid::GenerateRandomTileType()
{
	TArray<FName> TileTypes =
	{ FName("Cone"), FName("Cube") , FName("Cylinder") , FName("Sphere") , FName("Capsule") , FName("Pyramid") };

	return TileTypes[FMath::RandRange(0, TileTypes.Num() - 1)];
}

void ATileGrid::ProcessMatchingLoop()
{
	// 매칭이 있는지 확인
	TArray<ATile*> MatchingTiles = CheckForMatches();

	if (MatchingTiles.Num() > 0)
	{
		// 매칭된 타일이 있을 경우 삭제
		RemoveMatchingTiles(MatchingTiles);

		// 타일을 빈 공간으로 이동
		DropDownTiles();

		// 빈 공간에 새로운 타일을 채우기
		RefillGrid();

		// 모든 작업이 끝난 후 다시 매칭을 확인하기 위해 재귀 호출( 매칭이 더 이상 없을 때까지 반복)
		ProcessMatchingLoop(); // 재귀 호출
	}
	else
	{
		// 더 이상 매칭이 없으면 루프 종료
		UE_LOG(LogTemp, Display, TEXT("No more matches, puzzle stabilized."));
	}
}







