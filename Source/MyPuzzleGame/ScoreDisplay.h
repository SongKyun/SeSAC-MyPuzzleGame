// 옵저버 패턴 적용

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreDisplay.generated.h"

UCLASS()
class MYPUZZLEGAME_API AScoreDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	AScoreDisplay();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
