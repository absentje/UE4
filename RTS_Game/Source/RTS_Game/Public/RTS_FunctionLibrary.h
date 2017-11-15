// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RTS_Enumerations.h"
#include "RTS_Structures.h"
#include "RTS_FunctionLibrary.generated.h"


UCLASS(abstract)
class URTS_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// DataAsset Items
	UFUNCTION(BlueprintPure)
	static class UItems* GetDataAsset_Items();
	UFUNCTION(BlueprintCallable)
	static ETypeOfItem GetTypeOfItem(const int32 ItemId);

	// вспомогательные функции для работы FInventorySlot
	UFUNCTION(BlueprintPure)
	static int32 GetCount(const FInventorySlot& Slot);

	UFUNCTION(BlueprintPure)
	static int32 GetItemId(const FInventorySlot& Slot);

	UFUNCTION(BlueprintCallable)
	static void SetCount(UPARAM(ref) FInventorySlot& Slot, int32 Count);

	UFUNCTION(BlueprintCallable)
	static void SetItemId(UPARAM(ref) FInventorySlot& Slot, int32 Id);

	// вспомогательные функции для работы FInventory
	UFUNCTION(BlueprintPure)
	static FInventorySlot GetArmorSlot(const FInventory& Inventory);
	UFUNCTION(BlueprintPure)
	static FInventorySlot GetFirstWeaponSlot(const FInventory& Inventory);
	UFUNCTION(BlueprintPure)
	static FInventorySlot GetSecondWeaponSlot(const FInventory& Inventory);
	UFUNCTION(BlueprintPure)
	static FInventorySlot GetFirstAdditionalSlot(const FInventory& Inventory);
	UFUNCTION(BlueprintPure)
	static FInventorySlot GetSecondAdditionalSlot(const FInventory& Inventory);

	UFUNCTION(BlueprintCallable)
	static void SetArmorSlot(UPARAM(ref) FInventory& Inventory, const FInventorySlot& Slot);
	UFUNCTION(BlueprintCallable)
	static void SetFirstWeaponSlot(UPARAM(ref) FInventory& Inventory, const FInventorySlot& Slot);
	UFUNCTION(BlueprintCallable)
	static void SetSecondWeaponSlot(UPARAM(ref) FInventory& Inventory, const FInventorySlot& Slot);
	UFUNCTION(BlueprintCallable)
	static void SetFirstAdditionalSlot(UPARAM(ref) FInventory& Inventory, const FInventorySlot& Slot);
	UFUNCTION(BlueprintCallable)
	static void SetSecondAdditionalSlot(UPARAM(ref) FInventory& Inventory, const FInventorySlot& Slot);

	UFUNCTION(BlueprintPure)
	static TArray<FInventorySlot>& GetInventoryContents(UPARAM(ref) FInventory& Inventory);
	UFUNCTION(BlueprintCallable)
	static void SetArraySlot(UPARAM(ref) FInventory& Inventory, const FInventorySlot& Slot, const int32 Id);
};
