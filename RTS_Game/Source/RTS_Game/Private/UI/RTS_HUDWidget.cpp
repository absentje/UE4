// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/RTS_HUDWidget.h"
#include "RTS_PlayerController.h"
#include "UI/Inventory/ItemDrag.h"
#include "UI/WidgetDrag.h"
//#include "ActionSlot.h"


URTS_HUDWidget::URTS_HUDWidget(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
	RTS_PlayerController = Cast<ARTS_PlayerController>(GetOwningPlayer());
	if (auto world_ = GetWorld()) {
		
	}
}

bool URTS_HUDWidget::NativeOnDrop(
	const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::OnDrop(InGeometry, InDragDropEvent, InOperation);
	if (!RTS_PlayerController) return false;

	RTS_PlayerController->SetInputMode_GameAndUI();

	if (auto WidgetDrag_ = Cast<UWidgetDrag>(InOperation)) {
		return DroppedWidget(InGeometry, InDragDropEvent, WidgetDrag_);
	}

//	if (auto ItemDrag_ = Cast<UItemDrag>(InOperation)) {
//		return DroppedActionSlot(InGeometry, InDragDropEvent, ItemDrag_);
//	}

	return false;
}

bool URTS_HUDWidget::DroppedWidget(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UWidgetDrag* WidgetDrag)
{
	if (auto WidgetToDrag = WidgetDrag->WidgetToDrag) {
		WidgetToDrag->AddToViewport();
		FVector2D Position = GetActualPositionInViewport(InGeometry, InDragDropEvent, WidgetDrag->DropWindowOffset);
		WidgetToDrag->SetPositionInViewport(Position, false);
		return true;
	}
	else {
		return false;
	}
}

/*
bool URTS_HUDWidget::DroppedActionSlot(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UItemDrag* ItemDrag)
{
	auto ActionSlot = Cast<UActionSlot>(ItemDrag->DraggedItem);
	if (ActionSlot && RTS_PlayerController) {
		if (ActionSlot->TypeOfInventorySlot == ETypeOfActionSlot::CommonSlot) {
			
		}
		return true;
	}
	else {
		return false;
	}

}*/


FVector2D URTS_HUDWidget::GetActualPositionInViewport(const FGeometry& MyGeometry, const FDragDropEvent& PointerEvent, FVector2D DropWindowOffset)
{
	FVector2D local_pos = MyGeometry.AbsoluteToLocal(PointerEvent.GetScreenSpacePosition());
	return local_pos - DropWindowOffset;
}