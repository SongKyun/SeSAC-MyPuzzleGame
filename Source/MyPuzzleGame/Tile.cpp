// 타일 개별 객체를 관리하는 클래스, 타일의 색상, 모양, 상태, 매칭 여부를 관리

#include "Tile.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;

	// 타일 메쉬 컴포넌트 생성 및 설정
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	RootComponent = TileMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Tile(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (Tile.Succeeded())
	{
		TileMesh->SetStaticMesh(Tile.Object);
	}
}

void ATile::BeginPlay()
{
	Super::BeginPlay();
}

bool ATile::IsMatching(ATile* OtherTile)
{
	return TileType == OtherTile->TileType;
}