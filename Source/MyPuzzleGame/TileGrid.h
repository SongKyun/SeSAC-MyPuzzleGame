// 타일들의 그리드를 관리하고, 타일 생성, 타일 매칭 탐색, 타일 이동을 처리하는 역할을 담당

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileGrid.generated.h"

class ATile;
UCLASS()
class MYPUZZLEGAME_API ATileGrid : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ATileGrid();

	// 그리드 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Grid")
	int32 GridWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Grid")
	int32 GridHeight;
	
	// 타일을 1차원 배열로 관리
	UPROPERTY()
	TArray<ATile*> TileArray;

	// 그리드 초기화 함수
	void InitializeGrid();

	// 특정 위치의 타일을 얻는 함수
	ATile* GetTileAt(int32 x, int32 y) const;

	// 특정 위치의 타일을 설정하는 함수
	void SetTileAt(int32 x, int32 y, ATile* Tile);

};
