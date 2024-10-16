// Ÿ�� ���� ��ü�� �����ϴ� Ŭ����, Ÿ���� ����, ���, ����, ��Ī ���θ� ����

#include "Tile.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;

	// Ÿ�� �޽� ������Ʈ ���� �� ����
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