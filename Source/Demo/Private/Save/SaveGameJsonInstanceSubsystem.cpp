// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/SaveGameJsonInstanceSubsystem.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"

void USaveGameJsonInstanceSubsystem::SaveGameWithStruct(FCharacterStats Stats)
{
	FString OutputString;

	// Converte la struct in JSON
	FJsonObjectConverter::UStructToJsonObjectString(Stats, OutputString);

	FString Path = FPaths::ProjectDir() + "SaveGame.json";
	FFileHelper::SaveStringToFile(OutputString, *Path);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			TEXT("SaveGameWithStruct: File salvato"));
}

void USaveGameJsonInstanceSubsystem::SaveGame(FString Name, int32 Level)
{
	
	TSharedPtr<FJsonObject> JsonObj = MakeShared<FJsonObject>();

	JsonObj->SetStringField("name", Name);
	JsonObj->SetNumberField("level", Level);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = 
		TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize
	(JsonObj.ToSharedRef(), Writer);

	FString Path = FPaths::ProjectDir() + "SaveGame.json";
	FFileHelper::SaveStringToFile(OutputString, *Path);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			TEXT("SaveGame: File salvato"));
}

FCharacterStats USaveGameJsonInstanceSubsystem::LoadSaveGameWithStruct()
{
	FCharacterStats Stats;

	FString Path = FPaths::ProjectDir() + "SaveGame.json";
	FString JsonString;

	if (!FFileHelper::LoadFileToString(JsonString, *Path))
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				TEXT("LoadSaveGameWithStruct: File non trovato"));
		return Stats;
	}

	// Converte JSON → struct
	FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &Stats, 0, 0);
	
	return Stats;
}

void USaveGameJsonInstanceSubsystem::LoadTuplaSaveGame()
{
	TTuple<FString, int32> RRupla = LoadSaveGame();

	const FString& Name = RRupla.Get<0>();
	int32 Level = RRupla.Get<1>();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Green,
			FString::Printf(
				TEXT("RRupla → Nome: %s | Livello: %d"),
				*Name, Level)
		);
	}
}

TTuple<FString, int32> USaveGameJsonInstanceSubsystem::LoadSaveGame()
{
	
	FString Path = FPaths::ProjectDir() + "SaveGame.json";
	FString JsonString;

	if (!FFileHelper::LoadFileToString(JsonString, *Path))
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				TEXT("LoadSaveGame: File non trovato"));
		return MakeTuple(FString(""), 0);
	}

	TSharedPtr<FJsonObject> JsonObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		FString Name = JsonObj->GetStringField(TEXT("name"));
		int32 Level  = JsonObj->GetIntegerField(TEXT("level"));

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
				FString::Printf(TEXT("Caricato (Tuple): %s (%d)"), *Name, Level));

		return MakeTuple(Name, Level);
	}

	return MakeTuple(FString(""), 0);
}
