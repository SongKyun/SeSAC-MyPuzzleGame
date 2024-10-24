// 싱글톤 개념


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	// 초기 점수와 이동 횟수 설정
	PlayerScore = 0;
	RemaingMoves = 30;
	GameStateSubjectInstance = nullptr;
}

void UMyGameInstance::AddScore(int32 Points)
{
	PlayerScore += Points;

	// 점수 변경 시 Observer에게 알림
	if (GameStateSubjectInstance)
	{
		GameStateSubjectInstance->NotifyObservers(GetWorld()); // 점수 변경 시 알림
	}
}

void UMyGameInstance::DecreaseMoves()
{
	if (RemaingMoves > 0)
	{
		RemaingMoves--;

		if (GameStateSubjectInstance)
		{
			GameStateSubjectInstance->NotifyObserversMoves(this);
		}
	}
}

void UMyGameInstance::ResetGameState()
{
	PlayerScore = 0;
	RemaingMoves = 30; // 게임 시작 시 초기화
}

int32 UMyGameInstance::GetCurrentScore() const
{
	return PlayerScore;
}

void UMyGameInstance::SetGameStateSubject(UGameStateSubject* Subject)
{
	GameStateSubjectInstance = Subject;
}

int32 UMyGameInstance::GetRemainingMoves() const
{
	return RemaingMoves;
}
