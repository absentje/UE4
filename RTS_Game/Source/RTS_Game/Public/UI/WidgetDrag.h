// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "WidgetDrag.generated.h"

/**
*
*/
UCLASS()
class RTS_GAME_API UWidgetDrag : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UWidgetDrag();
	UWidgetDrag(class UUserWidget* WidgetToDrag_, FVector2D DropWindowOffset_ = FVector2D::ZeroVector);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	class UUserWidget* WidgetToDrag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	FVector2D DropWindowOffset;

	void DragCancelled_(UDragDropOperation* Operation);
};
