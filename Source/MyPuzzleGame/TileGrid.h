// 타일들의 그리드를 관리하고, 타일 생성, 타일 매칭 탐색, 타일 이동을 처리하는 역할을 담당

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileGrid.generated.h"

UCLASS()
class MYPUZZLEGAME_API ATileGrid : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ATileGrid();

	// 그리드 크기
	int32 GridSize;
	// 그리드의 타일들
	TArray<class ATile*> Tiles;
	// 그리드 생성 함수
	void CreateGrid(int32 Size);

};
