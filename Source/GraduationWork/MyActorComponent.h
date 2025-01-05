// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLatencyUpdated, int, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProcessUpdated, bool,bIsActive);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProcessSaved, FString, StatusMessage,bool,bHasSucceeded);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRADUATIONWORK_API ULatencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULatencyComponent();

	UFUNCTION(BlueprintCallable, Category = "Latency")
	void SetMaxLatencySamples(int Max);

	UFUNCTION(BlueprintCallable, Category = "Latency")
	void UpdateLatency(float Latency, float FramesPerSec, float FrameTimeMS);

	UFUNCTION(BlueprintCallable, Category = "Latency")
	void StartRecording();

	UPROPERTY(BlueprintAssignable, Category = "Latency")
	FOnLatencyUpdated OnLatencyUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Latency")
	FOnProcessUpdated OnProcessUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Latency")
	FOnProcessSaved OnProcessSaved;

	UFUNCTION(BlueprintPure, Category = "Latency")
	bool IsRecording() const { return m_bIsRecording; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Latency")
	void SaveStatisticsToCSV();

private:
	int m_MaxLatencySamples{ 0 };
	int m_TotalLatencySamples{ 0 };
	bool m_bIsRecording{ false };

	TArray<float> FPS{};
	TArray<float> FrameTime{};
	TArray<float> LatencySamples{};


};
