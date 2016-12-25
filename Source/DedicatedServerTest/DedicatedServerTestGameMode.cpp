// Fill out your copyright notice in the Description page of Project Settings.

#include "DedicatedServerTest.h"
#include "DedicatedServerTestGameMode.h"




void ADedicatedServerTestGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{

	
	}
}
APlayerController* ADedicatedServerTestGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	auto playerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{


	}
	return playerController;
}
void ADedicatedServerTestGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{


	}
}