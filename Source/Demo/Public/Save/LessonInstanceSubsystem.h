// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LessonInstanceSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FPlayerTransformState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float XPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float YPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZPosition;
	
};

USTRUCT(BlueprintType)
struct FObjectTransformState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float XPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float YPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZPosition;
	
};

USTRUCT(BlueprintType)
struct FWorldTransformState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FObjectTransformState> ObjectState;
	
};
/**
 * 
 */
UCLASS(BlueprintType)
class DEMO_API ULessonInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	void SavePlayerState(FPlayerTransformState PlayerState);
	
	UFUNCTION(BlueprintCallable)
	FPlayerTransformState LoadPlayerState();

	UFUNCTION(BlueprintCallable)
	void SaveWorldState(FWorldTransformState WorldState);
	
	UFUNCTION(BlueprintCallable)
	void SaveObjectState(FObjectTransformState ObjectState);
	
	UFUNCTION(BlueprintCallable)
	FWorldTransformState LoadWorldState();
};
