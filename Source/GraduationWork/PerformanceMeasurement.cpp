// Fill out your copyright notice in the Description page of Project Settings.


#include "PerformanceMeasurement.h"
#include "MyActorComponent.h"
#include "Misc/App.h"

void UPerformanceMeasurement::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UPerformanceMeasurement::NativeDestruct()
{
	DisableTimer();
}

void UPerformanceMeasurement::SetDeviceName(const FString& Name)
{
	FString TempName = Name;

	if (TempName.IsEmpty())
	{
		TempName = DeviceDefaultName;
	}
	DeviceName = TempName;
}

void UPerformanceMeasurement::StartProcess()
{
	if (bIsProcessActive)
	{
		return;
	}
	const auto World = GetWorld();

	if(!World)
	{
		return;
	}

	auto& TimeManager = World->GetTimerManager();

	TimeManager.SetTimer(TimerHandle, this, &UPerformanceMeasurement::CountDown, 1, true);

	constexpr bool bIsActive{ true };
	OnProcessUpdated(bIsActive);
}

void UPerformanceMeasurement::SetDeviceFrameTime(const float Value)
{

	DeviceFrameTime = Value;
}

void UPerformanceMeasurement::UpdateExportStatus(const FString& Value)
{
	SampleExportStatus = Value;
}

void UPerformanceMeasurement::ResetDeviceName()
{
	DeviceName = DeviceDefaultName;
}

FString UPerformanceMeasurement::GetEngineFPS() const
{
	const double FPS{ 1.0 / FApp::GetDeltaTime() };
	// Format to a string with 2 decimal places
	return ConvertToStringTwoDigits(FPS);
}

FString UPerformanceMeasurement::GetEngineFrameTimeInMS() const
{
	const double FrameTime{ FApp::GetDeltaTime() * 1000.0 };

	return ConvertToStringTwoDigitsMS(FrameTime);
}

FString UPerformanceMeasurement::GetDeviceFrameTimeInMS() const
{
	return ConvertToStringTwoDigitsMS(DeviceFrameTime);
}

FString UPerformanceMeasurement::ConvertToStringTwoDigitsMS(const double Value) const
{
	FString DigitString = ConvertToStringTwoDigits(Value);
	return FString::Printf(TEXT("%s ms"), *DigitString);
}

void UPerformanceMeasurement::OnLatencyUpdated(int Amount)
{
	float Percentage = (static_cast<float>(Amount) / static_cast<float>(MaxLatencySamples)) * 100.0f;

	SampleExportStatus = FString::Printf(TEXT("Processing: %.2f%% of samples"), Percentage);
}

void UPerformanceMeasurement::OnProcessUpdated(bool bIsActive)
{
	bIsProcessActive = bIsActive;
}

void UPerformanceMeasurement::OnProcessSaved(FString StatusMessage, bool bHasSucceeded)
{
	SampleExportStatus = StatusMessage;
}

void UPerformanceMeasurement::CountDown()
{
	if (CountdownNumber <= 0)
	{
		StartRecording();
		return;
	}
	SampleExportStatus = FString::Printf(TEXT("Prepare yourself!!\n\nExport starting in %d"),CountdownNumber);
	--CountdownNumber;
}

void UPerformanceMeasurement::StartRecording()
{
	if (LatencyComponent)
	{
		LatencyComponent->StartRecording();
	}

	DisableTimer();
}

void UPerformanceMeasurement::DisableTimer()
{
	const auto World = GetWorld();

	if (!World)
	{
		return;
	}

	auto& TimeManager = World->GetTimerManager();

	TimeManager.ClearTimer(TimerHandle);
}

FString UPerformanceMeasurement::ConvertToStringTwoDigits(const double Value) const
{
	return FString::Printf(TEXT("%.2f"), Value);
}

void UPerformanceMeasurement::SetLatencyComponent(ULatencyComponent* Component)
{
	if(LatencyComponent)
	{
		LatencyComponent->OnLatencyUpdated.RemoveDynamic(this, &UPerformanceMeasurement::OnLatencyUpdated);
		LatencyComponent->OnProcessUpdated.RemoveDynamic(this, &UPerformanceMeasurement::OnProcessUpdated);
		LatencyComponent->OnProcessSaved.RemoveDynamic(this, &UPerformanceMeasurement::OnProcessSaved);
	}
	LatencyComponent = Component;

	LatencyComponent->OnLatencyUpdated.AddDynamic(this, &UPerformanceMeasurement::OnLatencyUpdated);
	LatencyComponent->OnProcessUpdated.AddDynamic(this, &UPerformanceMeasurement::OnProcessUpdated);
	LatencyComponent->OnProcessSaved.AddDynamic(this, &UPerformanceMeasurement::OnProcessSaved);
}
