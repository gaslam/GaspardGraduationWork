// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AzureKinectEnum.h"
#include "Blueprint/UserWidget.h"
#include "PerformanceMeasurement.generated.h"
/**
 * 
 */

class ULatencyComponent;
UCLASS()
class GRADUATIONWORK_API UPerformanceMeasurement final : public UUserWidget
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Performance")
    /*Sets the device name. Returns with None if empty*/
    void SetDeviceName(const FString& Name);

    UFUNCTION(BlueprintCallable, Category = "Performance")
    void StartProcess();

    UFUNCTION(BlueprintCallable, Category = "Performance")
    /*Sets the device frame time of the received device. Returns with None if empty*/
    void SetDeviceFrameTime(const float Name);

    UFUNCTION(BlueprintCallable, Category = "Performance")
    /*Sets the device name. Returns with None if empty*/
    void UpdateExportStatus(const FString& Value);

    // Resets the device name to the default value
    UFUNCTION(BlueprintCallable, Category = "Performance")
	void ResetDeviceName();
    // Resets the device name to the default value
    UFUNCTION(BlueprintCallable, Category = "Performance")
    void SetLatencyComponent(ULatencyComponent* LatencyComponent);


    // Sets the device fps
    UFUNCTION(BlueprintCallable, Category = "Performance")
	void SetDeviceFPS(const float FPS);
    // Sets the azure kinect fps
    UFUNCTION(BlueprintCallable, Category = "Performance")
    void SetDeviceKinectFPS(const EKinectFps FPS);

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeDestruct() override;

private:
	bool bIsProcessActive{ false };
	int MaxLatencySamples{ 1000 };
	int CountdownNumber{ 10 };
	float DeviceFrameTime{ 0.0f };
	float DeviceFPS{ 0.0f };

	const FString DeviceDefaultName{ "None" };
    FString DeviceName{DeviceDefaultName};
    FString SampleExportStatus{ "Press Export CSV to start data collection" };

	FTimerHandle TimerHandle;

    TObjectPtr<ULatencyComponent> LatencyComponent;

    /** Gets the actual FPS from the engine */
    UFUNCTION(BlueprintPure, Category = "Performance")
    FString GetEngineFPS() const;

    /** Gets the actual frame time from the engine */
    UFUNCTION(BlueprintPure, Category = "Performance")
    FString GetEngineFrameTimeInMS() const;

    /** Gets the device frame time */
    UFUNCTION(BlueprintPure, Category = "Performance")
    FString GetDeviceFrameTimeInMS() const;


    /** Gets the actual device name */
    UFUNCTION(BlueprintPure, Category = "Performance")
    FString GetDeviceName() const { return DeviceName; }

    /** Gets the actual status of sample exports to excel */
    UFUNCTION(BlueprintPure, Category = "Performance")
	FString GetSampleExportStatus() const { return SampleExportStatus; }

    /** Gets the actual status of sample exports to excel */
    UFUNCTION(BlueprintPure, Category = "Performance")
    int GetMaxLatencySamples() const { return MaxLatencySamples; }


    UFUNCTION(BlueprintPure, Category = "Performance")
    ULatencyComponent* GetLatencyComponent() const { return LatencyComponent; }

    UFUNCTION(BlueprintPure, Category = "Performance")
    bool IsProcessActive() const { return bIsProcessActive; }

    UFUNCTION(BlueprintPure, Category = "Performance")
    bool IsInputEnabled() const { return !IsProcessActive(); }

	UFUNCTION(BlueprintPure, Category = "Performance")
	float GetDeviceFPS() const { return DeviceFPS; }

	FString ConvertToStringTwoDigits(const double Value) const;
	FString ConvertToStringTwoDigitsMS(const double Value) const;

	UFUNCTION(Category = "Performance")
	void OnLatencyUpdated(int Amount);

    UFUNCTION(Category = "Performance")
    void OnProcessUpdated(bool bIsActive);

	UFUNCTION(Category = "Performance")
	void OnProcessSaved(FString StatusMessage, bool bHasSucceeded);

	UFUNCTION(Category = "Performance")
	void CountDown();

	void StartRecording();

	void DisableTimer();
};
