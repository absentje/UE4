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
	// ��������� ������� ��� ������� �������
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
//	GetCapsuleComponent()->SetIsReplicated(true);
	// �� ������� ��������� � ����������� ������ (???)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// ��������� �������� ���������
	GetCharacterMovement()->bOrientRotationToMovement = true; // ������� ��������� � ����������� ��������
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f); // ������ �������� �������� ���
	GetCharacterMovement()->bConstrainToPlane = true; // ��������, �������������� ����������
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // �������� � ��������� ��� ������ �����������

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