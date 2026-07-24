// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor.h"

#include "UIDiegetic/DiegeticCharacter.h"


// Sets default values
AWidgetActor::AWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Widget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	Widget->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AWidgetActor::OnBeginOverlap);
	Mesh->OnComponentEndOverlap.AddDynamic(this, &AWidgetActor::OnEndOverlap);
}

// Called every frame
void AWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWidgetActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (ADiegeticCharacter* diegetiChar = Cast<ADiegeticCharacter>(OtherActor))
	{
		diegetiChar->SetFocusToWidgetAndGame(Widget->GetWidget());
	}
}

void AWidgetActor::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	if (ADiegeticCharacter* diegetiChar = Cast<ADiegeticCharacter>(OtherActor))
	{
		diegetiChar->SetFocusOnGame();
	}
}

