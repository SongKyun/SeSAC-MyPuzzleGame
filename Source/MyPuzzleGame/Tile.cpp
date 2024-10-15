// 타일 개별 객체를 관리하는 클래스, 타일의 색상, 모양, 상태, 매칭 여부를 관리

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