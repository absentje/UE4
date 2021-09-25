// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpActor.h"
#include "RTS_Character.h"
#include "RTS_PlayerController.h"
#include "DataAssets/Items.h"
#include "RTS_FunctionLibrary.h"

#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "ConstructorHelpers.h"
#include "UnrealNetwork.h"

// Sets default values
APickUpActor::APickUpActor()
{
	RootComponent->SetMobility(EComponentMobility::Movable);
	SetMeshSettingsDefault();
	if ( GetLocalRole() < ROLE_Authority ) {
		OnActorBeginOverlap.AddDynamic(this, &APickUpActor::BeginOverlap);
		OnActorEndOverlap.AddDynamic(this, &APickUpActor::EndOverlap);
	}
}

// Called when the game starts or when spawned
/**/
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}
void APickUpActor::SetMeshSettingsDefault()
{
	UStaticMeshComponent* MeshComp = GetStaticMeshComponent();
	if (MeshComp) {
		MeshComp->SetCastShadow(false);
		MeshComp->SetSimulatePhysics(true);
		MeshComp->SetGenerateOverlapEvents( true );

		MeshComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
		MeshComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		MeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		MeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		MeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);

		MeshComp->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Yes;
	}
}

FInventorySlot APickUpActor::GetInventorySlot() const
{
	return InvSlot;
}
void APickUpActor::SetInventorySlot(const FInventorySlot InvSlot_)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		InvSlot = InvSlot_;
	}
}

void APickUpActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(APickUpActor, InvSlot);
}

void APickUpActor::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ARTS_Character* CharacterRef = Cast<ARTS_Character>(OtherActor);
	if (CharacterRef){
		ARTS_PlayerController* PlayerControllerRef = 
			Cast<ARTS_PlayerController>(CharacterRef->Controller);
		if (PlayerControllerRef){
			PlayerControllerRef->InputPickUpActor(this);
		}
	}
}

void APickUpActor::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ARTS_Character* CharacterRef = Cast<ARTS_Character>(OtherActor);
	if (CharacterRef) {
		ARTS_PlayerController* PlayerControllerRef =
			Cast<ARTS_PlayerController>(CharacterRef->Controller);
		if (PlayerControllerRef) {
			PlayerControllerRef->OutputPickUpActor(this);
		}
	}
}

void APickUpActor::RefreshStaticMesh()
{
	if (UItems* DataAsset_Items = URTS_FunctionLibrary::GetDataAsset_Items()) {
		class UStaticMesh* Mesh_;
		try {
			Mesh_ = DataAsset_Items->ArrayOfItems[InvSlot.ItemId].MeshOfItem;
		}
		catch (...) {
			Mesh_ = NULL;
		}
		GetStaticMeshComponent()->SetStaticMesh(Mesh_);
	}
}
