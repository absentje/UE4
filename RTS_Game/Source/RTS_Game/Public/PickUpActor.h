// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "RTS_Enumerations.h"
#include "RTS_Structures.h"
#include "PickUpActor.generated.h"

UCLASS()
class APickUpActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	APickUpActor();
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void RefreshStaticMesh();

	UFUNCTION(BlueprintPure)
	FInventorySlot GetInventorySlot() const;

	UFUNCTION(BlueprintCallable)
	void SetInventorySlot(const FInventorySlot InvSlot_);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	void SetMeshSettingsDefault();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = RefreshStaticMesh)
	FInventorySlot InvSlot;
};
