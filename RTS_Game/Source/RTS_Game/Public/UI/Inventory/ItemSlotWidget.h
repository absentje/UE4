// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RTS_Enumerations.h"
#include "RTS_Structures.h"
#include "ItemSlotWidget.generated.h"

UCLASS(abstract)
class UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UItemSlotWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//, meta = (ExposeOnSpawn = "true"))
	FInventorySlot InventorySlot;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UTexture2D* currentImage_Texture2D;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UImage* ImageOfItem;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UEditableTextBox* CountOfItem_TextBox;

	class ARTS_PlayerController* RTS_PlayerController;

	UFUNCTION(BlueprintCallable)
		void SlotChanged_BP() { SlotChanged(); };
	virtual void SlotChanged();

	bool IsEmpty() const; // if empty - clear unuseful info of item

	void SetTextToInformationBar();

	virtual void NativeConstruct() override;

protected:
	void InvSlotClear(); // to do InventorySlot == {0,0}
	void ConstructImageOfItemWidget();
	void ConstructTextInfoOfItemWidget();

	void RefreshImageOfItem();
	void RefreshCountOfItem();

	class UDragDropOperation* CreateItemDrag() const;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, 
		const FPointerEvent& InMouseEvent) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, 
		const FDragDropEvent& InDragDropEvent, 
		UDragDropOperation* InOperation) override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, 
		UDragDropOperation* InOperation) override;

	bool DroppedWidget(const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation);

	void DroppedItemSlotWidget(const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation);
};
