// Fill out your copyright notice in the Description page of Project Settings.

#include "DedicatedServerTest.h"
#include "TitleGameModeBase.h"


void  ATitleGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

}
void  ATitleGameModeBase::InitGameState()
{
	Super::InitGameState();
}

void ATitleGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("ATitleGameModeBase::BeginPlay() with map: %s"), *GetDefault<UGameMapsSettings>()->GetGameDefaultMap());
	//if (GetNetMode() != NM_Standalone)
	//{
	//	// Attempt to login, returning true means an async login is in flight
	//	if (!UOnlineEngineInterface::Get()->DoesSessionExist(GetWorld(), GameSession->SessionName) &&
	//		!GameSession->ProcessAutoLogin())
	//	{
	//		GameSession->RegisterServer();
	//	}
	//}

}