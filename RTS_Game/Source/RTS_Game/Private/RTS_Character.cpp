//include project files
#include "RTS_Character.h"
#include "RTS_CharacterAnimInstance.h"

//include UE4 files
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "UnrealNetwork.h"


ARTS_Character::ARTS_Character()
{
	// Установка размера для игровой капсулы
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
//	GetCapsuleComponent()->SetIsReplicated(true);
	// Не вращать персонажа в направлении камеры (???)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// настройка движения персонажа
	GetCharacterMovement()->bOrientRotationToMovement = true; // поворот персонажа в направлении движения
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f); // задаем скорость поворота оси
	GetCharacterMovement()->bConstrainToPlane = true; // движение, ограничивается плоскостью
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // привязка к плоскости при первом подключении

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> 
		SkeletalMesh(TEXT("SkeletalMesh'/Game/CharacterContent/Meshes/Barney/SK_Mannequin_Barney.SK_Mannequin_Barney'"));
	if (SkeletalMesh.Succeeded()){
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}
	static ConstructorHelpers::FClassFinder<URTS_CharacterAnimInstance>
		AnimInstanceBPClass(TEXT("/Game/CharacterContent/RTS_AnimInstanceBP"));
	if (AnimInstanceBPClass.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstanceBPClass.Class);
	}
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, 0, -90));
	
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	if (SphereCollision) {
		SphereCollision->InitSphereRadius(250.0f);
	}
}

void ARTS_Character::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone

}

USphereComponent* ARTS_Character::GetSphereCollision() const
{
	return SphereCollision;
}