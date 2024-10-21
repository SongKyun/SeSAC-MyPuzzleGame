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

	// Ÿ���� ���õǾ����� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	bool bIsSelected;

	// Ÿ���� ���� �Ǵ� �����ϴ� �Լ�
	void SetSelected(bool bSelected);

	// Ÿ�� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile Properties")
	UStaticMeshComponent* TileMesh;

	// Ÿ�� Ÿ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Properties")
	FName TileType;

	// Ÿ���� ����ƽ�޽� ������ ���� TSubclassOf
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Properties")
	TMap<FName, UStaticMesh*> TileMeshes;

	// Ÿ�� ��Ī Ȯ�� �Լ�
	bool IsMatching(ATile* OtherTile) const;

	// Ÿ���� ������ TileType�� ���� �����ϴ� �Լ�
	void UpdateTileAppearance();

	// ���� ó���� �׽�Ʈ �ϴ� �Լ�
	void ProcessDataInParallel();
};
