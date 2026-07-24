// Fill out your copyright notice in the Description page of Project Settings.


#include "LessonHUD.h"

#include "Blueprint/UserWidget.h"

void ALessonHUD::BeginPlay()
{
	Super::BeginPlay();
	
	ShowWidget(MainMenuClass);
}

void ALessonHUD::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
	
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	
	if (CurrentWidget)
	{
		CurrentWidget->AddToViewport();
	}
}
