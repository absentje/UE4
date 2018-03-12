#pragma once

#include "CoreMinimal.h"
#include "ItemSlotWidget.h"
#include "RTS_Enumerations.h"
#include "RTS_Structures.h"
#include "InventorySlotWidget.generated.h"

UCLASS()
class UInventorySlotWidget : public UItemSlotWidget
{
	GENERATED_BODY()
public:

	UInventorySlotWidget(const FObjectInitializer& ObjectInitializer);

};