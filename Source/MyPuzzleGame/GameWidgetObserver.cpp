// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidgetObserver.h"

void UGameWidgetObserver::OnNotify_Implementation(int32 UpdateScore)
{
	// ��ü�κ��� ���ο� ������ �޾Ƽ� CurrentScore�� ������Ʈ
	CurrentScore = UpdateScore;

	// UI ������Ʈ (�������Ʈ���� ���� ����)
	UpdateScoreUI();
}
