#include "UI/Inventory/ActionSlotWidget.h"

#include "RTS_PlayerController.h"

UActionSlotWidget::UActionSlotWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UActionSlotWidget::SlotChanged()
{
	if (RTS_PlayerController) {
		auto& Inventory = RTS_PlayerController->Inventory;

		switch (TypeOfActionSlot) {
		case ETypeOfActionSlot::None:
			break;
		case ETypeOfActionSlot::ArmorSlot:
			InventorySlot = Inventory.ArmorSlot;
			break;
		case ETypeOfActionSlot::FirstWeaponSlot:
			InventorySlot = Inventory.FirstWeaponSlot;
			break;
		case ETypeOfActionSlot::SecondWeaponSlot:
			InventorySlot = Inventory.SecondWeaponSlot;
			break;
		case ETypeOfActionSlot::FirstAddSlot:
			InventorySlot = Inventory.FirstAdditionalSlot;
			break;
		case ETypeOfActionSlot::SecondAddSlot:
			InventorySlot = Inventory.SecondAdditionalSlot;
			break;
		}

		Super::SlotChanged();
	}
}