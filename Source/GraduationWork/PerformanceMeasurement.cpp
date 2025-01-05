// Fill out your copyright notice in the Description page of Project Settings.


#include "PerformanceMeasurement.h"
#include "Misc/App.h"

void UPerformanceMeasurement::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
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

FString UPerformanceMeasurement::ConvertToStringTwoDigits(const double Value) const
{
	return FString::Printf(TEXT("%.2f"), Value);
}
