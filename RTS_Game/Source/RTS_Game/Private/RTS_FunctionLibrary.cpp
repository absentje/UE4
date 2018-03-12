// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_FunctionLibrary.h"
#include "DataAssets/Items.h"

#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

#include "RTS_PlayerController.h"
#include "UI/Inventory/ActionSlotWidget.h"
#include "UI/Inventory/CommonSlotWidget.h"
#include "UI/Inventory/RTS_InventoryWidget.h"
#include "UI/Inventory/DraggedItem.h"
#include "UI/RTS_HUDWidget.h"


void URTS_FunctionLibrary::PrintMessage(FString Message, FColor Color, float TimeToDisplay)
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, Color, Message);
	}
}


// Widgets

class URTS_HUDWidget* URTS_FunctionLibrary::GetHUDWidgetRef(const class UUserWidget* widget)
{
	auto PlayerController = Cast<ARTS_PlayerController>(widget->GetOwningPlayer());
	if (PlayerController)
		return PlayerController->GetHUDWidget();
	else
		return nullptr;
}

class URTS_InventoryWidget* URTS_FunctionLibrary::GetInventoryWidgetRef(const class UUserWidget* widget)
{
	auto PlayerController = Cast<ARTS_PlayerController>(widget->GetOwningPlayer());
	if (PlayerController)
		return PlayerController->GetInventoryWidget();
	else
		return nullptr;
}

UClass * URTS_FunctionLibrary::GetClassPtrOf_CommonSlotWidget_BP()
{
	static auto Class_ptr = [] {
		FString PathName("/Game/Blueprints/UI/Inventory/CommonSlotWidget_BP");
		return ConstructorHelpersInternal::FindOrLoadClass(PathName, UCommonSlotWidget::StaticClass());
	}();
	return Class_ptr;
}

UClass * URTS_FunctionLibrary::GetClassPtrOf_ActionSlotWidget_BP()
{
	static auto Class_ptr = [] {
		FString PathName("/Game/Blueprints/UI/Inventory/ActionSlotWidget_BP");
		return ConstructorHelpersInternal::FindOrLoadClass(PathName, UActionSlotWidget::StaticClass());
	}();
	return Class_ptr;
}

UClass * URTS_FunctionLibrary::GetClassPtrOf_InventoryWidget_BP()
{
	static auto Class_ptr = [] {
		FString PathName("/Game/Blueprints/UI/Inventory/InventoryWidget_BP");
		return ConstructorHelpersInternal::FindOrLoadClass(PathName, URTS_InventoryWidget::StaticClass());
	}();
	return Class_ptr;
}

UClass * URTS_FunctionLibrary::GetClassPtrOf_HUD_BP()
{
	static auto Class_ptr = [] {
		FString PathName("/Game/Blueprints/UI/HUD_BP");
		return ConstructorHelpersInternal::FindOrLoadClass(PathName, URTS_HUDWidget::StaticClass());
	}();
	return Class_ptr;
}

UClass * URTS_FunctionLibrary::GetClassPtrOf_DraggedItem_BP()
{
	static auto Class_ptr = [] {
		FString PathName("/Game/Blueprints/UI/Inventory/DraggedItem_BP");
		return ConstructorHelpersInternal::FindOrLoadClass(PathName, UDraggedItem::StaticClass());
	}();
	return Class_ptr;
}

///////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////
// FOR DataAsset Items

UItems* URTS_FunctionLibrary::GetDataAsset_Items()
{
	static auto object_ptr = [] {
		FString PathName("/Game/Blueprints/Assets/Items");
		return ConstructorHelpersInternal::FindOrLoadObject<UItems>(PathName);
	}();
	return object_ptr;
}

TArray<FItem>& URTS_FunctionLibrary::GetItemsInfo() {
	return GetDataAsset_Items()->ArrayOfItems;
}

ETypeOfItem URTS_FunctionLibrary::GetTypeOfItem(const int32 ItemId)
{
	auto& mass = GetItemsInfo();
	if ((int)mass.GetAllocatedSize() <= ItemId || ItemId < 0)
		return ETypeOfItem::None;
	return mass[ItemId].TypeOfItem;
}