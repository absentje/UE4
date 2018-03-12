// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RTS_InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class URTS_InventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	void ConstructCommonSlots();
	void ConstructActionSlots();
	void CreateActionSlots();
	void SetTypeOfActionSlots();
	void ActionSlotsChanged();
public:
	class ARTS_PlayerController* RTS_PlayerController;

// Common Slots:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UUniformGridPanel* UniformGridPanelOfCommonSlots;

// Action SLots:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UActionSlotWidget* ArmorSlotWidget;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UActionSlotWidget* FirstWeaponSlotWidget;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UActionSlotWidget* SecondWeaponSlotWidget;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UActionSlotWidget* FirstAdditionalSlotWidget;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UActionSlotWidget* SecondAdditionalSlotWidget;
//

	URTS_InventoryWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation) override;
};
