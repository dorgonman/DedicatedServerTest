// Fill out your copyright notice in the Description page of Project Settings.

#include "DedicatedServerTest.h"
#include "BattleGameModeBase.h"


//DedicatedServerTestServer.exe Title -log
//DedicatedServerTestServer.exe Home -log
//DedicatedServerTestServer.exe Battle -log
ABattleGameModeBase::ABattleGameModeBase()
{

#if !UE_EDITOR
	//bUseAuthentication = true;
#endif
}

void ABattleGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//if (GetNetMode() != NM_Standalone)
	//{
	//	// Attempt to login, returning true means an async login is in flight
	//	if (!UOnlineEngineInterface::Get()->DoesSessionExist(GetWorld(), GameSession->SessionName) &&
	//		!GameSession->ProcessAutoLogin())
	//	{
	//		GameSession->RegisterServer();
	//	}
	//}
	//if (GetNetMode() != NM_DedicatedServer)
	{
		GameSession->RegisterServer();

	}

}


void ABattleGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	//if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{


	}
}
APlayerController* ABattleGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	auto playerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	//if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{
		//IOnlineSessionPtr SessionInt = Online::GetSessionInterface(GetWorld());
		////NewPlayer->SetNetDriverName();

		//FOnlineSessionSettings settings;
		//settings.NumPublicConnections = 5;
		//settings.bIsLANMatch = true;
		//settings.bIsDedicated = false;
		//settings.bShouldAdvertise = true;
		//FOnlineSessionSetting set;
		//set.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineServiceAndPing;
		//settings.Settings.Add("Ad", set);
		//settings.GetAdvertisementType("Ad");
		//FName testRoom = "TestRoom";
		//SessionInt->CreateSession(0, testRoom, settings);
		//int numSessions = SessionInt->GetNumSessions();
		//UE_LOG(LogTemp, Log, TEXT("numSessions: %d"), numSessions);

		//IOnlineChatPtr ChatInt = Online::GetChatInterface(GetWorld());

		//IOnlineVoicePtr VoiceInt = Online::GetVoiceInterface(GetWorld());
		//VoiceInt->create
		//IMPLEMENT_GET_INTERFACE(Session);
		//IMPLEMENT_GET_INTERFACE(Party);
		//IMPLEMENT_GET_INTERFACE(Chat);
		//IMPLEMENT_GET_INTERFACE(Friends);
		//IMPLEMENT_GET_INTERFACE(User);
		//IMPLEMENT_GET_INTERFACE(SharedCloud);
		//IMPLEMENT_GET_INTERFACE(UserCloud);
		//IMPLEMENT_GET_INTERFACE(Voice);
		//IMPLEMENT_GET_INTERFACE(ExternalUI);
		//IMPLEMENT_GET_INTERFACE(Time);

	}
	return playerController;
}
void ABattleGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	//if (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer)
	{

		PlayerControllerList.Add(NewPlayer);
	}
}


TSubclassOf<AGameSession> ABattleGameModeBase::GetGameSessionClass() const
{
	return GameSessionClass;
	/*Super::GetGameSessionClass();
	if (GameSessionClass) {
		return GameSessionClass;
	}
	else {
		return AGameSession::StaticClass();;
	}
*/
	//return GetGameSessionClass ? GameSessionClass : AGameSession::StaticClass();
	//return GameSessionClass;
}