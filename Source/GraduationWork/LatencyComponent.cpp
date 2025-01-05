// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"

// Sets default values for this component's properties
ULatencyComponent::ULatencyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULatencyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void ULatencyComponent::SetMaxLatencySamples(int Max)
{
	m_MaxLatencySamples = Max;
	
	LatencySamples.Reserve(Max);
	LatencySamples.Init(0.0f, Max);

	FPS.Reserve(Max);
	FPS.Init(0.0f, Max);
	FrameTime.Reserve(Max);
	FrameTime.Init(0.0f, Max);
}

void ULatencyComponent::StartRecording()
{
	m_bIsRecording = true;
	m_TotalLatencySamples = 0;
}

void ULatencyComponent::SaveStatisticsToCSV()
{
	FString SavePath = FPaths::ProjectSavedDir();
#if !WITH_EDITOR
	SavePath = FPaths::ProjectUserDir();
#endif
	SavePath += TEXT("LatencyStatistics.csv");

	FString CSVContent = TEXT("FPS, FrameTime, Latency\n"); // CSV Header

	for (int i{}; i < m_MaxLatencySamples; ++i)
	{
		const float ValueFPS = FPS[i];
		const float ValueFrameTime = FrameTime[i];
		const float ValueLatency = LatencySamples[i];
		CSVContent += FString::Printf(TEXT("%.2f, %.2f, %.2f\n"), ValueFPS, ValueFrameTime, ValueLatency);
	}

	//// Add statistics summary
	//float Avg, Min, Max;
	//CalculateStatistics(Avg, Min, Max);
	//CSVContent += FString::Printf(TEXT("\nStatistics\nAverage,%.2f\nMin,%.2f\nMax,%.2f\n"), Avg, Min, Max);

	if (FFileHelper::SaveStringToFile(CSVContent, *SavePath))
	{
		UE_LOG(LogTemp, Log, TEXT("Statistics saved successfully to: %s"), *SavePath);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Statistics saved successfully to: %s"), *SavePath));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save statistics to: %s"), *SavePath);
	}
}

//void ULatencyComponent::CalculateStatistics(float& Average, float& Min,float& Max) const
//{
//	if (LatencySamples.Num() > 0)
//	{
//		Min = FLT_MAX;
//		Max = FLT_MIN;
//		float Sum = 0.0f;
//
//		for (const float& Value : LatencySamples)
//		{
//			Sum += Value;
//			if (Value < Min) Min = Value;
//			if (Value > Max) Max = Value;
//		}
//
//		Average = Sum / LatencySamples.Num();
//	}
//	else
//	{
//		Average = 0.0f;
//		Min = 0.0f;
//		Max = 0.0f;
//	}
//}


void ULatencyComponent::UpdateLatency(float Latency,float FramesPerSec,float FrameTimeMS)
{
	if (!m_bIsRecording)
	{
		return;
	}

	if (m_TotalLatencySamples < m_MaxLatencySamples)
	{
		LatencySamples[m_TotalLatencySamples] = Latency;
		FPS[m_TotalLatencySamples] = FramesPerSec;
		FrameTime[m_TotalLatencySamples] = FrameTimeMS;
		++m_TotalLatencySamples;

		if (m_TotalLatencySamples >= m_MaxLatencySamples)
		{
			m_bIsRecording = false;
			SaveStatisticsToCSV();
		}
	}
}

