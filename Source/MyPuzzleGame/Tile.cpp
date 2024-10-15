// 타일 개별 객체를 관리하는 클래스, 타일의 색상, 모양, 상태, 매칭 여부를 관리

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
