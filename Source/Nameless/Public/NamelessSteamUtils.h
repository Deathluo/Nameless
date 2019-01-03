// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Online.h"
#include "Engine/LocalPlayer.h"
#include "UObject/Object.h"
#include "NamelessSteamUtils.generated.h"

UENUM(BlueprintType)
enum class EOnlineSteamStatus : uint8
{
	OSS_LoggedIn = 0		UMETA(DisplayName = "Logged In"),
	OSS_NotLoggedIn = 1		UMETA(DisplayName = "Not Logged In"),
	OSS_Local = 2			UMETA(DisplayName = "Local Player")
};

/**
 * 
 */
UCLASS()
class NAMELESS_API UNamelessSteamUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, meta = (WorldContext = WorldContextObject),Category = "Utils|Steam")
	static FString GetSteamId(UObject* WorldContextObject, int32 PlayerIndex);
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = WorldContextObject), Category = "Utils|Steam")
	static EOnlineSteamStatus GetSteamOnlineStatus(UObject* WorldContextObject, int32 PlayerIndex);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String" ,Keywords = "To String"), Category = "Utils|Steam")
	static FString ConvertOnlineStatusToString(EOnlineSteamStatus OnlineStatus);
};
