// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateSubject.h"
#include "MyGameInstance.h"
#include "Kismet//GameplayStatics.h"

//UGameStateSubject::UGameStateSubject()
//{
//	 초기 점수 설정
//	PlayerScore = 0;
//}

void UGameStateSubject::RegisterObserver(TScriptInterface<IObserver> Observer)
{
	// 옵저버를 리스트에 추가
	Observers.Add(Observer);
}

void UGameStateSubject::UnregisterObserver(TScriptInterface<IObserver> Observer)
{
	// 옵저버를 리스트에서 제거
	Observers.Remove(Observer);
}

void UGameStateSubject::NotifyObservers(UObject* WorldContextObject)
{
	// 옵저버 리스트에서 유효하지 않은 옵저버 제거
	Observers.RemoveAll([](const TScriptInterface<IObserver>& Observer)
		{
			if (!IsValid(Observer.GetObject()))
			{
				UE_LOG(LogTemp, Warning, TEXT("Invalid observer detected, removing from list"));
				return true; // 유효하지 않으면 제거
			}
			return false; // 유효하면 유지
		});

	// WorldContextObject가 nullptr이 아닌지 확인
	if (!WorldContextObject)
	{
		UE_LOG(LogTemp, Error, TEXT("WorldContextObject is null"));
		return;
	}

	// GameInstance 가져오기
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));

	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get GameInstance from WorldContextObject"));
		return;
	}

	int32 CurrentScore = GameInstance->GetCurrentScore();

	// 옵저버들에게 점수 업데이트 알림
	for (const TScriptInterface<IObserver>& Observer : Observers)
	{
		if (IsValid(Observer.GetObject())
			&& Observer.GetObject()->GetClass()->ImplementsInterface(UObserver::StaticClass()))
		{
			// 옵저버에게 알림
			IObserver::Execute_OnNotify(Observer.GetObject(), CurrentScore);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid observer or interface not implemented"));
		}
	}


	//// 등록된 모든 옵저버들에게 상태 변화를 알림
	//for (TScriptInterface<IObserver> Observer : Observers)
	//{
	//	// Observer 객체가 유효하고 IObserver 인터페이스를 구현하고 있는지 확인
	//	if (Observer.GetObject() && Observer.GetObject()->GetClass()->ImplementsInterface(UObserver::StaticClass()))
	//	{
	//		// 옵저버의 OnNoitfy 함수 호출 (점수 변화를 전달)
	//		// 실질적인 클래스 인스턴스 -> 함수를 호출
	//		// 인터페이스 -> 호출, 의존성이 확 낮아짐
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
//	// 점수를 증가시키고 상태 변화를 옵저버들에게 알림
//	PlayerScore += Amount;
//	NotifyObservers();
//}


