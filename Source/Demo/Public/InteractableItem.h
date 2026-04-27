// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "GameFramework/Actor.h"
#include "InteractableItem.generated.h"

UCLASS()
class DEMO_API AInteractableItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableItem();

	virtual void Interact(AActor* Caller) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractableItem")
	UStaticMeshComponent* StaticMesh;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
