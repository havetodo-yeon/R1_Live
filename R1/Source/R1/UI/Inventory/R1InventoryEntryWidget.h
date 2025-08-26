

#pragma once

#include "CoreMinimal.h"
#include "UI/R1UserWidget.h"
#include "R1InventoryEntryWidget.generated.h"

class USizeBox;
class UTextBlock;
class UImage;
class UR1InventorySlotsWidget;
class UR1ItemInstance;
class UR1ItemDragWidget;

/**
 * 
 */
UCLASS()
class R1_API UR1InventoryEntryWidget : public UR1UserWidget
{
	GENERATED_BODY()
	
public:
	UR1InventoryEntryWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	// 슬롯, 아이템 개수 등을 받아서 가지고 있는 초기화 함수
	void Init(UR1InventorySlotsWidget* InSlotsWidget, UR1ItemInstance* InItemInstance, int32 InItemCount);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void RefreshWidgetOpacity(bool bClearlyVisible);	// Visibility 따라서 Opacity 조절하는 부분
	void RefreshItemCount(int32 NewItemCount);	// ItemCount 따라서 세팅하는 부분

private:
	FIntPoint CachedFromSlotPos = FIntPoint::ZeroValue;	// int를 두 개로 묶어서 사용하는 개념
	FVector2D CachedDeltaWidgetPos = FVector2D::ZeroVector;
	int32 ItemCount = 0;

protected:
	UPROPERTY()
	TObjectPtr<UR1InventorySlotsWidget> SlotsWidget;	// Inventory Slots 위에 그려줌

	UPROPERTY()
	TObjectPtr<UR1ItemInstance> ItemInstance;	// 아이템에 대한 정보

	UPROPERTY()
	TSubclassOf<UR1ItemDragWidget> DragWidgetClass;	// 드래그 할 때 어떤 위젯으로 보여주고 싶은 지 연결

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;	// 크기 지정

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Count;	// 아이템 개수(해당 강의에서는 개념만 두고 구현X)

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;	// 이미지 아이콘

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Hover;	// 갖다 댔을 때 어떤 이미지로 떠야 하는 지

};
