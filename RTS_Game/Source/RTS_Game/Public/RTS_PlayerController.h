// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS_Enumerations.h"
#include "RTS_Structures.h"
#include "RTS_PlayerController.generated.h"

UCLASS()
class ARTS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTS_PlayerController();

	// override
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	void SetViewTarget(class AActor* NewViewTarget, FViewTargetTransitionParams TransitionParams = FViewTargetTransitionParams()) override;
	virtual void Tick(float DeltaSeconds) override;

	
	void InputPickUpActor(class APickUpActor* PUActor);
	void OutputPickUpActor(class APickUpActor* PUActor);

	void SetInputMode_GameAndUI();
	void SetInputMode_GameOnly();
	

protected:
	void CreateUI_Widgets();
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class URTS_HUDWidget *HUD_Widget;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = RefreshInventoryWidget)
	FInventory Inventory;
	UFUNCTION()
	void RefreshInventoryWidget();
	UFUNCTION()
	void LoadInventory();

	// PlayerInput variables
	int32 WheelVector;
	FVector2D CameraInput;
	uint32 bZoomKeyPressed : 1;
	
	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	UFUNCTION()
	void SetNewMoveDestination(const FVector DestLocation);
	UFUNCTION(reliable, server, WithValidation)
	void ServerSetNewMoveDestination(const FVector DestLocation);

	// Zoom button
	void ZoomKeyPressed();
	void ZoomKeyReleased();
	// MouseWheels
	void MouseWheelPressed();
	void MouseWheelReleased();
	// Camera turning
	void MouseX(float AxisValue);
	void MouseY(float AxisValue);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CameraReference")
	class ACameraWithSpringArm *CameraWithSpringArm;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CharacterReference")
	class ARTS_Character *CharacterReference;

	float mousePosX;
	float mousePosY;
};
