// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"

 UCLASS()
class GRADUATIONWORK_API UStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	void OnQuitButtonClicked();

private:

};
