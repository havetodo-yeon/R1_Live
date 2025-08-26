

#pragma once

#include "CoreMinimal.h"
#include "UI/R1UserWidget.h"
#include "R1InventorySlotsWidget.generated.h"

class UR1InventorySlotWidget;
class UUniformGridPanel;

class UR1InventoryEntryWidget;
class UR1ItemInstance;
class UCanvasPanel;

/**
 *
 */
UCLASS()
class R1_API UR1InventorySlotsWidget : public UR1UserWidget
{
	GENERATED_BODY()	// 옮기려는 자리에 아이템이 있을 경우 기존 아이템을 지우고 덮어쓰기


public:
	UR1InventorySlotsWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

	void OnInventoryEntryChanged(const FIntPoint& ItemSlotPos, TObjectPtr<UR1ItemInstance> Item);	// 배열에서 아이템 위치 변경 시: 삭제 후 새로운 자리에 추가

	// Item Drag 관련
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:
	void FinishDrag();

protected:
	UPROPERTY()
	TSubclassOf<UR1InventorySlotWidget> SlotWidgetClass;

	// 동적 생성된 SlotWidgetClass의 parent 역할
	UPROPERTY()
	TArray<TObjectPtr<UR1InventorySlotWidget>> SlotWidgets;

	UPROPERTY()
	TSubclassOf<UR1InventoryEntryWidget> EntryWidgetClass;	// 동적 생성 

	UPROPERTY()
	TArray<TObjectPtr<UR1InventoryEntryWidget>> EntryWidgets;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel_Slots;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel_Entries;

private:
	FIntPoint PrevDragOverSlotPos = FIntPoint(-1, -1);
	const int X_COUNT = 10;
	const int Y_COUNT = 5;
};