// Ÿ�� ���� ��ü�� �����ϴ� Ŭ����, Ÿ���� ����, ���, ����, ��Ī ���θ� ����

#include "Tile.h"
#include "Engine/Engine.h"
#include "Async/ParallelFor.h"

ATile::ATile()
{
	// Ÿ�� �޽� ������Ʈ ���� �� ����
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	RootComponent = TileMesh;

	// �޽� ������Ʈ�� ���� Ÿ�� Ÿ�� �ʱ�ȭ
	TileType = FName("Cube"); // �⺻ Ÿ�� Cube�� ���� (���߿� ����)

	bIsSelected = false; // ���� ���� �ʱ�ȭ
}

void ATile::SetSelected(bool bSelected)
{
	bIsSelected = bSelected;
	UpdateTileAppearance();
}

void ATile::BeginPlay()
{
	Super::BeginPlay();

	// Ÿ�� ���� ������Ʈ (TileType�� ���� �޽� ����)
	UpdateTileAppearance();
}

bool ATile::IsMatching(ATile* OtherTile) const
{
	// Ÿ�� Ÿ���� ��ġ�ϴ��� Ȯ��
	return TileType == OtherTile->TileType;
}

void ATile::UpdateTileAppearance()
{
	if (TileMeshes.Contains(TileType))
	{
		//TileType�� �´� Static Mesh�� ����
		TileMesh->SetStaticMesh(TileMeshes[TileType]);
	}
	else
	{
		// TileType�� �´� �޽ð� ������ �⺻ �޽ø� ����
		UE_LOG(LogTemp, Warning, TEXT("TileType %s has no Mesh set"), *TileType.ToString());
	}

	// ���õǾ��� ���� �ð��� �ǵ�� (���� ����)
	if (bIsSelected)
	{
		// Ÿ���� ���õǾ��� ���� ȿ��
		// �� : ���� ����
		if (UStaticMeshComponent* MeshComponent = FindComponentByClass<UStaticMeshComponent>())
		{
			MeshComponent->SetRenderCustomDepth(true); // ���õ� Ÿ���� ����
			MeshComponent->SetScalarParameterValueOnMaterials(TEXT("EmissiveStrength"), 10.0f); // ������ ���� ����
		}
	}
	else
	{
		if (UStaticMeshComponent* MeshComponent = FindComponentByClass<UStaticMeshComponent>())
		{
			MeshComponent->SetRenderCustomDepth(false); // �⺻ ���·� ����
			MeshComponent->SetScalarParameterValueOnMaterials(TEXT("EmissiveStrength"), 0.0f); // �⺻ ���� ����
		}
	}
}

void ATile::ProcessDataInParallel()
{
	TArray<int32> DataArray;
	DataArray.Init(0, 100);

	ParallelFor(DataArray.Num(), [&](int32 Index)
		{
			DataArray[Index] = Index * 2;

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Tile %d - %d"), Index, DataArray[Index]));
			}
		});

	UE_LOG(LogTemp, Warning, TEXT("ParallelFor Finish"));
}

