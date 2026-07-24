// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/LessonInstanceSubsystem.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "JsonObjectConverter.h"

void ULessonInstanceSubsystem::SavePlayerState(FPlayerTransformState PlayerState)
{
	FString JsonString;
	
	FJsonObjectConverter::UStructToJsonObjectString(PlayerState, JsonString);	
	
	FString path = FPaths::ProjectDir() + " PlayerState.json";
	FFileHelper::SaveStringToFile(JsonString, *path);
}

FPlayerTransformState ULessonInstanceSubsystem::LoadPlayerState()
{
	FString Path = FPaths::ProjectDir() + " PlayerState.json";
	FString JsonString;
	FPlayerTransformState PlayerState;
	if(!FFileHelper::LoadFileToString(JsonString, *Path))
	{
		return PlayerState;
	}
	
	FJsonObjectConverter::
		JsonObjectStringToUStruct(
			JsonString, 
			&PlayerState,
			0,
			0);
	
	return PlayerState;
}

void ULessonInstanceSubsystem::SaveWorldState(FWorldTransformState WorldState)
{
	FString JsonString;
	
	FJsonObjectConverter::UStructToJsonObjectString(WorldState, JsonString);	
	
	FString path = FPaths::ProjectDir() + " WorldState.json";
	FFileHelper::SaveStringToFile(JsonString, *path);
}

void ULessonInstanceSubsystem::SaveObjectState(FObjectTransformState ObjectState)
{
	FString Path = FPaths::ProjectDir() + " WorldState.json";
	FString JsonString;
	FWorldTransformState WorldState;
	if(!FFileHelper::LoadFileToString(JsonString, *Path))
	{
		return;
	}
	FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &WorldState);
	
	for (auto Object : WorldState.ObjectState)
	{
		if (Object.ObjectName == ObjectState.ObjectName)
		{
			Object = ObjectState;
			FJsonObjectConverter::UStructToJsonObjectString(WorldState, JsonString);	
			FFileHelper::SaveStringToFile(JsonString, *Path);
			return;
		}
	}
	
	WorldState.ObjectState.Add(ObjectState);
	
	FJsonObjectConverter::UStructToJsonObjectString(WorldState, JsonString);	
	
	FFileHelper::SaveStringToFile(JsonString, *Path);
	
}

FWorldTransformState ULessonInstanceSubsystem::LoadWorldState()
{
	FString Path = FPaths::ProjectDir() + " WorldState.json";
	FString JsonString;
	FWorldTransformState WorldState;
	if(!FFileHelper::LoadFileToString(JsonString, *Path))
	{
		return WorldState;
	}
	
	FJsonObjectConverter::
		JsonObjectStringToUStruct(
			JsonString, 
			&WorldState,
			0,
			0);
	
	return WorldState;
}
