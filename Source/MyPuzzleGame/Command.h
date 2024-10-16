// Excute()�� Undo() �޼��带 �����Ͽ�, ����� �����ϰ� ����� �� �ִ� ������ ����

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
	// ��� ����
	virtual void Execute() = 0;

	// ��� ��� (Undo)
	virtual void Undo() = 0;

	//virtual ~ICommand() = default;
};
