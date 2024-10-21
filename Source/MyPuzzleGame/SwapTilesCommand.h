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

	// 교환 전 타일의 위치
	FVector FirstTileOriginalLocation;
	FVector SecondTileOriginalLocation;

public:
	// 생성자
	void Initialize(ATile* InFirstTile, ATile* InSecondTile);

	// ICommand 인터페이스 구현
	virtual void Execute() override;
	virtual void Undo() override;
};
