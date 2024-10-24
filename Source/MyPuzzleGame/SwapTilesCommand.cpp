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

	// 원래 위치를 저장
	FirstTileOriginalLocation = FirstTile->GetActorLocation();
	SecondTileOriginalLocation = SecondTile->GetActorLocation();
}

void USwapTilesCommand::Execute()
{

	// 타일 그리드 가져오기 (FirstTile의 소속 그리드)
	ATileGrid* TileGrid = FirstTile->TileGrid;

	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(TileGrid->GetWorld()));
	if (GameInstance)
	{
		GameInstance->DecreaseMoves(); // 스왑 시 이동 횟수 차감
	}

	// 유효성 확인
	if (!FirstTile || !SecondTile)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Tiles for swapping"));
		return;
	}

	// 그리드가 유효한지 확인
	if (!TileGrid)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Grid"));
		return;
	}
	
	// 그리드 내에서 타일을 교환
	TileGrid->SwapTiles(FirstTile, SecondTile);

	// 타일 교환 후 매칭 확인
	TArray<ATile*> MatchingTiles = TileGrid->CheckForMatches();
	if (MatchingTiles.Num() > 0) // 매칭이 있을 경우
	{
		TileGrid->RemoveMatchingTiles(MatchingTiles); // 매칭 타일 삭제
	}
	else // 매칭이 없을 경우
	{
		Undo(); // 타일 원래 위치로 되돌림
	}

	/*
	// 두 타일의 위치를 서로 교환 (월드 좌표)
	FirstTile->SetActorLocation(SecondTileOriginalLocation);
	SecondTile->SetActorLocation(FirstTileOriginalLocation);

	// 그리드 좌표도 함께 교환
	FVector2D TempPosition = FirstTile->TilePosition;
	FirstTile->UpdateTilePosition(SecondTile->TilePosition);
	SecondTile->UpdateTilePosition(TempPosition);

	// TODO :: 매칭 확인 등의 로직
	*/
}

void USwapTilesCommand::Undo()
{
	// 타일의 위치를 원래대로 되돌림 (월드 좌표)
	FirstTile->SetActorLocation(FirstTileOriginalLocation);
	SecondTile->SetActorLocation(SecondTileOriginalLocation);

	// 그리드 좌표도 원래대로 되돌림
	FVector2D TempPosition = FirstTile->TilePosition;
	FirstTile->UpdateTilePosition(SecondTile->TilePosition);
	SecondTile->UpdateTilePosition(TempPosition);

	// 그리드 배열 업데이트
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