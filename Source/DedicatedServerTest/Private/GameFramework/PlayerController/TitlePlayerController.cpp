// Fill out your copyright notice in the Description page of Project Settings.

#include "DedicatedServerTest.h"
#include "TitlePlayerController.h"
#include "AudioDeviceManager.h"


//https://madebykrol.wordpress.com/2015/05/21/unreal-engine-and-online-multiplayer/



ATitlePlayerController::ATitlePlayerController()
	:SearchSettings(new FOnlineSessionSearch())
{

	SearchSettings->bIsLanQuery = false;
	if (GEngine->GetNetMode(GetWorld()) != NM_DedicatedServer)
	{
		FindSessionCompeteDelegate.BindUObject(this, &ATitlePlayerController::OnFindSessionsComplete);
		JoinSessionCompleteDelegate.BindLambda([this](FName sessionName,
			EOnJoinSessionCompleteResult::Type eSessionType)
		{
			OnJoinSessionsComplete(sessionName, eSessionType);
		});
		//(this, &AMyPlayerController::OnJoinSessionsComplete);
	}

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

}


void ATitlePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine->GetNetMode(GetWorld()) != NM_DedicatedServer)
	{
		IOnlineSessionPtr SessionInt = Online::GetSessionInterface(GetWorld());
		SessionInt->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompeteDelegate);
		SessionInt->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);
		bool b = SessionInt->FindSessions(0, SearchSettings);
		int numSessions = SessionInt->GetNumSessions();
		UE_LOG(LogTemp, Log, TEXT("numSessions: %d"), numSessions);
	}
	//EOnJoinSessionCompleteResult::Type eSessionType;
	//UE_LOG(LogTemp, Log, TEXT("numSessions: %d"), (int)eSessionType);
	/*IOnlineVoicePtr VoiceInterface = Online::GetVoiceInterface();
	if (VoiceInterface.IsValid()) {
	VoiceInterface->RegisterLocalTalker(0);
	VoiceInterface->StopNetworkedVoice(0);
	VoiceInterface->StartNetworkedVoice(0);
	}
	FAudioDeviceManager* DeviceManager = GEngine->GetAudioDeviceManager();

	if (DeviceManager && !DeviceManager->IsPlayAllDeviceAudio())
	{
	DeviceManager->TogglePlayAllDeviceAudio();
	}*/
}



void ATitlePlayerController::OnFindSessionsComplete(bool bSuccess)
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

		SessionInt->JoinSession(0, GameSessionName, SearchSettings->SearchResults[0]);
	}
}

void ATitlePlayerController::OnJoinSessionsComplete(FName sessionName,
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
		ClientTravel(URL, TRAVEL_Absolute);
	}

	FAudioDeviceManager* DeviceManager = GEngine->GetAudioDeviceManager();

	if (DeviceManager && !DeviceManager->IsPlayAllDeviceAudio())
	{
		DeviceManager->TogglePlayAllDeviceAudio();
	}
}
