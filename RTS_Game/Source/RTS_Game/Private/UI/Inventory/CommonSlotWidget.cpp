#include "UI/Inventory/CommonSlotWidget.h"

#include "RTS_PlayerController.h"


UCommonSlotWidget::UCommonSlotWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UCommonSlotWidget::SlotChanged()
{
	if (RTS_PlayerController) {
		auto& Inventory = RTS_PlayerController->Inventory;
		if (CommonSlotID < (int32)Inventory.InventoryContents.Num()) {
			InventorySlot = Inventory.InventoryContents[CommonSlotID];
		}
		Super::SlotChanged();
	}
}