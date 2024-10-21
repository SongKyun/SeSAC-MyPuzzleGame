// Ÿ�ϵ��� �׸��带 �����ϰ�, Ÿ�� ����, Ÿ�� ��Ī Ž��, Ÿ�� �̵��� ó���ϴ� ������ ���

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

	// �׸��� ũ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Grid")
	int32 GridWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Grid")
	int32 GridHeight;
	
	// Ÿ�� ���� ��ġ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Grid")
	float TileSpacing;

	// Ÿ���� ������ Blueprint Ŭ������ ������ �� �ֵ��� TSubclassOf ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Tile Grid")
	TSubclassOf<ATile> TileClass; // TileClass�� ���忡 ��ġ�� TileGrid���� ������ �� ����

	// Ÿ���� 1���� �迭�� ����
	UPROPERTY()
	TArray<ATile*> TileArray;

	// �׸��� �ʱ�ȭ �Լ�
	void InitializeGrid();

	// Ư�� ��ġ�� Ÿ���� ��� �Լ�
	ATile* GetTileAt(int32 x, int32 y) const;

	// Ư�� ��ġ�� Ÿ���� �����ϴ� �Լ�
	void SetTileAt(int32 x, int32 y, ATile* Tile);

};
