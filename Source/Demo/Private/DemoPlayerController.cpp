// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoPlayerController.h"
#include "EnhancedInputSubsystems.h"


void ADemoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (auto* LP = GetLocalPlayer())
	{
		if (auto* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (MappingContext)
			{
				Subsystem->AddMappingContext(MappingContext, MappingPriority);
			}
		}
	}

}
