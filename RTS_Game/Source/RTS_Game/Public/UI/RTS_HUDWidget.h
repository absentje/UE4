// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RTS_HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class URTS_HUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class ARTS_PlayerController* RTS_PlayerController;

	URTS_HUDWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

	bool DroppedWidget(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, class UWidgetDrag* WidgetDrag);

//	bool DroppedActionSlot(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, class UItemDrag* ItemDrag);

	FVector2D GetActualPositionInViewport(const FGeometry& MyGeometry, const FDragDropEvent& PointerEvent, FVector2D DropWindowOffset);
};
