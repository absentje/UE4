// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory/ItemDrag.h"
#include "UI/Inventory/ItemSlotWidget.h"
#include "RTS_PlayerController.h"

UItemDrag::UItemDrag() {
	OnDragCancelled.AddDynamic(this, &UItemDrag::DragCancelled_);
}

void UItemDrag::DragCancelled_(UDragDropOperation* Operation) {
	if (DraggedItem) {
		DraggedItem->RTS_PlayerController->SetInputMode_GameAndUI();
	}
}