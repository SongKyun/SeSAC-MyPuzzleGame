// Fill out your copyright notice in the Description page of Project Settings.


#include "TileCommandInvoker.h"
#include "Command.h"

ATileCommandInvoker::ATileCommandInvoker()
{
}

ATileCommandInvoker::~ATileCommandInvoker()
{
}

void ATileCommandInvoker::ExecuteCommand(ICommand* Command)
{
	Command->Execute();
	CommandHistory.Push(Command);
}

void ATileCommandInvoker::UndoLastCommand()
{
	if (CommandHistory.Num() > 0)
	{
		ICommand* lastCommand = CommandHistory.Last();
		lastCommand->Undo();
		CommandHistory.Pop();
	}
}
