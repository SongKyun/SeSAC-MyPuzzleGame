// �÷��̾� �Է� �޾� ��� ����, ����� ����� ����� �ǵ�����(Undo) ��� ����

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"

#include "APlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ATile;
class ATileGrid;

UCLASS()
class MYPUZZLEGAME_API AAPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAPlayerController();

protected:
	virtual void BeginPlay() override;

	// ���콺 Ŀ�� ���̱�
	virtual void SetupInputComponent() override;

	// ù ��°�� �� ��°�� ���õ� Ÿ���� ���� ������ ���� (GC ����)
	TWeakObjectPtr<ATile> FirstSelectedTile;
	TWeakObjectPtr<ATile> SecondSelectedTile;
	// TWeakObjectPtr �� ����ϸ� GC�� ������ ��ü�� üũ �����ϴ�.

	// TileGrid�� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	ATileGrid* TileGrid;

	// Input ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SelectTileAction;

	// Ÿ���� �����ϴ� �Լ�
	void SelectTile(const FInputActionValue& Value);

	// �� ���� Ÿ���� �����ϰ� ó���ϴ� �Լ�
	void ProcessSelectedTiles();

};
