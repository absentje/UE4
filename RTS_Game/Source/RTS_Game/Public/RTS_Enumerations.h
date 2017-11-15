// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RTS_Enumerations.generated.h"

UENUM(BlueprintType)
enum class ETypeOfItem : uint8
{
	None,
	Weapon,
	Armor,
	Ammo,
	FirstSlot,
	SecondSlot
};
UENUM(BlueprintType)
enum class ETypeOfWeapon : uint8
{
	None,
	Hip_Weapon,			// тазобедренное оружие
	Ironsights_Weapon,	// прицельное оружие
	Pistol

};
UENUM(BlueprintType)
enum class ETypeOfInventorySlot : uint8
{
	None,
	NotFromInventory,
	CommonSlot,
	WeaponSlot,
	ArmorSlot,
	FirstAddSlot,
	SecondAddSlot
};

UCLASS(abstract)
class RTS_GAME_API URTS_Enumerations : public UObject
{
	GENERATED_BODY()
};
