// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/Inventory/RTS_InventoryWidget.h"
#include "RTS_PlayerController.h"
#include "RTS_FunctionLibrary.h"
#include "UI/Inventory/ActionSlotWidget.h"
#include "UI/Inventory/CommonSlotWidget.h"

#include "UObject/ConstructorHelpers.h"
#include "Blueprint/WidgetTree.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

URTS_InventoryWidget::URTS_InventoryWidget(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

void URTS_InventoryWidget::NativeConstruct() {
	Super::NativeConstruct();
	RTS_PlayerController = Cast<ARTS_PlayerController>(GetOwningPlayer());
	if (RTS_PlayerController) {
		ConstructCommonSlots();
		ConstructActionSlots();
	}
}

void URTS_InventoryWidget::ConstructCommonSlots() 
{
	UniformGridPanelOfCommonSlots = NewObject<UUniformGridPanel>();
	const auto Class_ptr = URTS_FunctionLibrary::GetClassPtrOf_CommonSlotWidget_BP();
	if (!Class_ptr) {
		URTS_FunctionLibrary::PrintMessage("CommonSlot Class_ptr is nullptr");
	}
	if (UniformGridPanelOfCommonSlots) 
	{
		UniformGridPanelOfCommonSlots->SetSlotPadding(FMargin(4));
		UniformGridPanelOfCommonSlots->SetMinDesiredSlotWidth(10);
		UniformGridPanelOfCommonSlots->SetMinDesiredSlotHeight(10);
		const int COUNT_OF_ROWS = 5;
		const int COUNT_OF_COLUMNS = 5;
		for (int i = 0; i != COUNT_OF_ROWS; ++i) 
		{
			for (int j = 0; j != COUNT_OF_COLUMNS; ++j) 
			{
				const int CommonSlot_ID = i * COUNT_OF_COLUMNS + j;
				auto CommonSlotWidgetRef =
					CreateWidget<UCommonSlotWidget>(RTS_PlayerController, Class_ptr);
				CommonSlotWidgetRef->CommonSlotID = CommonSlot_ID;
				auto UniformGridSlot =
					UniformGridPanelOfCommonSlots->AddChildToUniformGrid(CommonSlotWidgetRef);
				UniformGridSlot->SetRow(i);
				UniformGridSlot->SetColumn(j);
				CommonSlotWidgetRef->SlotChanged();
			}
		}
	}
}

void URTS_InventoryWidget::ConstructActionSlots() {
	CreateActionSlots();
	SetTypeOfActionSlots();
	ActionSlotsChanged();
}

void URTS_InventoryWidget::CreateActionSlots() {
	const auto PlContr_ptr = RTS_PlayerController;
	const auto Class_ptr = URTS_FunctionLibrary::GetClassPtrOf_ActionSlotWidget_BP();
	if (!Class_ptr) {
		URTS_FunctionLibrary::PrintMessage("ActionSlot Class_ptr is nullptr");
	}

	ArmorSlotWidget				=	CreateWidget<UActionSlotWidget>(PlContr_ptr, Class_ptr);
	FirstWeaponSlotWidget		=	CreateWidget<UActionSlotWidget>(PlContr_ptr, Class_ptr);
	SecondWeaponSlotWidget		=	CreateWidget<UActionSlotWidget>(PlContr_ptr, Class_ptr);
	FirstAdditionalSlotWidget	=	CreateWidget<UActionSlotWidget>(PlContr_ptr, Class_ptr);
	SecondAdditionalSlotWidget	=	CreateWidget<UActionSlotWidget>(PlContr_ptr, Class_ptr);
}

void URTS_InventoryWidget::SetTypeOfActionSlots() {
	ArmorSlotWidget->TypeOfActionSlot				=	ETypeOfActionSlot::ArmorSlot;
	FirstWeaponSlotWidget->TypeOfActionSlot			=	ETypeOfActionSlot::FirstWeaponSlot;
	SecondWeaponSlotWidget->TypeOfActionSlot		=	ETypeOfActionSlot::SecondWeaponSlot;
	FirstAdditionalSlotWidget->TypeOfActionSlot		=	ETypeOfActionSlot::FirstAddSlot;
	SecondAdditionalSlotWidget->TypeOfActionSlot	=	ETypeOfActionSlot::SecondAddSlot;
}

void URTS_InventoryWidget::ActionSlotsChanged() {
	ArmorSlotWidget->SlotChanged();
	FirstWeaponSlotWidget->SlotChanged();
	SecondWeaponSlotWidget->SlotChanged();
	FirstAdditionalSlotWidget->SlotChanged();
	SecondAdditionalSlotWidget->SlotChanged();
}

void URTS_InventoryWidget::NativeOnDragDetected(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::OnDragDetected(InGeometry, InMouseEvent, OutOperation);
	// need to define
	//	*
	//
	
}