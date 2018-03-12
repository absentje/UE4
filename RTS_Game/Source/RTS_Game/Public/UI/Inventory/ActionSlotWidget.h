#pragma once

#include "CoreMinimal.h"
#include "InventorySlotWidget.h"
#include "RTS_Enumerations.h"
#include "RTS_Structures.h"
#include "ActionSlotWidget.generated.h"

UCLASS()
class UActionSlotWidget : public UInventorySlotWidget
{
	GENERATED_BODY()
public:
	UActionSlotWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	ETypeOfActionSlot TypeOfActionSlot;

	virtual void SlotChanged() override;
};