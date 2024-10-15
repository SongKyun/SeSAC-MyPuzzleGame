// 싱글톤 패턴 적용
// 게임의 전반적인 상태 관리, 현재 점수, 남은 이동 횟수 등의 게임 정보를 관리하며 전역에서 접근 가능

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class MYPUZZLEGAME_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
