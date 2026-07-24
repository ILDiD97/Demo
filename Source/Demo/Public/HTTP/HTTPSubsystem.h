// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "HTTPSubsystem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DEMO_API UHTTPSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SendPostRequest();
	
	void OnPostRequestRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
	
	UFUNCTION(BlueprintCallable)
	void SendGetRequest();
	
	void OnGetRequestRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
	
};
