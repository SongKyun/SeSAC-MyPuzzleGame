// 플레이어 입력 받아 명령 실행, 실행된 명령을 기록해 되돌리기(Undo) 기능 제공

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

	// 마우스 커서 보이기
	virtual void SetupInputComponent() override;

	// 첫 번째와 두 번째로 선택된 타일을 약한 참조로 저장 (GC 대응)
	TWeakObjectPtr<ATile> FirstSelectedTile;
	TWeakObjectPtr<ATile> SecondSelectedTile;
	// TWeakObjectPtr 를 사용하면 GC로 삭제된 객체를 체크 가능하다.

	// TileGrid에 대한 참조
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	ATileGrid* TileGrid;

	// Input 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SelectTileAction;

	// 타일을 선택하는 함수
	void SelectTile(const FInputActionValue& Value);

	// 두 개의 타일을 선택하고 처리하는 함수
	void ProcessSelectedTiles();

};
