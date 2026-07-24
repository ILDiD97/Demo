// Fill out your copyright notice in the Description page of Project Settings.


#include "UIDiegetic/TestDiegeticCharacter.h"

#include "AudioMixerBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ATestDiegeticCharacter::ATestDiegeticCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>("WidgetInteraction");
	
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
}

// Called when the game starts or when spawned
void ATestDiegeticCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestDiegeticCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestDiegeticCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = 
		Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(
			IA_Move, 
			ETriggerEvent::Triggered,
			this,
			&ATestDiegeticCharacter::OnMove);
		
		EnhancedInputComponent->BindAction(
			IA_MouseLook,
			ETriggerEvent::Triggered,
			this,
			&ATestDiegeticCharacter::Look);
		
		EnhancedInputComponent->BindAction(
			IA_Jump,
			ETriggerEvent::Started,
			this,
			&ACharacter::Jump);
		EnhancedInputComponent->BindAction(
			IA_Jump,
			ETriggerEvent::Completed,
			this,
			&ACharacter::StopJumping);
		
		EnhancedInputComponent->BindAction(
			IA_MouseX,
			ETriggerEvent::Started,
			this,
			&ATestDiegeticCharacter::OnStartedInputUI);
		EnhancedInputComponent->BindAction(
			IA_MouseX,
			ETriggerEvent::Completed,
			this,
			&ATestDiegeticCharacter::OnEndInputUI);
	}
		
}

void ATestDiegeticCharacter::OnMove(const FInputActionValue& InputActionValue)
{
	FVector2D InputVector = InputActionValue.Get<FVector2D>();
	
	AddMovementInput(GetActorForwardVector(), InputVector.Y);
	AddMovementInput(GetActorRightVector(), InputVector.X);
}

void ATestDiegeticCharacter::Look(const FInputActionValue& InputActionValue)
{
	FVector2D InputVector = InputActionValue.Get<FVector2D>();
	
	AddControllerYawInput(InputVector.X);
	AddControllerPitchInput(InputVector.Y);
}

void ATestDiegeticCharacter::OnStartedInputUI(const FInputActionValue& InputActionValue)
{
	if (WidgetInteractionComponent)
	{
		WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
	}
}

void ATestDiegeticCharacter::OnEndInputUI(const FInputActionValue& InputActionValue)
{
	if (WidgetInteractionComponent)
	{
		WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
	}
}

void ATestDiegeticCharacter::SetFocusInputUIAndGame(UUserWidget* Widget)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(Widget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
}

void ATestDiegeticCharacter::SetFocusGame()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = false;
	}
}

