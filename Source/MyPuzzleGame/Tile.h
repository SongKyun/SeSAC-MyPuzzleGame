// 타일 개별 객체를 관리하는 클래스, 타일의 색상, 모양, 상태, 매칭 여부를 관리

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class MYPUZZLEGAME_API ATile : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ATile();

	// 타일이 선택되었는지 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	bool bIsSelected;

	// 타일을 선택 또는 해제하는 함수
	void SetSelected(bool bSelected);

	// 타일 외형
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile Properties")
	UStaticMeshComponent* TileMesh;

	// 타일 타입 정의
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Properties")
	FName TileType;

	// 타일의 스태틱메쉬 설정을 위한 TSubclassOf
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Properties")
	TMap<FName, UStaticMesh*> TileMeshes;

	// 타일 매칭 확인 함수
	bool IsMatching(ATile* OtherTile) const;

	// 타일의 외형을 TileType에 따라 설정하는 함수
	void UpdateTileAppearance();

	// 병렬 처리를 테스트 하는 함수
	void ProcessDataInParallel();
};
