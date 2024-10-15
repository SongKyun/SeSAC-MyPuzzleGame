// 싱글톤 개념

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class MYPUZZLEGAME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UMyGameInstance();

public:
	// 게임 상태 관리 변수들

	// 플레이어 점수
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Data")
	int32 PlayerScore;

	// 남은 이동 횟수
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Data")
	int32 RemainingMoves;

	// 점수 증가 메서드
	UFUNCTION(BlueprintCallable, Category = "Game Functions")
	void AddScore(int32 Points);

	// 남은 이동 횟수 감소 메서드
	UFUNCTION(BlueprintCallable, Category = "Game Functions")
	void DecreaseMoves();

	// 게임 상태 초기화 (레벨 시작 시 호출)
	UFUNCTION(BlueprintCallable, Category = "Game Function")
	void ResetGameState();
};
