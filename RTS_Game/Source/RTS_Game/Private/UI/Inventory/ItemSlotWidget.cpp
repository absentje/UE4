// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/Inventory/ItemSlotWidget.h"
#include "UI/Inventory/ItemDrag.h"
#include "UI/Inventory/DraggedItem.h"
#include "UI/WidgetDrag.h"

#include "RTS_PlayerController.h"
#include "RTS_FunctionLibrary.h"
#include "DataAssets/Items.h"

#include "Components/EditableTextBox.h"
#include "Components/OverlaySlot.h"
#include "Components/SizeBox.h"
#include "Components/Overlay.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"

UItemSlotWidget::UItemSlotWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}


void UItemSlotWidget::NativeConstruct() {
	RTS_PlayerController = Cast<ARTS_PlayerController>(GetOwningPlayer());
	
	CountOfItem_TextBox = NewObject<UEditableTextBox>();
	CountOfItem_TextBox->IsReadOnly = true;
	CountOfItem_TextBox->SetVisibility(ESlateVisibility::HitTestInvisible);

	ImageOfItem = NewObject<UImage>();
	currentImage_Texture2D = nullptr;
	Super::NativeConstruct();
}


bool UItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry,
	const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::OnDrop(InGeometry, InDragDropEvent, InOperation);
	if (!RTS_PlayerController) return false;

	RTS_PlayerController->SetInputMode_GameAndUI();

	if (auto ItemDrag_ = Cast<UItemDrag>(InOperation)) {
		DroppedItemSlotWidget(InGeometry, InDragDropEvent, ItemDrag_);
		return true;
	}
	return true; // ??
}

void UItemSlotWidget::NativeOnDragCancelled(const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
	URTS_FunctionLibrary::PrintMessage("UItemSlotWidget::NativeOnDragCancelled(...) called");
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	if (!RTS_PlayerController) return;

	RTS_PlayerController->SetInputMode_GameAndUI();
}

bool UItemSlotWidget::DroppedWidget(const FGeometry& InGeometry,
	const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	// need to define
	//	*
	//
	return true;
}

void UItemSlotWidget::DroppedItemSlotWidget(const FGeometry& InGeometry,
	const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{

}

void UItemSlotWidget::SlotChanged() {
	if (!IsEmpty()) {
		RefreshImageOfItem();
		RefreshCountOfItem();
	}
	else {
		ImageOfItem->SetVisibility(ESlateVisibility::Hidden);
		CountOfItem_TextBox->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool UItemSlotWidget::IsEmpty() const {
	static const int32 COUNT_OF_ITEMS = (int32)URTS_FunctionLibrary::GetItemsInfo().Num();

	if (InventorySlot.Count	 > 0	&&
		InventorySlot.ItemId > 0	&&
		InventorySlot.ItemId < COUNT_OF_ITEMS)
		return false;
	// if empty - clear unuseful info of item
	const_cast<UItemSlotWidget*>(this)->InvSlotClear();
	return true;
}

void UItemSlotWidget::SetTextToInformationBar()
{
}

void UItemSlotWidget::InvSlotClear() {
	InventorySlot.Count = 0;
	InventorySlot.ItemId = 0;
}

void UItemSlotWidget::RefreshImageOfItem() {
	auto& ItemInfo = URTS_FunctionLibrary::GetItemsInfo()[InventorySlot.ItemId];
	if (ImageOfItem) {
		currentImage_Texture2D = ItemInfo.PictureOfItem;
		ImageOfItem->SetBrushFromTexture(ItemInfo.PictureOfItem, true);
		ImageOfItem->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else {
		currentImage_Texture2D = nullptr;
	}
}

void UItemSlotWidget::RefreshCountOfItem() {
	if (CountOfItem_TextBox) {
		const int COUNT_OF_ITEM = InventorySlot.Count;
		if (COUNT_OF_ITEM > 1) {
			CountOfItem_TextBox->SetText(FText::FromString(FString::FromInt(COUNT_OF_ITEM)));
			CountOfItem_TextBox->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
		else {
			CountOfItem_TextBox->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	RTS_PlayerController->SetInputMode_UI_Only();
	OutOperation = CreateItemDrag();
}

FReply UItemSlotWidget::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	SetTextToInformationBar();
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
		reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}
	return reply;
}

UDragDropOperation* UItemSlotWidget::CreateItemDrag() const {
	auto drag_drop_operation = NewObject<UItemDrag>();
	if (RTS_PlayerController && !IsEmpty()) {
		RTS_PlayerController->DragDropOp_property = drag_drop_operation; // for garbage collector
		drag_drop_operation->DraggedItem = const_cast<UItemSlotWidget*>(this);
		drag_drop_operation->ItemImage = currentImage_Texture2D;

		auto DragVisual = CreateWidget<UDraggedItem>(RTS_PlayerController, URTS_FunctionLibrary::GetClassPtrOf_DraggedItem_BP());
		DragVisual->ImageOfDraggedItem = NewObject<UImage>();
		DragVisual->ImageOfDraggedItem->SetBrushFromTexture(currentImage_Texture2D);

		drag_drop_operation->DefaultDragVisual = DragVisual;
		drag_drop_operation->Pivot = EDragPivot::MouseDown;
	}
	return drag_drop_operation;
}