// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
// Sets default values
ADemoCharacter::ADemoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADemoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADemoCharacter::OnInteract(const FInputActionValue& Value)
{
	PerformInteractionTrace();
}

void ADemoCharacter::PerformInteractionTrace()
{
	FVector StartLocation = FVector::ZeroVector;
	FRotator StartRotation = FRotator::ZeroRotator;
	GetActorEyesViewPoint(StartLocation, StartRotation);
	
	FVector EndLocation = StartLocation + (StartRotation.Vector() * InteractionRange);
	
	FHitResult Hit;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(
		Hit, 
		StartLocation, 
		EndLocation, 
		ECC_Visibility, 
		CollisionParameters))
	{
		if (IInteractable* Interface = Cast<IInteractable>(Hit.GetActor()))
		{
			Interface->Interact(this);
		}
	}
	
	DrawDebugLine(
		GetWorld(), 
		StartLocation,
		EndLocation, 
		Hit.bBlockingHit ? FColor::Green : FColor::Red, 
		false,
		2);
}

// Called every frame
void ADemoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(InteractAction, 
			ETriggerEvent::Triggered, 
			this, &ADemoCharacter::OnInteract);
	}
}

