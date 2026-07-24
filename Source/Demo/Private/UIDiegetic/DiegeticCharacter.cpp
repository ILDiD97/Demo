// Fill out your copyright notice in the Description page of Project Settings.


#include "UIDiegetic/DiegeticCharacter.h"

#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Save/LessonInstanceSubsystem.h"
#include "Save/SaveInterface.h"

// Sets default values
ADiegeticCharacter::ADiegeticCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>("InteractionUI");
}

// Called when the game starts or when spawned
void ADiegeticCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADiegeticCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADiegeticCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(
			IA_Move, 
			ETriggerEvent::Triggered, 
			this, 
			&ADiegeticCharacter::Move);
		
		EnhancedInputComponent->BindAction(
			IA_Look, 
			ETriggerEvent::Triggered, 
			this, 
			&ADiegeticCharacter::Look);
		
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
			IA_MouseClickLeft,
			ETriggerEvent::Started, 
			this, 
			&ADiegeticCharacter::StartUIClick);
		EnhancedInputComponent->BindAction(
			IA_MouseClickLeft, 
			ETriggerEvent::Completed, 
			this, 
			&ADiegeticCharacter::EndUIClick);
	}
}

void ADiegeticCharacter::Move(const FInputActionValue& InputActionValue)
{
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void ADiegeticCharacter::Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ADiegeticCharacter::StartUIClick(const FInputActionValue& InputActionValue)
{
		bool bIsHovering = WidgetInteractionComponent->IsOverHitTestVisibleWidget();
		UE_LOG(LogTemp, Warning, TEXT("Il widget interaction sta colpendo qualcosa? %s"), bIsHovering ? TEXT("Sì") : TEXT("No"));
	if (WidgetInteractionComponent)
	{
		WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
	}
}

void ADiegeticCharacter::EndUIClick(const FInputActionValue& InputActionValue)
{
	if (WidgetInteractionComponent)
	{
		WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
	}
}

void ADiegeticCharacter::SetFocusToWidgetAndGame(UUserWidget* Widget)
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

void ADiegeticCharacter::SetFocusOnGame()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = false;
	}
}

void ADiegeticCharacter::ScanActors()
{
	// FVector Start = GetActorLocation();
	// FVector End = Start;
	// float Radius = 500;
	//
	// TArray<FHitResult> Hits;
	//
	// UKismetSystemLibrary::SphereTraceMulti(
	// 	GetWorld(),
	// 	Start,
	// 	End,
	// 	Radius,
	// 	UEngineTypes::ConvertToTraceType(ECC_Pawn),
	// 	false,
	// 	TArray<AActor*>(),
	// 	EDrawDebugTrace::None,
	// 	Hits,
	// 	true
	// 	);
	// TArray<AActor*> HitActors;
	// for (auto Hit : Hits)
	// {
	// 	AActor* HitActor = Hit.GetActor();
	// 	if (HitActor)
	// 	{
	// 		if (HitActor->GetClass()->
	// 			ImplementsInterface(
	// 				USaveInterface::StaticClass()))
	// 		{
	// 			HitActors.Add(HitActor);
	// 		}
	// 	}
	// }
	//
	// TArray<FObjectTransformState> ActorStates;
	//
	// if (UGameInstance* GI = GetGameInstance())
	// {
	// 	if (ULessonInstanceSubsystem* Subsystem = GI->GetSubsystem<ULessonInstanceSubsystem>())
	// 	{
	// 		int c = 0;
	// 		for (auto Actor : HitActors)
	// 		{
	// 			int ID = c;
	//
	// 			FVector Position = Actor->GetActorLocation();
	//
	// 			FObjectTransformState ActorState;
	// 			ActorState.id = ID;
	// 			ActorState.XPosition = Position.X;
	// 			ActorState.YPosition = Position.Y;
	// 			ActorState.ZPosition = Position.Z;
	//
	// 			ActorStates.Add(ActorState);
	// 			c++;
	// 		}
	// 		//Subsystem->SaveObjectState(ActorStates);
	// 	}
	// }
}

