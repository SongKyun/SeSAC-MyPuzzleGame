// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Observer.h"

#include "GameStateSubject.generated.h"

/**
 * ��ü Ŭ���� - ���¸� �����ϰ� ���� �� �������鿡�� �˸��� ����
 * �� Ŭ������ UObject�� ��ӹ޾� �𸮾� ������ �޸� ������ ���յ�
 */
UCLASS()
class MYPUZZLEGAME_API UGameStateSubject : public UObject
{
	GENERATED_BODY()

private:
	// ������ ����Ʈ : ��ϵ� ���������� ���� ��ȭ�� ������ - ����
	TArray <TScriptInterface<IObserver>> Observers;
	
	// ��ü�� ���� ���� ( ex : �÷��̾� ���� )
	//int32 PlayerScore;

public:
	// ������ : �ʱ� ���� ����
	//UGameStateSubject();

	// ������ ��� : ��ü�� ���� ��ȭ�� �˸� �������� �����
	void RegisterObserver(TScriptInterface<IObserver> Observer);

	// ������ ��� ���� : ���� ��ȭ �˸��� ������ �������� ������
	void UnregisterObserver(TScriptInterface<IObserver> Observer);

	// WorldContextObject�� �Ű������� �޾Ƽ� ó��
	void NotifyObservers(UObject* WorldContextObject);

	// ���� �̵� Ƚ�� ������ ���������� �˸�
	void NotifyObserversMoves(UObject* WorldContextObject);

	// ���� ��ȭ �߻� �� ��� ���������� �˸�
	//void NotifyObservers();

	// ����(����)�� �����ϴ� �Լ� ���°� ����Ǹ� NotifyObservers()�� ȣ���
	//void IncreaseScore(int32 Amount);

	// ���� ���� ��ȯ
	//int32 GetScore() const { return PlayerScore; }
};
