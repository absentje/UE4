// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Structures.h"

FInventorySlot::FInventorySlot() :
	ItemId(0), Count(0)
{
}

FInventory::FInventory()
{
	const int COUNT_OF_INVENTORY_OBJECTS = 16;
	InventoryContents.InsertDefaulted(0, COUNT_OF_INVENTORY_OBJECTS);
}



