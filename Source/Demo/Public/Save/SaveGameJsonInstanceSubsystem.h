// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveGameJsonInstanceSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 level;
};

/**
 * 
 */
UCLASS(BlueprintType)
class DEMO_API USaveGameJsonInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SaveGameWithStruct(FCharacterStats Stats);
	
	UFUNCTION(BlueprintCallable)
	void SaveGame(FString Name, int32 Level);
	
	UFUNCTION(BlueprintCallable)
	FCharacterStats LoadSaveGameWithStruct();

	UFUNCTION(BlueprintCallable)
	void LoadTuplaSaveGame();
	
	TTuple<FString, int32> LoadSaveGame();
};
