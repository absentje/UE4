// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraWithSpringArm.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "RTS_PlayerController.h"
#include "Materials/Material.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

#define print(text) {if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text);}

// Sets default values
ACameraWithSpringArm::ACameraWithSpringArm()
{
	SetReplicates(false);
	SetReplicateMovement(false);

 	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true;	// Вращение будет относительно мира, а не родителя
	CameraBoom->TargetArmLength = 800.f;	// Длина "рычага"
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f); // Вращение компонента относительно родительского элемента
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
		// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // камера не будет вращаться относительно рычага

		// Создаем наклейку(decal) в мире, чтобы показать местоположение курсора
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void ACameraWithSpringArm::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraWithSpringArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CursorToWorld != nullptr && Controller){
		if (Controller->IsValidLowLevel()) {
			// Структура, содержащая информацию об одном ударе следа, таком как точка удара
			// и нормальная поверхность в этой точке.(weakptr on actor, etc.)
			FHitResult TraceHitResult;
			Controller->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocationAndRotation(TraceHitResult.Location, CursorR);
		}
	}
}

void ACameraWithSpringArm::SetController(class ARTS_PlayerController *Controller_) {
	Controller = Controller_;
}

void ACameraWithSpringArm::ChangeZoom(int32 WheelVector, float deltaTime, float speedChanging) {
	static const float MIN_ARM_LENGTH = 150;
	static const float MAX_ARM_LENGTH = 2000;
	CameraBoom->TargetArmLength =
		FMath::Clamp<float>(CameraBoom->TargetArmLength - WheelVector * speedChanging * deltaTime,
			MIN_ARM_LENGTH, MAX_ARM_LENGTH);
}

void ACameraWithSpringArm::PlaneDisplacement(FVector2D Vector2D, float deltaTime, float speedChanging) {
	// условимся, что Vector2D.X сонаправлено с Forward
	//				Vector2D.Y сонаправлено с Right
	FVector Forward = CameraBoom->GetForwardVector();
	FVector Right = CameraBoom->GetRightVector();
	// ScaleForward нужен для убирания зависимости скорости перемещения камеры
	// от угла просмотра камеры, иначе при угле камеры -80, скорость перемещения камеры
	// значительно снижается
	int32 ScaleForward = FMath::Sqrt(1 +
		((Forward.Z) * (Forward.Z)) / ((Forward.X) * (Forward.X) + (Forward.Y) * (Forward.Y)) );
	// |Forward|/|{xOy-компонента}| = 1/cosA = sqrt(1+z^2/(x^2+y^2))
	Forward.Z = 0;
	Right.Z = 0;
	FVector Location = CameraBoom->GetComponentLocation();
	Location += (Forward * ScaleForward * Vector2D.X + Right * Vector2D.Y) * deltaTime * speedChanging;
	CameraBoom->SetWorldLocation(Location);
}

void ACameraWithSpringArm::RotateCamera(FVector2D CameraInput, float deltaTime, float speedChanging) {
	FRotator NewRotation = CameraBoom->GetComponentRotation();
	NewRotation.Yaw += CameraInput.X * deltaTime * speedChanging;
	NewRotation.Pitch = 
		FMath::Clamp(NewRotation.Pitch + CameraInput.Y * deltaTime * speedChanging, -70.0f, -10.0f);
	CameraBoom->SetWorldRotation(NewRotation);
}