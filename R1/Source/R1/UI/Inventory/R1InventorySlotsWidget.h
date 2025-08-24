

#pragma once

#include "CoreMinimal.h"
#include "UI/R1UserWidget.h"
#include "R1InventorySlotsWidget.generated.h"

class UR1InventorySlotWidget;
class UUniformGridPanel;

/**
 *
 */
UCLASS()
class R1_API UR1InventorySlotsWidget : public UR1UserWidget
{
	GENERATED_BODY()


public:
	UR1InventorySlotsWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TSubclassOf<UR1InventorySlotWidget> SlotWidgetClass;

	// 동적 생성된 SlotWidgetClass의 parent 역할
	UPROPERTY()
	TArray<TObjectPtr<UR1InventorySlotWidget>> SlotWidgets;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel_Slots;
};
