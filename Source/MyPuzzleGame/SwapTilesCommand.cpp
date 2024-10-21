// Fill out your copyright notice in the Description page of Project Settings.


#include "SwapTilesCommand.h"
#include "Tile.h"

void USwapTilesCommand::Initialize(ATile* InFirstTile, ATile* InSecondTile)
{
	FirstTile = InFirstTile;
	SecondTile = InSecondTile;

	// ���� ��ġ�� ����
	FirstTileOriginalLocation = FirstTile->GetActorLocation();
	SecondTileOriginalLocation = SecondTile->GetActorLocation();
}

void USwapTilesCommand::Execute()
{
	// �� Ÿ���� ��ġ�� ���� ��ȯ
	FirstTile->SetActorLocation(SecondTileOriginalLocation);
	SecondTile->SetActorLocation(FirstTileOriginalLocation);

	// TODO :: ��Ī Ȯ�� ���� ����
}

void USwapTilesCommand::Undo()
{
	// Ÿ���� ��ġ�� ������� �ǵ���
	FirstTile->SetActorLocation(FirstTileOriginalLocation);
	SecondTile->SetActorLocation(SecondTileOriginalLocation);
}