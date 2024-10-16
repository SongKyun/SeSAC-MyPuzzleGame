// Excute()와 Undo() 메서드를 정의하여, 명령을 실행하고 취소할 수 있는 구조를 제공

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Command.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCommand : public UInterface
{
	GENERATED_BODY()
};

class MYPUZZLEGAME_API ICommand
{
	GENERATED_BODY()

public:
	// 명령 실행
	virtual void Execute() = 0;

	// 명령 취소 (Undo)
	virtual void Undo() = 0;

	//virtual ~ICommand() = default;
};
