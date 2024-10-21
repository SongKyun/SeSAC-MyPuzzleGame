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
	int32 CurrentScore;

public:
	// ��ü�κ��� ���� ��ȭ�� ������ �� ȣ��Ǵ� �Լ�
	virtual void OnNotify_Implementation(int32 UpdateScore) override;

	// ������ UI�� �ݿ��ϴ� �Լ� (�������Ʈ���� ���� ����)
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void UpdateScoreUI();
};
