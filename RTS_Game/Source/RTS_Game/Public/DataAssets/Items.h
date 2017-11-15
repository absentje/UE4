// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RTS_Enumerations.h"
#include "RTS_Structures.h"
#include "Items.generated.h"


UCLASS(BlueprintType)
class UItems : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItem> ArrayOfItems;
	// вспомогательные функции для работы FItem
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UTexture2D* GetPictureOfItem(const FItem& Item);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static class UStaticMesh* GetStaticMeshOfItem(const FItem& Item);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString GetDescription(const FItem& Item);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static ETypeOfItem GetTypeOfItem(const FItem& Item);
};
