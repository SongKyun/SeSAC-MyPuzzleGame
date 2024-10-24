// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateSubject.h"
#include "MyGameInstance.h"
#include "Kismet//GameplayStatics.h"

//UGameStateSubject::UGameStateSubject()
//{
//	 �ʱ� ���� ����
//	PlayerScore = 0;
//}

void UGameStateSubject::RegisterObserver(TScriptInterface<IObserver> Observer)
{
	// �������� ����Ʈ�� �߰�
	Observers.Add(Observer);
}

void UGameStateSubject::UnregisterObserver(TScriptInterface<IObserver> Observer)
{
	// �������� ����Ʈ���� ����
	Observers.Remove(Observer);
}

void UGameStateSubject::NotifyObservers(UObject* WorldContextObject)
{
	// ������ ����Ʈ���� ��ȿ���� ���� ������ ����
	Observers.RemoveAll([](const TScriptInterface<IObserver>& Observer)
		{
			if (!IsValid(Observer.GetObject()))
			{
				UE_LOG(LogTemp, Warning, TEXT("Invalid observer detected, removing from list"));
				return true; // ��ȿ���� ������ ����
			}
			return false; // ��ȿ�ϸ� ����
		});

	// WorldContextObject�� nullptr�� �ƴ��� Ȯ��
	if (!WorldContextObject)
	{
		UE_LOG(LogTemp, Error, TEXT("WorldContextObject is null"));
		return;
	}

	// GameInstance ��������
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));

	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get GameInstance from WorldContextObject"));
		return;
	}

	int32 CurrentScore = GameInstance->GetCurrentScore();

	// �������鿡�� ���� ������Ʈ �˸�
	for (const TScriptInterface<IObserver>& Observer : Observers)
	{
		if (IsValid(Observer.GetObject())
			&& Observer.GetObject()->GetClass()->ImplementsInterface(UObserver::StaticClass()))
		{
			// ���������� �˸�
			IObserver::Execute_OnNotify(Observer.GetObject(), CurrentScore);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid observer or interface not implemented"));
		}
	}


	//// ��ϵ� ��� �������鿡�� ���� ��ȭ�� �˸�
	//for (TScriptInterface<IObserver> Observer : Observers)
	//{
	//	// Observer ��ü�� ��ȿ�ϰ� IObserver �������̽��� �����ϰ� �ִ��� Ȯ��
	//	if (Observer.GetObject() && Observer.GetObject()->GetClass()->ImplementsInterface(UObserver::StaticClass()))
	//	{
	//		// �������� OnNoitfy �Լ� ȣ�� (���� ��ȭ�� ����)
	//		// �������� Ŭ���� �ν��Ͻ� -> �Լ��� ȣ��
	//		// �������̽� -> ȣ��, �������� Ȯ ������
	//		IObserver::Execute_OnNotify(Observer.GetObject(), PlayerScore);
	//	}
	//}
}

void UGameStateSubject::NotifyObserversMoves(UObject* WorldContextObject)
{
	Observers.RemoveAll([](const TScriptInterface<IObserver>& Observer)
		{
			return !IsValid(Observer.GetObject());
		});

	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));

	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get GameInstance"));
		return;
	}

	int32 RemainingMoves = GameInstance->GetRemainingMoves();

	for (const TScriptInterface<IObserver>& Observer : Observers)
	{
		if (IsValid(Observer.GetObject()) && Observer.GetObject()->GetClass()->ImplementsInterface(UObserver::StaticClass()))
		{
			IObserver::Execute_OnNotifyRemainingMoves(Observer.GetObject(), RemainingMoves);
		}
	}
}

//void UGameStateSubject::IncreaseScore(int32 Amount)
//{
//	// ������ ������Ű�� ���� ��ȭ�� �������鿡�� �˸�
//	PlayerScore += Amount;
//	NotifyObservers();
//}


