// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_FunctionLibrary.h"
#include "DataAssets/Items.h"

#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"

#include <thread>
#include <chrono>

// FOR FInventorySlot
int32 URTS_FunctionLibrary::GetCount(const FInventorySlot &Slot)
{
	return Slot.Count;
}

int32 URTS_FunctionLibrary::GetItemId(const FInventorySlot &Slot)
{
	return Slot.ItemId;
}

void URTS_FunctionLibrary::SetCount(UPARAM(ref) FInventorySlot & Slot, int32 Count)
{
	Slot.Count = Count;
}

void URTS_FunctionLibrary::SetItemId(UPARAM(ref) FInventorySlot & Slot, int32 Id)
{
	Slot.ItemId = Id;
}


// FOR FInventory
FInventorySlot URTS_FunctionLibrary::GetArmorSlot(const FInventory & Inventory)
{
	return Inventory.ArmorSlot;
}

FInventorySlot URTS_FunctionLibrary::GetFirstWeaponSlot(const FInventory & Inventory)
{
	return Inventory.FirstWeaponSlot;
}

FInventorySlot URTS_FunctionLibrary::GetSecondWeaponSlot(const FInventory & Inventory)
{
	return Inventory.SecondWeaponSlot;
}

FInventorySlot URTS_FunctionLibrary::GetFirstAdditionalSlot(const FInventory & Inventory)
{
	return Inventory.FirstAdditionalSlot;
}

FInventorySlot URTS_FunctionLibrary::GetSecondAdditionalSlot(const FInventory & Inventory)
{
	return Inventory.SecondAdditionalSlot;
}

void URTS_FunctionLibrary::SetArmorSlot(UPARAM(ref) FInventory & Inventory, const FInventorySlot & Slot)
{
	Inventory.ArmorSlot.Count = Slot.Count;
	Inventory.ArmorSlot.ItemId = Slot.ItemId;
}

void URTS_FunctionLibrary::SetFirstWeaponSlot(UPARAM(ref) FInventory & Inventory, const FInventorySlot & Slot)
{
	Inventory.FirstWeaponSlot.Count = Slot.Count;
	Inventory.FirstWeaponSlot.ItemId = Slot.ItemId;
}

void URTS_FunctionLibrary::SetSecondWeaponSlot(UPARAM(ref) FInventory & Inventory, const FInventorySlot & Slot)
{
	Inventory.SecondWeaponSlot.Count = Slot.Count;
	Inventory.SecondWeaponSlot.ItemId = Slot.ItemId;
}

void URTS_FunctionLibrary::SetFirstAdditionalSlot(UPARAM(ref) FInventory & Inventory, const FInventorySlot & Slot)
{
	Inventory.FirstAdditionalSlot.Count = Slot.Count;
	Inventory.FirstAdditionalSlot.ItemId = Slot.ItemId;
}

void URTS_FunctionLibrary::SetSecondAdditionalSlot(UPARAM(ref) FInventory & Inventory, const FInventorySlot & Slot)
{
	Inventory.SecondAdditionalSlot.Count = Slot.Count;
	Inventory.SecondAdditionalSlot.ItemId = Slot.ItemId;
}

TArray<FInventorySlot>& URTS_FunctionLibrary::GetInventoryContents(UPARAM(ref) FInventory& Inventory)
{
	return Inventory.InventoryContents;
}

void URTS_FunctionLibrary::SetArraySlot(UPARAM(ref)FInventory & Inventory, const FInventorySlot & Slot, const int32 Id)
{
	Inventory.InventoryContents[Id] = Slot;
}


// FOR DataAsset Items

UItems* URTS_FunctionLibrary::GetDataAsset_Items()
{
	static ConstructorHelpers::FObjectFinder<UItems> StaticDataAsset_Items(TEXT("Items'/Game/Blueprints/Assets/Items.Items'"));
	if (StaticDataAsset_Items.Succeeded()) {
		return StaticDataAsset_Items.Object;
	}
	else {
		return NULL;
	}
}

ETypeOfItem URTS_FunctionLibrary::GetTypeOfItem(const int32 ItemId)
{
	try {
		return GetDataAsset_Items()->ArrayOfItems[ItemId].TypeOfItem;
	}
	catch (...) {
		return ETypeOfItem::None;
	}
}