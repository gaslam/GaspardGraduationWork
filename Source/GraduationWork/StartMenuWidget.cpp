// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuWidget.h"
#include <Kismet/KismetSystemLibrary.h>

void UStartMenuWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}