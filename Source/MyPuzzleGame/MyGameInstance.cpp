// �̱��� ����


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	// �ʱ� ������ �̵� Ƚ�� ����
	PlayerScore = 0;
	RemaingMoves = 30;
	GameStateSubjectInstance = nullptr;
}

void UMyGameInstance::AddScore(int32 Points)
{
	PlayerScore += Points;

	// ���� ���� �� Observer���� �˸�
	if (GameStateSubjectInstance)
	{
		GameStateSubjectInstance->NotifyObservers(GetWorld()); // ���� ���� �� �˸�
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
	RemaingMoves = 30; // ���� ���� �� �ʱ�ȭ
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
