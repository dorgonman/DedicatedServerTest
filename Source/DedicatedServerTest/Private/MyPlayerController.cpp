// Fill out your copyright notice in the Description page of Project Settings.

#include "DedicatedServerTest.h"
#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController() 
	:SearchSettings(new FOnlineSessionSearch())
{

	SearchSettings->bIsLanQuery = false;
	if (GEngine->GetNetMode(GetWorld()) != NM_DedicatedServer)
	{
		FindSessionCompeteDelegate.BindUObject(this, &AMyPlayerController::OnFindSessionsComplete);
		JoinSessionCompleteDelegate.BindLambda([this](FName sessionName,
			EOnJoinSessionCompleteResult::Type eSessionType) 
		{
			OnJoinSessionsComplete(sessionName, eSessionType);
		});
			//(this, &AMyPlayerController::OnJoinSessionsComplete);
	}

}


void AMyPlayerController::BeginPlay()
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

}



void AMyPlayerController::OnFindSessionsComplete(bool bSuccess)
{
	UE_LOG(LogTemp, Log, TEXT("OnFindSessionCompleteDelegate: %d"), bSuccess);
	IOnlineSessionPtr SessionInt = Online::GetSessionInterface(GetWorld());
	int numSessions = SessionInt->GetNumSessions();
	UE_LOG(LogTemp, Log, TEXT("numSessions: %d"), numSessions);
	if (SearchSettings->SearchResults.Num() > 0) {
		FOnlineSessionSearchResult result;
		result.Session = SearchSettings->SearchResults[0].Session;
		//SearchSettings->SearchResults[0].GetSessionIdStr();
		SessionInt->JoinSession(0, "Game", result);
	}
}

void AMyPlayerController::OnJoinSessionsComplete(FName sessionName,
	EOnJoinSessionCompleteResult::Type eSessionType)
{
	UE_LOG(LogTemp, Log, TEXT("OnJoinSessionsComplete: %s, result: %d"), *FString(sessionName.ToString()), (int)eSessionType);
}
