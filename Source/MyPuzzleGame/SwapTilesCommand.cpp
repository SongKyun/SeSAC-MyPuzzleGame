// Fill out your copyright notice in the Description page of Project Settings.


#include "SwapTilesCommand.h"
#include "Tile.h"
#include "TileGrid.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USwapTilesCommand::Initialize(ATile* InFirstTile, ATile* InSecondTile)
{
	FirstTile = InFirstTile;
	SecondTile = InSecondTile;

	// ���� ��ġ�� ����
	FirstTileOriginalLocation = FirstTile->GetActorLocation();
	SecondTileOriginalLocation = SecondTile->GetActorLocation();
}

void USwapTilesCommand::Execute()
{

	// Ÿ�� �׸��� �������� (FirstTile�� �Ҽ� �׸���)
	ATileGrid* TileGrid = FirstTile->TileGrid;

	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(TileGrid->GetWorld()));
	if (GameInstance)
	{
		GameInstance->DecreaseMoves(); // ���� �� �̵� Ƚ�� ����
	}

	// ��ȿ�� Ȯ��
	if (!FirstTile || !SecondTile)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Tiles for swapping"));
		return;
	}

	// �׸��尡 ��ȿ���� Ȯ��
	if (!TileGrid)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Grid"));
		return;
	}
	
	// �׸��� ������ Ÿ���� ��ȯ
	TileGrid->SwapTiles(FirstTile, SecondTile);

	// Ÿ�� ��ȯ �� ��Ī Ȯ��
	TArray<ATile*> MatchingTiles = TileGrid->CheckForMatches();
	if (MatchingTiles.Num() > 0) // ��Ī�� ���� ���
	{
		TileGrid->RemoveMatchingTiles(MatchingTiles); // ��Ī Ÿ�� ����
	}
	else // ��Ī�� ���� ���
	{
		Undo(); // Ÿ�� ���� ��ġ�� �ǵ���
	}

	/*
	// �� Ÿ���� ��ġ�� ���� ��ȯ (���� ��ǥ)
	FirstTile->SetActorLocation(SecondTileOriginalLocation);
	SecondTile->SetActorLocation(FirstTileOriginalLocation);

	// �׸��� ��ǥ�� �Բ� ��ȯ
	FVector2D TempPosition = FirstTile->TilePosition;
	FirstTile->UpdateTilePosition(SecondTile->TilePosition);
	SecondTile->UpdateTilePosition(TempPosition);

	// TODO :: ��Ī Ȯ�� ���� ����
	*/
}

void USwapTilesCommand::Undo()
{
	// Ÿ���� ��ġ�� ������� �ǵ��� (���� ��ǥ)
	FirstTile->SetActorLocation(FirstTileOriginalLocation);
	SecondTile->SetActorLocation(SecondTileOriginalLocation);

	// �׸��� ��ǥ�� ������� �ǵ���
	FVector2D TempPosition = FirstTile->TilePosition;
	FirstTile->UpdateTilePosition(SecondTile->TilePosition);
	SecondTile->UpdateTilePosition(TempPosition);

	// �׸��� �迭 ������Ʈ
	ATileGrid* TileGrid = FirstTile->TileGrid;
	if (TileGrid)
	{
		int32 X1, Y1, X2, Y2;
		if (TileGrid->GetTileGridPosition(FirstTile, X1, Y1) && TileGrid->GetTileGridPosition(SecondTile, X2, Y2))
		{
			TileGrid->SetTileAt(X1, Y1, FirstTile);
			TileGrid->SetTileAt(X2, Y2, SecondTile);
		}
	}
}