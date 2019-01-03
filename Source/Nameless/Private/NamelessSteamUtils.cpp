// Fill out your copyright notice in the Description page of Project Settings.

#include "NamelessSteamUtils.h"



FString UNamelessSteamUtils::GetSteamId(UObject* WorldContextObject, int32 PlayerIndex)
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get(FName("Steam"));

	UWorld* WorldPtr = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);

	if (WorldPtr)
	{
		ULocalPlayer* LocalPlayer = GEngine->GetLocalPlayerFromControllerId(WorldPtr, PlayerIndex);

		if (LocalPlayer)
		{
			TSharedPtr<const FUniqueNetId> Pid = OSS->GetIdentityInterface()->GetUniquePlayerId(LocalPlayer->GetControllerId());

			if (Pid.IsValid())
			{
				return Pid->ToString();
			}
		}
	}
	return TEXT("Error");
}

EOnlineSteamStatus UNamelessSteamUtils::GetSteamOnlineStatus(UObject* WorldContextObject, int32 PlayerIndex)
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get(FName("Steam"));

	UWorld* WorldPtr = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);

	if (WorldPtr)
	{
		ULocalPlayer* LocalPlayer = GEngine->GetLocalPlayerFromControllerId(WorldPtr, PlayerIndex);

		if (LocalPlayer)
		{
			TSharedPtr<const FUniqueNetId> Pid = OSS->GetIdentityInterface()->GetUniquePlayerId(LocalPlayer->GetControllerId());

			if (Pid.IsValid())
			{
				ELoginStatus::Type LoginStatus = OSS->GetIdentityInterface()->GetLoginStatus(*Pid);

				switch (LoginStatus)
				{
				case ELoginStatus::LoggedIn:
					return EOnlineSteamStatus::OSS_LoggedIn;

				case ELoginStatus::NotLoggedIn:
					return EOnlineSteamStatus::OSS_NotLoggedIn;

				case ELoginStatus::UsingLocalProfile:
					return EOnlineSteamStatus::OSS_Local;
				}
			}
		}
	}

	return EOnlineSteamStatus::OSS_NotLoggedIn;
}

FString UNamelessSteamUtils::ConvertOnlineStatusToString(EOnlineSteamStatus OnlineStatus)
{
	switch (OnlineStatus)
	{
	case EOnlineSteamStatus::OSS_LoggedIn:
		return TEXT("Logged In");

	case EOnlineSteamStatus::OSS_NotLoggedIn:
		return TEXT("Not Logged In");

	case EOnlineSteamStatus::OSS_Local:
		return TEXT("Local Player");

	default:
		return TEXT("Error");
	}
}
