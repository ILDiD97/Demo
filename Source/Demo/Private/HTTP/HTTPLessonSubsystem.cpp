// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTP/HTTPLessonSubsystem.h"

void UHTTPLessonSubsystem::SendPostRequest()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
			FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(
		this, &UHTTPLessonSubsystem::OnRequestCompleted);

	Request->SetURL(
		TEXT("https://jsonplaceholder.typicode.com/posts"));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(
		TEXT("Content-Type"), 
		TEXT("application/json; charset=UTF-8"));
	
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("title"),
	TEXT("Titolo da Unreal"));
	JsonObject->SetStringField(TEXT("body"),
			TEXT("Ciao da Unreal"));
	
	FString BodyString;
	TSharedRef<TJsonWriter<>> Writer = 
		TJsonWriterFactory<>::Create(&BodyString);
	FJsonSerializer::Serialize(
		JsonObject.ToSharedRef(), Writer);
	
	Request->SetContentAsString(BodyString);
	Request->ProcessRequest();
}

void UHTTPLessonSubsystem::OnRequestCompleted(
	TSharedPtr<IHttpRequest> HttpRequest,
	TSharedPtr<IHttpResponse> HttpResponse, 
	bool bArg)
{
	if (bArg && HttpResponse.IsValid())
	{
		int32 Code = HttpResponse->GetResponseCode();
		FString Msg = FString::Printf(TEXT("Codeice di Risposta è %d"), Code);
	
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(
				-1,
				5,
				FColor::Green,
				Msg);
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1,
				5,
				FColor::Red,
				"Andrea è un fallito");
	}
}

void UHTTPLessonSubsystem::SendGetRequest()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
			FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(
		this, &UHTTPLessonSubsystem::OnGetRequestCompleted);
	
	Request->SetURL(TEXT("https://jsonplaceholder.typicode.com/posts/1"));
	Request->SetVerb(TEXT("GET"));
	
	Request->ProcessRequest();
}

void UHTTPLessonSubsystem::OnGetRequestCompleted(
	TSharedPtr<IHttpRequest> HttpRequest,
	TSharedPtr<IHttpResponse> HttpResponse, bool bArg)
{
	if (bArg && HttpResponse.IsValid())
	{
		FString ResponseString = HttpResponse->GetContentAsString();
        
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(
				-1,
				5,
				FColor::Blue,
				ResponseString);
	}
}
