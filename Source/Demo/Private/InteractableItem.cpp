// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItem.h"

#include "DemoCharacter.h"

// Sets default values
AInteractableItem::AInteractableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AInteractableItem::Interact(AActor* Caller)
{
	UE_LOG(LogTemp, Warning, TEXT("Oggetto raccolto da %s"), *Caller->GetName());
	
	Cast<ADemoCharacter>(Caller)->Item = this;
}

// Called when the game starts or when spawned
void AInteractableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

