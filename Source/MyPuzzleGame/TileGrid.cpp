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
	TArray<FName> TileTypes = { FName("Cone"), FName("Cube") , FName("Cylinder") , FName("Sphere") , FName("Capsule") , FName("Pyramid") };

	for (int32 x = 0; x < GridWidth; ++x)
	{
		for (int32 y = 0; y < GridHeight; ++y)
		{
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
		TileArray[y * GridWidth + x] = Tile; // 타일 배열에 저장
	}
}

