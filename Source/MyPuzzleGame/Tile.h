// Ÿ�� ���� ��ü�� �����ϴ� Ŭ����, Ÿ���� ����, ���, ����, ��Ī ���θ� ����

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM(BlueprintType)
enum class ETileColor : uint8
{
	// UMETA ��Ÿ�����͸� �߰��� �� ����ϴ� ��ũ���̴�.
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

	// Ÿ���� ����
	ETileColor TileColor;
	// ���� ���� ����
	void SetRandomColor();
	ETileColor GetTileColor() const;
};
