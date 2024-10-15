// �̱��� ����

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
	// ���� ���� ���� ������

	// �÷��̾� ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Data")
	int32 PlayerScore;

	// ���� �̵� Ƚ��
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Data")
	int32 RemainingMoves;

	// ���� ���� �޼���
	UFUNCTION(BlueprintCallable, Category = "Game Functions")
	void AddScore(int32 Points);

	// ���� �̵� Ƚ�� ���� �޼���
	UFUNCTION(BlueprintCallable, Category = "Game Functions")
	void DecreaseMoves();

	// ���� ���� �ʱ�ȭ (���� ���� �� ȣ��)
	UFUNCTION(BlueprintCallable, Category = "Game Function")
	void ResetGameState();
};
