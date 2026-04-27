// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class DEMO_API IInteractable 
{
	GENERATED_BODY()
public:
	
	virtual void Interact(AActor* Caller) = 0;
	
};
