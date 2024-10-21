// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileCommandInvoker.generated.h"

class ICommand;

UCLASS()
class MYPUZZLEGAME_API ATileCommandInvoker : public AActor
{
	GENERATED_BODY()

public:
	ATileCommandInvoker();
	~ATileCommandInvoker();

	void ExecuteCommand(ICommand* Command);
	void UndoLastCommand();

private:
	TArray<ICommand*> CommandHistory;
};
