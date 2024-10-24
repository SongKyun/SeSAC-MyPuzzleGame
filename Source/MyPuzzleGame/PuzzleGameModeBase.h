#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PuzzleGameModeBase.generated.h"

class UGameWidgetObserver;
UCLASS()
class MYPUZZLEGAME_API APuzzleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// ���� ���� �� ȣ��Ǵ� �Լ�
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameWidgetObserver> MainWidgetClass;
};
