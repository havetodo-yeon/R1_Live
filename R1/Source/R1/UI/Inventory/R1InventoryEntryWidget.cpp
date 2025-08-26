


#include "UI/Inventory/R1InventoryEntryWidget.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "UI/Inventory/R1InventorySlotsWidget.h"
#include "Item/R1ItemInstance.h"
#include "UI/Item/Drag/R1DragDropOperation.h"
#include "UI/Item/Drag/R1ItemDragWidget.h"

UR1InventoryEntryWidget::UR1InventoryEntryWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UR1ItemDragWidget> FindDragWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Item/WBP_ItemDrag.WBP_ItemDrag_C'"));
	if (FindDragWidgetClass.Succeeded())	// 찾았으면 드래그 아이콘
	{
		DragWidgetClass = FindDragWidgetClass.Class;
	}
}

void UR1InventoryEntryWidget::Init(UR1InventorySlotsWidget* InSlotsWidget, UR1ItemInstance* InItemInstance, int32 InItemCount)
{
	SlotsWidget = InSlotsWidget;
	ItemInstance = InItemInstance;
	ItemCount = InItemCount;
}

void UR1InventoryEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Count->SetText(FText::GetEmpty());	// 아이템 개수(해당 강의에서는 개념만 두고 구현X
}

/** OnMouseEnter/Leave: 마우스를 갖다대면 Image_Hover **/
void UR1InventoryEntryWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	Image_Hover->SetRenderOpacity(1.f);
}

void UR1InventoryEntryWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	Image_Hover->SetRenderOpacity(0.f);
}

FReply UR1InventoryEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	// 옮기려는 자리에 아이템이 있을 경우 기존 아이템을 지우고 덮어쓰기
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);	// Drag 먼저 발생하도록
	}

	const FIntPoint UnitInventorySlotSize = FIntPoint(50, 50);	// 인벤토리 슬롯 사이즈

	// 몇 번째 슬롯을 클릭하고 있는 지 받아옴
	FVector2D MouseWidgetPos = SlotsWidget->GetCachedGeometry().AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	FVector2D ItemWidgetPos = SlotsWidget->GetCachedGeometry().AbsoluteToLocal(InGeometry.LocalToAbsolute(UnitInventorySlotSize / 2.f));
	FIntPoint ItemSlotPos = FIntPoint(ItemWidgetPos.X / UnitInventorySlotSize.X, ItemWidgetPos.Y / UnitInventorySlotSize.Y);

	CachedFromSlotPos = ItemSlotPos;
	CachedDeltaWidgetPos = MouseWidgetPos - ItemWidgetPos;

	return Reply;
}

void UR1InventoryEntryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UR1ItemDragWidget* DragWidget = CreateWidget<UR1ItemDragWidget>(GetOwningPlayer(), DragWidgetClass);
	FVector2D EntityWidgetSize = FVector2D(1 * 50, 1 * 50);	// TEMP: 모든 아이템은 한 칸 짜리
	DragWidget->Init(EntityWidgetSize, nullptr, ItemCount);

	// 드래그 할 때 그려지는 정보
	UR1DragDropOperation* DragDrop = NewObject<UR1DragDropOperation>();
	DragDrop->DefaultDragVisual = DragWidget;
	DragDrop->Pivot = EDragPivot::MouseDown;
	DragDrop->FromItemSlotPos = CachedFromSlotPos;
	DragDrop->ItemInstance = ItemInstance;
	DragDrop->DeltaWidgetPos = CachedDeltaWidgetPos;

	OutOperation = DragDrop;
}

void UR1InventoryEntryWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	RefreshWidgetOpacity(true);
}

void UR1InventoryEntryWidget::RefreshWidgetOpacity(bool bClearlyVisible)
{
	SetRenderOpacity(bClearlyVisible ? 1.f : 0.5f);
}

void UR1InventoryEntryWidget::RefreshItemCount(int32 NewItemCount)
{
	ItemCount = NewItemCount;
	Text_Count->SetText((ItemCount >= 2) ? FText::AsNumber(ItemCount) : FText::GetEmpty());
}