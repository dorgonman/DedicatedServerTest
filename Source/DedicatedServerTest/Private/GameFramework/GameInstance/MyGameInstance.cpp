// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameInstance.h"
#include "DedicatedServerTest.h"

#include "AudioDeviceManager.h"


//https://madebykrol.wordpress.com/2015/05/21/unreal-engine-and-online-multiplayer/

UMyGameInstance::UMyGameInstance()
	:SearchSettings(new FOnlineSessionSearch())
{

	SearchSettings->bIsLanQuery = false;
	auto NetMode = GEngine->GetNetMode(GetWorld());
	if (NetMode != NM_DedicatedServer)
	{
		FindSessionCompeteDelegate.BindUObject(this, &UMyGameInstance::OnFindSessionsComplete);
		JoinSessionCompleteDelegate.BindLambda([this](FName sessionName,
			EOnJoinSessionCompleteResult::Type eSessionType)
		{
			OnJoinSessionsComplete(sessionName, eSessionType);
		});
		//(this, &AMyPlayerController::OnJoinSessionsComplete);
	}

}

void UMyGameInstance::Init()
{
	Super::Init();

}


#if WITH_EDITOR

bool UMyGameInstance::InitializePIE(bool bAnyBlueprintErrors, int32 PIEInstance, bool bRunAsDedicated)
{

	return Super::InitializePIE(bAnyBlueprintErrors, PIEInstance, bRunAsDedicated);

}

bool UMyGameInstance::StartPIEGameInstance(ULocalPlayer* LocalPlayer, bool bInSimulateInEditor, bool bAnyBlueprintErrors, bool bStartInSpectatorMode)
{
	bool result = Super::StartPIEGameInstance(LocalPlayer, bInSimulateInEditor, bAnyBlueprintErrors, bStartInSpectatorMode);
	FindAndJoinSessions();
	return result;
}
#endif //#if WITH_EDITOR

void UMyGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
	FindAndJoinSessions();

}
bool UMyGameInstance::JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults)
{
	//Super::JoinSession(LocalPlayer, SessionIndexInSearchResults);
	return true;
}
bool UMyGameInstance::JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult)
{
	return true;
}

void UMyGameInstance::FindAndJoinSessions()
{

	auto NetMode = GEngine->GetNetMode(GetWorld());
	if (NetMode != NM_DedicatedServer)
	{
		IOnlineSessionPtr SessionInt = Online::GetSessionInterface(GetWorld());
		SessionInt->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompeteDelegate);
		SessionInt->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);
		if (!bJoinCompleted) {
			bool b = SessionInt->FindSessions(0, SearchSettings);
			int numSessions = SessionInt->GetNumSessions();
			UE_LOG(LogTemp, Log, TEXT("numSessions: %d"), numSessions);
		}
	}

}

void UMyGameInstance::OnFindSessionsComplete(bool bSuccess)
{
	UE_LOG(LogTemp, Log, TEXT("OnFindSessionCompleteDelegate: %d"), bSuccess);
	IOnlineSessionPtr SessionInt = Online::GetSessionInterface(GetWorld());
	int numSessions = SessionInt->GetNumSessions();
	UE_LOG(LogTemp, Log, TEXT("numSessions: %d"), numSessions);
	if (SearchSettings->SearchResults.Num() > 0) {
		//FOnlineSessionSearchResult result;
		//result.Session = SearchSettings->SearchResults[0].Session;
		//SearchSettings->SearchResults[0].GetSessionIdStr();
		//FOnlineSubsystemBPCallHelper Helper(TEXT("JoinSession"), GEngine->GetWorldFromContextObject(WorldContextObject));
		//Helper.QueryIDFromPlayerController(PlayerControllerWeakPtr.Get());
		//Sessions->JoinSession(*Helper.UserID, GameSessionName, OnlineSearchResult);
		//SessionInt->joined
		SessionInt->JoinSession(0, GameSessionName, SearchSettings->SearchResults[0]);
	}
}

void UMyGameInstance::OnJoinSessionsComplete(FName sessionName,
	EOnJoinSessionCompleteResult::Type eSessionType)
{
	UE_LOG(LogTemp, Log, TEXT("OnJoinSessionsComplete: %s, result: %d"), *FString(sessionName.ToString()), (int)eSessionType);
	IOnlineSessionPtr SessionInt = Online::GetSessionInterface(GetWorld());
	//SessionInt->JoinSession(0, GameSessionName, SearchSettings->SearchResults[0]); 
	//IOnlineVoicePtr VoiceInterface = Online::GetVoiceInterface();
	//if (VoiceInterface.IsValid()) {
	//	VoiceInterface->StopNetworkedVoice(0);
	//	VoiceInterface->RegisterLocalTalker(0);
	//	VoiceInterface->StartNetworkedVoice(0);
	//}

	FString URL;
	//IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();

	if (SessionInt->GetResolvedConnectString(sessionName, URL))
	{
		auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		pc->ClientTravel(URL, TRAVEL_Absolute);
	}

	FAudioDeviceManager* DeviceManager = GEngine->GetAudioDeviceManager();

	if (DeviceManager && !DeviceManager->IsPlayAllDeviceAudio())
	{
		DeviceManager->TogglePlayAllDeviceAudio();
	}

	bJoinCompleted = true;
}
