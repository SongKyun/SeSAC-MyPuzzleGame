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

		// UI ������ ���� �ݿ� (�� : ���� �ؽ�Ʈ ������Ʈ )
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

//��� ����Ʈ �� �������� �ϴ� �ּ� ó��
void UGameWidgetObserver::UpdateScoreUI(int32 NewScore)
{
	// ScoreText�� ���ε��Ǿ� �ִ��� Ȯ��
	if (ScoreText)
	{
		// TextBlock�� ������ ������Ʈ
		ScoreText->SetText(FText::AsNumber(NewScore));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ScoreText is not bound to the widget"));
	}
}

