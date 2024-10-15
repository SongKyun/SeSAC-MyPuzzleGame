// 싱글톤 개념


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	// 초기 점수와 이동 횟수 설정
	PlayerScore = 0;
	RemainingMoves = 30;
}

void UMyGameInstance::AddScore(int32 Points)
{
	PlayerScore += Points;
}

void UMyGameInstance::DecreaseMoves()
{
	if (RemainingMoves > 0)
	{
		RemainingMoves--;
	}
}

void UMyGameInstance::ResetGameState()
{
	PlayerScore = 0;
	RemainingMoves = 30; // 게임 시작 시 초기화
}






