// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RTS_CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class URTS_CharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	class ARTS_Character *Character;
	class UCharacterMovementComponent *MovementComponent;

	// угол между вектором скорости и вектором направления mesh'а
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Direction_CPP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float LastMoveSpeed_CPP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MoveSpeed_CPP;
	/*
	BlendMS = Lerp(BlendingMS, MS, 0.5);
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float BlendingMoveSpeed_CPP;

	// ось по вертикали
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Pitch_CPP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float LastYaw_CPP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DeltaYaw_CPP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint32 IsDead_CPP : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint32 IsMoving_CPP : 1;


	void SetCharacterProperties_SpeedAndDirection();

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;
};
