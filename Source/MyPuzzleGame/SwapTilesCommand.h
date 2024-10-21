// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Command.h"

#include "SwapTilesCommand.generated.h"

class ATile;
UCLASS()
class MYPUZZLEGAME_API USwapTilesCommand : public UObject, public ICommand
{
	GENERATED_BODY()

private:
	ATile* FirstTile;
	ATile* SecondTile;

	// ��ȯ �� Ÿ���� ��ġ
	FVector FirstTileOriginalLocation;
	FVector SecondTileOriginalLocation;

public:
	// ������
	void Initialize(ATile* InFirstTile, ATile* InSecondTile);

	// ICommand �������̽� ����
	virtual void Execute() override;
	virtual void Undo() override;
};
