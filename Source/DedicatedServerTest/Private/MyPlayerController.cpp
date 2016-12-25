// Fill out your copyright notice in the Description page of Project Settings.

#include "DedicatedServerTest.h"
#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController() 
	:SearchSettings(new FOnlineSessionSearch())
{

	SearchSettings->bIsLanQuery = false;
	if (GEngine->GetNetMode(GetWorld()) != NM_DedicatedServer)
	{
		Delegate.BindLambda([this](bool bSuccess)
		{
			UE_LOG(LogTemp, Log, TEXT("OnFindSessionCompleteDelegate: %d"), bSuccess);
			IOnlineSessionPtr SessionInt = Online::GetSessionInterface(GetWorld());
			int numSessions = SessionInt->GetNumSessions();
			UE_LOG(LogTemp, Log, TEXT("numSessions: %d"), numSessions);
			FOnlineSessionSearchResult result;
			SessionInt->JoinSession(0, "TestRoom", result);
		});
	}

}


void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine->GetNetMode(GetWorld()) != NM_DedicatedServer)
	{
		IOnlineSessionPtr SessionInt = Online::GetSessionInterface(GetWorld());
		//FOnlineSessionSettings settings;
		//settings.bIsLANMatch = false;
		//settings.bIsDedicated = false;
		//FName testRoom = "TestRoom2";
		//
		//SessionInt->CreateSession(0, testRoom, settings);


		//SearchSettings->SearchState = EOnlineAsyncTaskType

		/*DelegateHandle = SessionInt->AddOnFindSessionsCompleteDelegate_Handle(Delegate);
		bool b = SessionInt->FindSessions(0, SearchSettings);
		int numSessions = SessionInt->GetNumSessions();
		UE_LOG(LogTemp, Log, TEXT("numSessions: %d"), numSessions);*/
	}
}