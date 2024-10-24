// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidgetObserver.h"
#include "MyGameInstance.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameWidgetObserver::OnNotify_Implementation(int32 UpdateScore)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		int32 CurrentScore = MyGameInstance->GetCurrentScore();

		// UI 위젯에 점수 반영 (예 : 점수 텍스트 업데이트 )
		UpdateScoreUI(CurrentScore);
	}
}

void UGameWidgetObserver::OnNotifyRemainingMoves_Implementation(int32 RemainingMoves)
{
	if (MovesText)
	{
		MovesText->SetText(FText::AsNumber(RemainingMoves));
	}
}

//블루 프린트 실 구현으로 일단 주석 처리
void UGameWidgetObserver::UpdateScoreUI(int32 NewScore)
{
	// ScoreText가 바인딩되어 있는지 확인
	if (ScoreText)
	{
		// TextBlock의 내용을 업데이트
		ScoreText->SetText(FText::AsNumber(NewScore));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ScoreText is not bound to the widget"));
	}
}

