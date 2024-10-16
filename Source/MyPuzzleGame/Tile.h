// Ÿ�� ���� ��ü�� �����ϴ� Ŭ����, Ÿ���� ����, ���, ����, ��Ī ���θ� ����

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	UStaticMeshComponent* TileMesh;

	// Ÿ���� ���� �Ǵ� ����� �����ϴ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Properties")
	FName TileType;

	// Ÿ�� ��Ī Ȯ�� �Լ�
	bool IsMatching(ATile* OtherTile);
};
