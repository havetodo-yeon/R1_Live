

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "R1DragDropOperation.generated.h"

class UR1ItemInstance;

/**
 * 드래깅이 일어났을 때 그 정보를 캐싱해서 가지고 있는 용도
 */
UCLASS()
class R1_API UR1DragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UR1DragDropOperation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	FIntPoint FromItemSlotPos = FIntPoint::ZeroValue;	// 원래 위치

	UPROPERTY()
	TObjectPtr<UR1ItemInstance> ItemInstance;

	FVector2D DeltaWidgetPos = FVector2D::ZeroVector;

};
