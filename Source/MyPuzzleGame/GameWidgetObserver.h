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
	// ���� ������ ����
	//int32 CurrentScore;

protected:
	// UI���� ���ε��� TextBlock�� �������� ���� ���� ����
	// BindWidget �̳����̼��� ����Ͽ� Blueprint�� ������ ���ε�
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MovesText; // ���� �̵� Ƚ���� ǥ���� TextBlock

public:
	// ��ü�κ��� ���� ��ȭ�� ������ �� ȣ��Ǵ� �Լ�
	virtual void OnNotify_Implementation(int32 UpdateScore) override;

	// ���� �̵� Ƚ�� ������Ʈ �Լ�
	virtual void OnNotifyRemainingMoves_Implementation(int32 RemainingMoves) override;

	// ������ UI�� �ݿ��ϴ� �Լ� (�������Ʈ���� ���� ����)
	UFUNCTION()
	void UpdateScoreUI(int32 NewScore);
};
