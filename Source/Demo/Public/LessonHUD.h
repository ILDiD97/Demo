// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LessonHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ALessonHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	void ShowWidget(TSubclassOf<UUserWidget> WidgetClass);
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainMenuClass;
	
	UPROPERTY(VisibleAnywhere)
	UUserWidget* CurrentWidget;
};
