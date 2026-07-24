// Fill out your copyright notice in the Description page of Project Settings.


#include "UIDiegetic/DiegeticActor.h"

#include "NavigationSystemTypes.h"
#include "UIDiegetic/TestDiegeticCharacter.h"

// Sets default values
ADiegeticActor::ADiegeticActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComp;
	
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComp->SetupAttachment(MeshComp);
	
	if (WidgetComp && WidgetClass)
	{
		//UUserWidget* Widget = CreateWidget(this, WidgetClass);
		WidgetComp->SetWidgetClass(WidgetClass);
		//WidgetComp->SetWidget(Widget);
	}
}

// Called when the game starts or when spawned
void ADiegeticActor::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, & ADiegeticActor::OnBeginOverlap);
	MeshComp->OnComponentEndOverlap.AddDynamic(this, &ADiegeticActor::OnEndOverlap);
}

// Called every frame
void ADiegeticActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADiegeticActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (ATestDiegeticCharacter* DiegeticCharacter = Cast<ATestDiegeticCharacter>(OtherActor))
	{
		DiegeticCharacter->SetFocusInputUIAndGame(WidgetComp->GetWidget());
	}
}

void ADiegeticActor::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	if (ATestDiegeticCharacter* DiegeticCharacter = Cast<ATestDiegeticCharacter>(OtherActor))
	{
		DiegeticCharacter->SetFocusGame();
	}
}

