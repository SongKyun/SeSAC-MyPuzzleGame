// Ÿ�� ���� ��ü�� �����ϴ� Ŭ����, Ÿ���� ����, ���, ����, ��Ī ���θ� ����

#include "Tile.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATile::BeginPlay()
{
	Super::BeginPlay();

	SetRandomColor();
}

void ATile::SetRandomColor()
{
	int32 RandomValue = FMath::RandRange(0, 3);
	TileColor = static_cast<ETileColor>(RandomValue);
}

ETileColor ATile::GetTileColor() const
{
	return TileColor;
}
