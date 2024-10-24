// �̱��� ����

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
	// �÷��̾� ����
	int32 PlayerScore;

	// ���� ����, ���� ��Ī Ƚ��
	int32 RemaingMoves;

	// Observer ��ü�� �����ϴ� ���� �߰�
	UGameStateSubject* GameStateSubjectInstance;

public:
	// ���� ���� �޼���
	UFUNCTION(BlueprintCallable, Category = "Game Functions")
	void AddScore(int32 Points);

	// ���� �̵� Ƚ�� ���� �޼���
	UFUNCTION(BlueprintCallable, Category = "Game Functions")
	void DecreaseMoves();

	// ���� ���� �ʱ�ȭ (���� ���� �� ȣ��)
	UFUNCTION(BlueprintCallable, Category = "Game Function")
	void ResetGameState();

	// ���� ������ �������� �Լ�
	int32 GetCurrentScore() const;

	// Observer ��ü�� �����ϴ� �Լ�
	void SetGameStateSubject(UGameStateSubject* Subject);

	int32 GetRemainingMoves() const; // ���� �̵� Ƚ�� ��ȯ
};
