// 타일 개별 객체를 관리하는 클래스, 타일의 색상, 모양, 상태, 매칭 여부를 관리

#include "Tile.h"
#include "Engine/Engine.h"
#include "Async/ParallelFor.h"

ATile::ATile()
{
	// 타일 메쉬 컴포넌트 생성 및 설정
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	RootComponent = TileMesh;

	// 메시 업데이트를 위한 타일 타입 초기화
	TileType = FName("Cube"); // 기본 타입 Cube로 설정 (나중에 랜덤)

	bIsSelected = false; // 선택 여부 초기화
	TilePosition = FVector2D::ZeroVector; // 그리드 상의 좌표
}

void ATile::SetSelected(bool bSelected)
{
	bIsSelected = bSelected;
	UpdateTileAppearance();
}

void ATile::BeginPlay()
{
	Super::BeginPlay();

	// 타일 외형 업데이트 (TileType에 따라 메시 변경)
	UpdateTileAppearance();
}

bool ATile::IsMatching(ATile* OtherTile) const
{
	// 타일 타입이 일치하는지 확인
	return TileType == OtherTile->TileType;
}

void ATile::UpdateTileAppearance()
{
	if (TileMeshes.Contains(TileType))
	{
		//TileType에 맞는 Static Mesh를 설정
		TileMesh->SetStaticMesh(TileMeshes[TileType]);
	}
	else
	{
		// TileType에 맞는 메시가 없으면 기본 메시를 설정
		UE_LOG(LogTemp, Warning, TEXT("TileType %s has no Mesh set"), *TileType.ToString());
	}

	// 선택되었을 때의 시각적 피드백 (색상 변경)
	if (bIsSelected)
	{
		// 타일이 선택되었을 때의 효과
		// 예 : 색상 변경
		if (UStaticMeshComponent* MeshComponent = FindComponentByClass<UStaticMeshComponent>())
		{
			MeshComponent->SetRenderCustomDepth(true); // 선택된 타일을 강조
			MeshComponent->SetScalarParameterValueOnMaterials(TEXT("EmissiveStrength"), 10.0f); // 강조된 색상 변경
		}
	}
	else
	{
		if (UStaticMeshComponent* MeshComponent = FindComponentByClass<UStaticMeshComponent>())
		{
			MeshComponent->SetRenderCustomDepth(false); // 기본 상태로 복귀
			MeshComponent->SetScalarParameterValueOnMaterials(TEXT("EmissiveStrength"), 0.0f); // 기본 색상 복귀
		}
	}
}

void ATile::ProcessDataInParallel()
{
	TArray<int32> DataArray;
	DataArray.Init(0, 100);

	ParallelFor(DataArray.Num(), [&](int32 Index)
		{
			DataArray[Index] = Index * 2;

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Tile %d - %d"), Index, DataArray[Index]));
			}
		});

	UE_LOG(LogTemp, Warning, TEXT("ParallelFor Finish"));
}

bool ATile::IsAdjacentTo(ATile* OtherTile) const
{
	if (!OtherTile)
	{
		return false;
	}

	// 두 타일의 그리드 좌표 차이를 계산하여 인접 여부 확인
	int32 DeltaX = FMath::Abs(TilePosition.X - OtherTile->TilePosition.X);
	int32 DeltaY = FMath::Abs(TilePosition.Y - OtherTile->TilePosition.Y);

	// 두 타일이 가로 또는 세로로 1칸 차이일 경우 인접한 것으로 판단
	return (DeltaX + DeltaY) == 1;

	// 인접 여부를 확인 (가로 또는 세로로 한 칸 차이)
	//return(FMath::Abs(TilePosition.X - OtherTile->TilePosition.X) == 1 && TilePosition.Y == OtherTile->TilePosition.Y) ||
		//(FMath::Abs(TilePosition.Y - OtherTile->TilePosition.Y) == 1 && TilePosition.X == OtherTile->TilePosition.X);
}

void ATile::UpdateTilePosition(const FVector2D& NewPosition)
{
	TilePosition = NewPosition;
}

