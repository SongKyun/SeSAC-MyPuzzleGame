// �̱��� ����


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	// �ʱ� ������ �̵� Ƚ�� ����
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
	RemainingMoves = 30; // ���� ���� �� �ʱ�ȭ
}






