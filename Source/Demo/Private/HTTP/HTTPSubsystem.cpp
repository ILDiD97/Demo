// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTP/HTTPSubsystem.h"

void UHTTPSubsystem::SendPostRequest()
{
	// 1. Crea la richiesta HTTP
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request 
	= FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(
		this, &UHTTPSubsystem::OnPostRequestRecieved);
    
	// 2. Imposta URL e Metodo POST
	Request->SetURL(TEXT(
		"https://jsonplaceholder.typicode.com/posts"));
	Request->SetVerb(
		TEXT("POST"));
	Request->SetHeader(
		TEXT("Content-Type"), 
		TEXT("application/json; charset=UTF-8"));

	// 3. Crea il corpo JSON da inviare
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("title"), 
		TEXT("Titolo da Unreal"));
	JsonObject->SetStringField(TEXT("body"), 
		TEXT("Contenuto del post inviato tramite POST."));
	JsonObject->SetNumberField(TEXT("userId"),
		1);

	FString BodyString;
	TSharedRef<TJsonWriter<>> Writer = 
		TJsonWriterFactory<>::Create(&BodyString);
	FJsonSerializer::Serialize(
		JsonObject.ToSharedRef(), Writer);

	// 4. Assegna il body e invia
	Request->SetContentAsString(BodyString);
	Request->ProcessRequest();
}

void UHTTPSubsystem::OnPostRequestRecieved(
	FHttpRequestPtr Request, 
	FHttpResponsePtr Response, 
	bool bSuccess)
{
	if (bSuccess && Response.IsValid())
	{
		int32 Code = Response->GetResponseCode();
		FString ResponseString = Response->GetContentAsString();
        
		if (GEngine)
		{
			FString Msg = FString::Printf(TEXT("POST Risposta (Codice %d)"), Code);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Msg);
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 5.f, 
				FColor::Red, 
				TEXT("POST Fallita o risposta non valida."));
		}
	}
}

void UHTTPSubsystem::SendGetRequest()
{
	// 1. Crea la richiesta HTTP
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(
		this, &UHTTPSubsystem::OnGetRequestRecieved);
	
	// 2. Imposta URL (GET)
	Request->SetURL(
		TEXT("https://jsonplaceholder.typicode.com/posts/1"));
	Request->SetVerb(TEXT("GET"));

	// 3. Invia
	Request->ProcessRequest();
}

void UHTTPSubsystem::OnGetRequestRecieved(
	FHttpRequestPtr Request, 
	FHttpResponsePtr Response, 
	bool bSuccess)
{
	if (bSuccess && Response.IsValid())
	{
		int32 Code = Response->GetResponseCode();
		FString ResponseString = Response->GetContentAsString();
        
		if (GEngine)
		{
			FString Msg = FString::Printf(TEXT("GET Risposta (Codice %d): %s"), Code, *ResponseString);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, Msg);
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GET Fallita o risposta non valida."));
		}
	}
}
