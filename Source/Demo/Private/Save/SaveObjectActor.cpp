// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/SaveObjectActor.h"

// Sets default values
ASaveObjectActor::ASaveObjectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASaveObjectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASaveObjectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

