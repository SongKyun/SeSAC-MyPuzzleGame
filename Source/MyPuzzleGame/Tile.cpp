// Ÿ�� ���� ��ü�� �����ϴ� Ŭ����, Ÿ���� ����, ���, ����, ��Ī ���θ� ����

#include "Tile.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATile::BeginPlay()
{
	Super::BeginPlay();
}

bool ATile::IsMatching(ATile* OtherTile)
{
	return TileType == OtherTile->TileType;
}