// Fill out your copyright notice in the Description page of Project Settings.


#include "AzureCharacter.h"

#include "AzureKinectDevice.h"

// Sets default values
AAzureCharacter::AAzureCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AAzureCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (!AzureKinect)
	{
		return;
	}

	AzureKinect->StartDevice();
}

void AAzureCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (!AzureKinect || !AzureKinect->IsOpen())
	{
		return;
	}

	AzureKinect->StopDevice();
}

void AAzureCharacter::BeginDestroy()
{
	Super::BeginDestroy();
	if (AzureKinect && AzureKinect->IsOpen())
	{
		AzureKinect->StopDevice();
	}
}

// Called to bind functionality to input
void AAzureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

