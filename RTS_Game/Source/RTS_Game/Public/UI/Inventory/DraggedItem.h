// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggedItem.generated.h"

/**
 * 
 */
UCLASS()
class RTS_GAME_API UDraggedItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UDraggedItem(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UImage* ImageOfDraggedItem;
};
