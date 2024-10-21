// Fill out your copyright notice in the Description page of Project Settings.


#include "SwapTilesCommand.h"
#include "Tile.h"

void USwapTilesCommand::Initialize(ATile* InFirstTile, ATile* InSecondTile)
{
	FirstTile = InFirstTile;
	SecondTile = InSecondTile;

	// 원래 위치를 저장
	FirstTileOriginalLocation = FirstTile->GetActorLocation();
	SecondTileOriginalLocation = SecondTile->GetActorLocation();
}

void USwapTilesCommand::Execute()
{
	// 두 타일의 위치를 서로 교환
	FirstTile->SetActorLocation(SecondTileOriginalLocation);
	SecondTile->SetActorLocation(FirstTileOriginalLocation);

	// TODO :: 매칭 확인 등의 로직
}

void USwapTilesCommand::Undo()
{
	// 타일의 위치를 원래대로 되돌림
	FirstTile->SetActorLocation(FirstTileOriginalLocation);
	SecondTile->SetActorLocation(SecondTileOriginalLocation);
}