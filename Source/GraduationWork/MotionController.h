// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MotionController.generated.h"

UCLASS()
class GRADUATIONWORK_API AMotionController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMotionController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region RightHand
	//Handles the usage of the right hand
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MotionController")
	TObjectPtr<class UMotionControllerComponent> MotionControllerRightGrip;

	//A visual representation of the right hand
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MotionController")
	TObjectPtr<USkeletalMeshComponent> MotionControllerRight;

	/** Handles the visualization of the right hand like animations */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<class UXRDeviceVisualizationComponent> XRDeviceVisualizationRight;
#pragma endregion RightHand

#pragma region LeftHand
	//Handles the usage of the left hand
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MotionController")
	TObjectPtr<class UMotionControllerComponent> MotionControllerLeftGrip;

	//A visual representation of the left hand
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MotionController")
	TObjectPtr<USkeletalMeshComponent> MotionControllerLeft;

	/** Handles the visualization of the left hand like animations */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<class UXRDeviceVisualizationComponent> XRDeviceVisualizationLeft;
#pragma endregion Lefthand



	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MotionController")
	TObjectPtr<USceneComponent> ControllerOrigin;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MotionController")
	TObjectPtr<class UCameraComponent> CameraComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MotionController")
	TObjectPtr<class UVRNotificationsComponent> NotificationsComponent;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void SetupHands();

	void SetupCamera();

};
