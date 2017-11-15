// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_CharacterAnimInstance.h"
#include "RTS_Character.h"

#include "GameFramework/CharacterMovementComponent.h"

void URTS_CharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ARTS_Character>(TryGetPawnOwner());
	if (Character) {
		MovementComponent =
			Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
	}
}

void URTS_CharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Character) {
		SetCharacterProperties_SpeedAndDirection();
	}
}


void URTS_CharacterAnimInstance::SetCharacterProperties_SpeedAndDirection()
{
	// Get direction and speed for animation control.
	
	LastMoveSpeed_CPP = MoveSpeed_CPP;	//	set#1
	FVector Velocity = Character->GetVelocity();
	MoveSpeed_CPP = Velocity.Size();	//	set#2
	BlendingMoveSpeed_CPP =
		FMath::Lerp(BlendingMoveSpeed_CPP, MoveSpeed_CPP, 0.3);	//	set#3
	Direction_CPP = CalculateDirection(Velocity, Character->GetActorRotation());	//	set#4
	static const float MIN_POSSIBLE_SPEED = 0.1;
	if (MoveSpeed_CPP >= MIN_POSSIBLE_SPEED)	//	set#5
		IsMoving_CPP = true;
	else
		IsMoving_CPP = false;
}