// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Observer.generated.h"

// �� Ŭ������ UCLASS�� �ƴ� UINTERFACE�� �����Ͽ� �������̽��� ����
UINTERFACE(MinimalAPI)
class UObserver : public UInterface
{
	GENERATED_BODY()
};

/**
* IObserver �������̽� ����
* ��� ���������� �� �������̽��� �����Ͽ� ��ü�κ��� ���� ��ȭ�� ������
*/
class MYPUZZLEGAME_API IObserver
{
	GENERATED_BODY()


public:
	// ��ü�κ��� ���� ��ȭ�� �����ϴ� �Լ�
	// BlueprintNativeEvent�� ���ǵǾ�, C++ �Ǵ� �������Ʈ���� ���� ����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Observer")
	void OnNotify(int32 UpdatedScore);

	// ���� �̵� Ƚ�� �˸� �Լ� �߰�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Observer")
	void OnNotifyRemainingMoves(int32 RemainingMoves);
};
