// Fill out your copyright notice in the Description page of Project Settings.
//include project files
#include "RTS_PlayerController.h"
#include "RTS_HUDWidget.h"
#include "RTS_InventoryWidget.h"
#include "PickUpActor.h"
#include "RTS_Character.h"
#include "CameraWithSpringArm.h"
#include "RTS_FunctionLibrary.h"

//include UE4 files
#include "AI/Navigation/NavigationSystem.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include <GameFramework/WorldSettings.h>
#include "UnrealNetwork.h"

ARTS_PlayerController::ARTS_PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;	// Если false, эта функция тика никогда не будет зарегистрирована
											// и никогда не будет отмечена.
	PrimaryActorTick.bStartWithTickEnabled = true;	// Если значение true, эта функция будет активирована,
													// но позже ее можно будет отключить.
	bAllowTickBeforeBeginPlay = false;
	
}

void ARTS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	// активируем камеру
	if (IsLocalController()){
		FVector CharacterLocation = FVector::ZeroVector;
		if (GetPawn())
			CharacterLocation = GetPawn()->GetActorLocation();
		UWorld* World = GetWorld();
		if (World) {
			CameraWithSpringArm =
				World->SpawnActor<ACameraWithSpringArm>(CharacterLocation, FRotator::ZeroRotator);
			CameraWithSpringArm->SetController(this);
			SetViewTarget(CameraWithSpringArm);
		}
		CreateUI_Widgets();
	}
}
void ARTS_PlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone

}

void ARTS_PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ARTS_PlayerController::SetViewTarget(AActor* NewViewTarget, FViewTargetTransitionParams TransitionParams) {
	if (CameraWithSpringArm)
		NewViewTarget = CameraWithSpringArm;
	Super::SetViewTarget(NewViewTarget, TransitionParams);
}


void ARTS_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CameraWithSpringArm) {
		if (bZoomKeyPressed)
		{
			if (WheelVector)
			{
				CameraWithSpringArm->ChangeZoom(WheelVector, DeltaSeconds);
				WheelVector = 0;
			}
		}
		else
		{
			// PlaneDisplacement
			int32 sizeX, sizeY;
			GetViewportSize(sizeX, sizeY);
			GetMousePosition(mousePosX, mousePosY);
			FVector2D VectorOfDisplacement(0, 0);
			{
				static const int32 BorderWidth = 50; // толщина границы
				if (mousePosX < BorderWidth)
					VectorOfDisplacement.Y = -1;
				if (mousePosX > sizeX - BorderWidth)
					VectorOfDisplacement.Y = 1;
				if (mousePosY < BorderWidth)
					VectorOfDisplacement.X = 1;
				if (mousePosY > sizeY - BorderWidth)
					VectorOfDisplacement.X = -1;
			}
			FHitResult TraceHitResult;
			GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			if (!VectorOfDisplacement.IsZero()) {
				CameraWithSpringArm->PlaneDisplacement(VectorOfDisplacement, DeltaSeconds);
			}
		}
		if (!CameraInput.IsZero()) {
			CameraWithSpringArm->RotateCamera(CameraInput, DeltaSeconds);
			CameraInput = FVector2D::ZeroVector;
		}
	}

}

void ARTS_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	// keep updating the destination every tick while desired
}

void ARTS_PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ARTS_PlayerController::MoveToMouseCursor);
	InputComponent->BindAction("ZoomKey", IE_Pressed, this, &ARTS_PlayerController::ZoomKeyPressed);
	InputComponent->BindAction("ZoomKey", IE_Released, this, &ARTS_PlayerController::ZoomKeyReleased);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &ARTS_PlayerController::InventoryKeyPressed);
	InputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &ARTS_PlayerController::MouseWheelPressed);
	InputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &ARTS_PlayerController::MouseWheelReleased);
	InputComponent->BindAxis("MouseX", this, &ARTS_PlayerController::MouseX);
	InputComponent->BindAxis("MouseY", this, &ARTS_PlayerController::MouseY);
}

void ARTS_PlayerController::MoveToMouseCursor()
{
	// Отслеживаем что находится под курсором мыши
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		ServerSetNewMoveDestination(Hit.ImpactPoint);
	}

}

void ARTS_PlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(MyPawn->Controller, DestLocation);
		}
		
	}
	if (Role < ROLE_Authority)
	{
		ServerSetNewMoveDestination(DestLocation);
	}
}

