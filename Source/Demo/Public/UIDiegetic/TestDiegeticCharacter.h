// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/WidgetInteractionComponent.h"
#include "GameFramework/Character.h"
#include "TestDiegeticCharacter.generated.h"

UCLASS()
class DEMO_API ATestDiegeticCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestDiegeticCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnMove(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void Look(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void OnStartedInputUI(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void OnEndInputUI(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void SetFocusInputUIAndGame(UUserWidget* Widget);
	
	UFUNCTION()
	void SetFocusGame();
	
	UPROPERTY(EditAnywhere)
	UInputAction* IA_Move;
	
	UPROPERTY(EditAnywhere)
	UInputAction* IA_MouseLook;
	
	UPROPERTY(EditAnywhere)
	UInputAction* IA_MouseX;
	
	UPROPERTY(EditAnywhere)
	UInputAction* IA_Jump;
	
	UPROPERTY(EditAnywhere)
	UWidgetInteractionComponent* WidgetInteractionComponent;
};
