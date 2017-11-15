// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RTS_Character.generated.h"

UCLASS()
class ARTS_Character : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollision;
protected:
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

public:
	ARTS_Character();

	UFUNCTION(BlueprintPure)
	class USphereComponent* GetSphereCollision() const;

};