bool ARTS_PlayerController::ServerSetNewMoveDestination_Validate(const FVector DestLocation)
{
	return true;
}

void ARTS_PlayerController::ServerSetNewMoveDestination_Implementation(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(MyPawn->Controller, DestLocation);
		}
	}
}

void ARTS_PlayerController::ZoomKeyPressed()
{
	bZoomKeyPressed = 1;
	bShowMouseCursor = false;
	SetInputMode_GameOnly();
}

void ARTS_PlayerController::ZoomKeyReleased()
{
	bZoomKeyPressed = 0;
	bShowMouseCursor = true;
	SetInputMode_GameAndUI();
}

void ARTS_PlayerController::MouseWheelPressed()
{
	WheelVector++;
}
void ARTS_PlayerController::MouseWheelReleased()
{
	WheelVector--;
}

void ARTS_PlayerController::MouseX(float AxisValue)
{
	if (bZoomKeyPressed) {
		CameraInput.X += AxisValue;
	}
}
void ARTS_PlayerController::MouseY(float AxisValue)
{
	if (bZoomKeyPressed) {
		CameraInput.Y += AxisValue;
	}
}

void ARTS_PlayerController::InventoryKeyPressed() {
	if (Inventory_Widget) {
		ESlateVisibility NewVisibility;
		if (Inventory_Widget->GetVisibility() == ESlateVisibility::Hidden) {
			NewVisibility = ESlateVisibility::SelfHitTestInvisible;
		}
		else {
			NewVisibility = ESlateVisibility::Hidden;
		}
		Inventory_Widget->SetVisibility(NewVisibility);
	}
}


void ARTS_PlayerController::SetInputMode_GameAndUI()
{
	static const FInputModeGameAndUI InputMode = 
		[] {
			FInputModeGameAndUI InputMode;
			// Set parameters of InputMode
			InputMode.SetWidgetToFocus(NULL);
			InputMode.SetHideCursorDuringCapture(false);
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			return InputMode;
		}();
	SetInputMode(InputMode);
}

void ARTS_PlayerController::SetInputMode_GameOnly()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void ARTS_PlayerController::SetInputMode_UI_Only() {
	static const FInputModeUIOnly InputMode = [] {
		FInputModeUIOnly Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		return Mode;
	}();
	SetInputMode(InputMode);
}


void ARTS_PlayerController::CreateUI_Widgets()
{
	// HUD
	{
		auto Class_ptr = URTS_FunctionLibrary::GetClassPtrOf_HUD_BP();
		if (Class_ptr) {
			HUD_Widget = CreateWidget<URTS_HUDWidget>(this, Class_ptr);
			if (HUD_Widget) {
				HUD_Widget->AddToViewport();
				HUD_Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
		}
	}
	// Inventory
	{
		auto Class_ptr = URTS_FunctionLibrary::GetClassPtrOf_InventoryWidget_BP();
		if (Class_ptr) {
			Inventory_Widget = CreateWidget<URTS_InventoryWidget>(this, Class_ptr);
			if (Inventory_Widget) {
				Inventory_Widget->AddToViewport();
				const FVector2D InventoryPositionInViewPort(0, 200);
				Inventory_Widget->SetPositionInViewport(InventoryPositionInViewPort, false);
				Inventory_Widget->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	SetInputMode_GameAndUI();
}



// вызывать на сервере, т.к. Inventory is replicated
void ARTS_PlayerController::LoadInventory()
{
	// need to define
	//	*
	//
	FInventory TRANSIENT_Inv;
	{
		TRANSIENT_Inv.InventoryContents[2].Count = 1;
		TRANSIENT_Inv.InventoryContents[2].ItemId = 1;
		TRANSIENT_Inv.InventoryContents[4].Count = 3;
		TRANSIENT_Inv.InventoryContents[4].ItemId = 2;
	}
	Inventory = TRANSIENT_Inv;
}


void ARTS_PlayerController::InputPickUpActor(APickUpActor* PUActor)
{
	// need to define
	//	*
	//
}

void ARTS_PlayerController::OutputPickUpActor(APickUpActor* PUActor)
{
	// need to define
	//	*
	//
}

// repnotify function
void ARTS_PlayerController::RefreshInventoryWidget()
{
	// need to define
	//	*
	//
}




class URTS_HUDWidget * ARTS_PlayerController::GetHUDWidget() const {
	return HUD_Widget;
}

class URTS_InventoryWidget * ARTS_PlayerController::GetInventoryWidget() const {
	return Inventory_Widget;
}
