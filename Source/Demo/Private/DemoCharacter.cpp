// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
	FVector Start = FVector::ZeroVector;
	FRotator Rotation = FRotator::ZeroRotator;
	GetActorEyesViewPoint(Start, Rotation);
	
	FVector End = Start * (Rotation.Vector() * InteractionRange);
	
	FHitResult Hit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,
		CollisionParams))
	{
		if (IInteractable* Interactable = Cast<IInteractable>(Hit.GetActor()))
		{
			Interactable->Interact(this);
		}
	}
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

	if (UEnhancedInputComponent* EInputComponent =
		CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EInputComponent->BindAction(InteractionAction, 
			ETriggerEvent::Triggered, this,
			&ADemoCharacter::OnInteract);
	}
}

