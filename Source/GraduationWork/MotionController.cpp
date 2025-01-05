// Fill out your copyright notice in the Description page of Project Settings.


#include "MotionController.h"

#include "MotionControllerComponent.h"
#include "XRDeviceVisualizationComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "VRNotificationsComponent.h"
#include "IXRTrackingSystem.h"
#include "HeadMountedDisplay.h"
#include "PerformanceMeasurement.h"
#include "Camera/CameraComponent.h"


// Sets default values
AMotionController::AMotionController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	ControllerOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("ControllerOrigin"));

	RootComponent = ControllerOrigin;

	SetupHands();

	SetupCamera();

	NotificationsComponent = CreateDefaultSubobject<UVRNotificationsComponent>(TEXT("NotificationsComponent"));
}

// Called when the game starts or when spawned
void AMotionController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMotionController::SetupHands()
{
	const TArray<FName> HandNames = TArray<FName>({ TEXT("Left"), TEXT("Right") });

#pragma region RightHand
	//Setup Right hand grip
	MotionControllerRightGrip = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRightGrip"));
	MotionControllerRightGrip->SetupAttachment(ControllerOrigin);
	MotionControllerRightGrip->SetTrackingMotionSource(HandNames[1]);

	//Visualise the right hand
	XRDeviceVisualizationRight = CreateDefaultSubobject<UXRDeviceVisualizationComponent>(TEXT("RightHandVisualizer"));
	XRDeviceVisualizationRight->SetupAttachment(MotionControllerRightGrip);

	//Mesh for the right hand
	MotionControllerRight = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MotionControllerRight"));
	MotionControllerRight->SetupAttachment(MotionControllerRightGrip);
#pragma endregion RightHand

#pragma region LeftHand
	//Setup Right hand grip
	MotionControllerLeftGrip = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeftGrip"));
	MotionControllerLeftGrip->SetupAttachment(ControllerOrigin);
	MotionControllerLeftGrip->SetTrackingMotionSource(HandNames[0]);

	//Visualise the right hand
	XRDeviceVisualizationLeft = CreateDefaultSubobject<UXRDeviceVisualizationComponent>(TEXT("LeftHandVisualizer"));
	XRDeviceVisualizationLeft->SetupAttachment(MotionControllerLeftGrip);

	//Mesh for the right hand
	MotionControllerLeft = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MotionControllerLeft"));
	MotionControllerLeft->SetupAttachment(MotionControllerLeftGrip);
#pragma endregion LeftHand


}

void AMotionController::SetupCamera()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	CameraComponent->SetRelativeLocation(FVector(-150.f, 0.0f, 0.0f));
	CameraComponent->SetupAttachment(ControllerOrigin);
}

void AMotionController::SetDeviceName()
{
	const auto& XRSystem = GEngine->XRSystem;
	if (!XRSystem)
	{
		return;
	}

	const auto Device = XRSystem->GetHMDDevice();

	if (!Device)
	{
		return;
	}
	FName Name = Device->GetHMDName();
	PerformanceMeasurement->SetDeviceName(Name.ToString());
}

void AMotionController::ResetDeviceName()
{
	if (PerformanceMeasurement)
	{
		PerformanceMeasurement->ResetDeviceName();
	}
}

// Called every frame
void AMotionController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMotionController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

