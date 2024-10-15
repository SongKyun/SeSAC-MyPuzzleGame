// 타일 개별 객체를 관리하는 클래스, 타일의 색상, 모양, 상태, 매칭 여부를 관리

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM(BlueprintType)
enum class ETileColor : uint8
{
	// UMETA 메타데이터를 추가할 때 사용하는 매크로이다.
	Red UMETA(DisplayName = "Red"),
	Green UMETA(DisplayName = "Green"),
	Blue UMETA(DisplayName = "Blue"),
	Yellow UMETA(DisplayName = "Yellow")
};

UCLASS()
class MYPUZZLEGAME_API ATile : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ATile();

	// 타일의 색상
	ETileColor TileColor;
	// 랜덤 색상 설정
	void SetRandomColor();
	ETileColor GetTileColor() const;
};
