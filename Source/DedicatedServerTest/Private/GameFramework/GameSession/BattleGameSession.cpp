// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleGameSession.h"
#include "DedicatedServerTest.h"


//https://forums.unrealengine.com/showthread.php?97479-Dedicated-server-with-Steam-is-a-joke
//open steam.ServerSteamID(long number):PORT

//https://wiki.unrealengine.com/How_To_Use_Sessions_In_C%2B%2B


//https://wiki.unrealengine.com/Using_Steamworks_with_UE4


//https://answers.unrealengine.com/questions/323185/modules-custom-onlinesubsystem-any-docs-or-tutoria.html

//https://answers.unrealengine.com/questions/323457/online-sessions-gamesessionname.html

//https://answers.unrealengine.com/questions/24190/understanding-the-ionlinesubsystem-and-agamesessio.html



//https://answers.unrealengine.com/questions/115618/ionlinesessionstartsessionfname-sessionname-called.html
//IOnlineSession::StartSession(FName SessionName); =>It should be called on both the server and the clients. ( invites, joins, etc.)
void ABattleGameSession::RegisterServer()
{
	Super::RegisterServer();
	//UE_LOG(LogTemp, Log, TEXT("ABattleGameSession::RegisterServer() with map: %s"), *GetDefault<UGameMapsSettings>()->GetGameDefaultMap());
	//const int MaxNumPlayers = 8;
	//const bool bIsPresence = true;
	//const bool bIsLAN = false;
	//const int HostingPlayerNum = 0;
	//const FString GameType = "Battle";
	const FString MapName = GetWorld()->GetMapName();;//"Battle";
	//const auto UserId = MakeShareable(new FUniqueNetIdString(FString::Printf(TEXT("%d"), HostingPlayerNum)));

	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			FOnlineSessionSettings Settings;
			Settings.bAllowInvites = true;
			Settings.bUsesPresence = false;
			Settings.bAllowJoinInProgress = true;
			Settings.bAllowJoinViaPresence = true;
			Settings.bAllowJoinViaPresenceFriendsOnly = false;
			Settings.bAntiCheatProtected = true;
			Settings.bIsLANMatch = false;
			Settings.bIsDedicated = true;
			Settings.bShouldAdvertise = true;
			Settings.NumPublicConnections = 60;
			Settings.NumPrivateConnections = 0;
			Settings.Set(SETTING_MAPNAME, MapName, EOnlineDataAdvertisementType::ViaOnlineService);

			//if (bIsPresence)
			{
				//	Settings.QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
			}
			Sessions->CreateSession(0, GameSessionName, Settings);
			//Sessions->StartSession(GameSessionName);
			//Sessions->GameServerName = FString("My Server!");
		}
	}
}

bool ABattleGameSession::GetSessionJoinability(FName InSessionName, FJoinabilitySettings& OutSettings)
{
	return Super::GetSessionJoinability(InSessionName, OutSettings);

}

bool ABattleGameSession::TravelToSession(int32 ControllerId, FName InSessionName)
{
	return Super::TravelToSession(ControllerId, InSessionName);

}

FString ABattleGameSession::ApproveLogin(const FString& Options)
{
	return Super::ApproveLogin(Options);

}