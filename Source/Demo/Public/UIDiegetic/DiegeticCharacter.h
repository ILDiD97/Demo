// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/WidgetInteractionComponent.h"
#include "GameFramework/Character.h"
#include "DiegeticCharacter.generated.h"

UCLASS()
class DEMO_API ADiegeticCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADiegeticCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void Look(const FInputActionValue& InputActionValue);
	
	void StartUIClick(const FInputActionValue& InputActionValue);
	void EndUIClick(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void SetFocusToWidgetAndGame(UUserWidget* Widget);
	
	UFUNCTION()
	void SetFocusOnGame();
	
	UPROPERTY(EditAnywhere)
	UInputAction* IA_Move;
	
	UPROPERTY(EditAnywhere)
	UInputAction* IA_Look;
	
	UPROPERTY(EditAnywhere)
	UInputAction* IA_Jump;
	
	UPROPERTY(EditAnywhere)
	UInputAction* IA_MouseClickLeft;
	
	UPROPERTY(EditAnywhere)
	UWidgetInteractionComponent* WidgetInteractionComponent;

	UFUNCTION(BlueprintCallable)
	void ScanActors();

};
