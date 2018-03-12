// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetDrag.h"
#include "RTS_InventoryWidget.h"
#include "RTS_PlayerController.h"

UWidgetDrag::UWidgetDrag(class UUserWidget* WidgetToDrag_, FVector2D DropWindowOffset_) :
	WidgetToDrag(WidgetToDrag_), DropWindowOffset(DropWindowOffset_)
{
	//OnDragCancelled.AddDynamic(this, &UWidgetDrag::DragCancelled_);
}

UWidgetDrag::UWidgetDrag()
{
	//OnDragCancelled.AddDynamic(this, &UWidgetDrag::DragCancelled_);
}


void UWidgetDrag::DragCancelled_(UDragDropOperation* Operation) {
	WidgetToDrag->AddToViewport();

	if (auto WidgetToDrag_ptr = Cast<URTS_InventoryWidget>(WidgetToDrag)) {
		WidgetToDrag_ptr->RTS_PlayerController->SetInputMode_GameAndUI();
	}
}