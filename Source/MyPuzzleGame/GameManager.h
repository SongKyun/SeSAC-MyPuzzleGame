// �̱��� ���� ����
// ������ �������� ���� ����, ���� ����, ���� �̵� Ƚ�� ���� ���� ������ �����ϸ� �������� ���� ����

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
