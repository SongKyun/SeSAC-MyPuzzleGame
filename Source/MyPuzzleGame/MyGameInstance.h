// 싱글톤 개념

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameStateSubject.h"

#include "MyGameInstance.generated.h"

UCLASS()
class MYPUZZLEGAME_API UMyGameInstance : public UGameInstance
{
	UMyGameInstance();
	
	GENERATED_BODY()
	
private:
	// 플레이어 점수
	int32 PlayerScore;

	// 게임 진행, 남은 매칭 횟수
	int32 RemaingMoves;

	// Observer 주체를 참조하는 변수 추가
	UGameStateSubject* GameStateSubjectInstance;

public:
	// 점수 증가 메서드
	UFUNCTION(BlueprintCallable, Category = "Game Functions")
	void AddScore(int32 Points);

	// 남은 이동 횟수 감소 메서드
	UFUNCTION(BlueprintCallable, Category = "Game Functions")
	void DecreaseMoves();

	// 게임 상태 초기화 (레벨 시작 시 호출)
	UFUNCTION(BlueprintCallable, Category = "Game Function")
	void ResetGameState();

	// 현재 점수를 가져오는 함수
	int32 GetCurrentScore() const;

	// Observer 주체를 설정하는 함수
	void SetGameStateSubject(UGameStateSubject* Subject);

	int32 GetRemainingMoves() const; // 남은 이동 횟수 반환
};
