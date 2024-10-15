// 옵저버 패턴 적용

#include "ScoreDisplay.h"

AScoreDisplay::AScoreDisplay()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AScoreDisplay::BeginPlay()
{
	Super::BeginPlay();
	
}

void AScoreDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

