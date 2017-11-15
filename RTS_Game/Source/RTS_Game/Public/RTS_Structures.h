// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RTS_Enumerations.h"
#include "RTS_Structures.generated.h"

USTRUCT(BlueprintType)
struct FWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinDmg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxDmg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmountOfAmmoInMagazine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmoInMagazine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETypeOfWeapon TypeOfWeapon;
};
USTRUCT(BlueprintType)
struct FArmor
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PhysResist;
};
USTRUCT(BlueprintType)
struct FAmmo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> WeaponsId;
};
USTRUCT(BlueprintType)
struct FFirstSlot
{
	GENERATED_USTRUCT_BODY()

};
USTRUCT(BlueprintType)
struct FSecondSlot
{
	GENERATED_USTRUCT_BODY()

};
USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()

	// Common properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NameOfItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* PictureOfItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* MeshOfItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCountable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETypeOfItem TypeOfItem;

	// Weapon properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeapon Weapon;
	// Armor properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FArmor Armor;
	// Ammo properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAmmo Ammo;
	// FirstSlot properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFirstSlot FirstSlot;
	// SecondSlot properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSecondSlot SecondSlot;
	// Other properties
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_USTRUCT_BODY()

	// Properties

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;

	FInventorySlot();
};
USTRUCT(BlueprintType)
struct FInventory
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventorySlot ArmorSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventorySlot FirstWeaponSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventorySlot SecondWeaponSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventorySlot FirstAdditionalSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventorySlot SecondAdditionalSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventorySlot> InventoryContents;

	FInventory();
};

UCLASS(abstract)
class RTS_GAME_API URTS_Structures : public UObject
{
	GENERATED_BODY()

};
