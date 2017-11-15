// Fill out your copyright notice in the Description page of Project Settings.

#include "DataAssets/Items.h"

UTexture2D * UItems::GetPictureOfItem(const FItem & Item)
{
	return Item.PictureOfItem;
}

class UStaticMesh * UItems::GetStaticMeshOfItem(const FItem & Item)
{
	return Item.MeshOfItem;
}

FString UItems::GetDescription(const FItem & Item)
{
	return Item.Description;
}

ETypeOfItem UItems::GetTypeOfItem(const FItem & Item)
{
	return Item.TypeOfItem;
}
