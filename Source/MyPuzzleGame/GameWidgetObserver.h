// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Observer.h"

#include "GameWidgetObserver.generated.h"

/**
 * 
 */
UCLASS()
class MYPUZZLEGAME_API UGameWidgetObserver : public UUserWidget, public IObserver
{
	GENERATED_BODY()
	
private:
	// 현재 점수를 저장
	//int32 CurrentScore;

protected:
	// UI에서 바인딩된 TextBlock을 가져오기 위한 변수 선언
	// BindWidget 이노테이션을 사용하여 Blueprint의 위젯을 바인딩
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MovesText; // 남은 이동 횟수를 표시할 TextBlock

public:
	// 주체로부터 상태 변화를 수신할 때 호출되는 함수
	virtual void OnNotify_Implementation(int32 UpdateScore) override;

	// 남은 이동 횟수 업데이트 함수
	virtual void OnNotifyRemainingMoves_Implementation(int32 RemainingMoves) override;

	// 점수를 UI에 반영하는 함수 (블루프린트에서 구현 가능)
	UFUNCTION()
	void UpdateScoreUI(int32 NewScore);
};
