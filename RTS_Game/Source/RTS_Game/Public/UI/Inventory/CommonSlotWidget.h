#pragma once

#include "CoreMinimal.h"
#include "InventorySlotWidget.h"
#include "RTS_Enumerations.h"
#include "RTS_Structures.h"
#include "CommonSlotWidget.generated.h"

UCLASS()
class UCommonSlotWidget : public UInventorySlotWidget
{
	GENERATED_BODY()
public:

	UCommonSlotWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
	int32 CommonSlotID;

	virtual void SlotChanged() override;
};