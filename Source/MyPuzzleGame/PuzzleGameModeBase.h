#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PuzzleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYPUZZLEGAME_API APuzzleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// 게임 시작 시 호출되는 함수
	virtual void BeginPlay() override;
};
