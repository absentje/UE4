// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDrag.generated.h"

/**
 * 
 */
UCLASS()
class RTS_GAME_API UItemDrag : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UItemDrag();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	class UTexture2D* ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	class UItemSlotWidget* DraggedItem;

	UFUNCTION()
	void DragCancelled_(UDragDropOperation* Operation);
};
