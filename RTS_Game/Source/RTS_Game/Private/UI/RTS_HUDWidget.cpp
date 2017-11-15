// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_HUDWidget.h"

URTS_HUDWidget::URTS_HUDWidget(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
	RTS_PlayerController = Cast<ARTS_PlayerController>(GetOwningPlayer());
}

bool URTS_HUDWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::OnDrop(InGeometry, InDragDropEvent, InOperation);
	DroppedWidget(InGeometry, InDragDropEvent, InOperation);
	return true; // ??
}

bool URTS_HUDWidget::DroppedWidget(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	// need to define
	//	*
	//
}