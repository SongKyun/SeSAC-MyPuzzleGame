// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateSubject.h"

UGameStateSubject::UGameStateSubject()
{
	// �ʱ� ���� ����
	PlayerScore = 0;
}

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

void UGameStateSubject::NotifyObservers()
{
	// ��ϵ� ��� �������鿡�� ���� ��ȭ�� �˸�
	for (TScriptInterface<IObserver> Observer : Observers)
	{
		// Observer ��ü�� ��ȿ�ϰ� IObserver �������̽��� �����ϰ� �ִ��� Ȯ��
		if (Observer.GetObject() && Observer.GetObject()->GetClass()->ImplementsInterface(UObserver::StaticClass()))
		{
			// �������� OnNoitfy �Լ� ȣ�� (���� ��ȭ�� ����)
			// �������� Ŭ���� �ν��Ͻ� -> �Լ��� ȣ��
			// �������̽� -> ȣ��, �������� Ȯ ������
			IObserver::Execute_OnNotify(Observer.GetObject(), PlayerScore);
		}
	}
}

void UGameStateSubject::IncreaseScore(int32 Amount)
{
	// ������ ������Ű�� ���� ��ȭ�� �������鿡�� �˸�
	PlayerScore += Amount;
	NotifyObservers();
}


