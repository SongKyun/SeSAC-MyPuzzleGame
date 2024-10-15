// 싱글톤 패턴 적용
// 게임의 전반적인 상태 관리, 현재 점수, 남은 이동 횟수 등의 게임 정보를 관리하며 전역에서 접근 가능

#include "GameManager.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

