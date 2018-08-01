// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "MyPlayerController.generated.h"


//https://answers.unrealengine.com/questions/49442/trying-to-make-in-game-voice-communication.html
/**
 * 
 */
UCLASS()
class DEDICATEDSERVERTEST_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();
	virtual void BeginPlay() override;



public:
	UFUNCTION()
	virtual void OnFindSessionsComplete(bool bSuccess);

	//UFUNCTION()
	virtual void OnJoinSessionsComplete(FName sessionName, EOnJoinSessionCompleteResult::Type eSessionType);
private:
	// The delegate executed by the online subsystem
	FOnFindSessionsCompleteDelegate FindSessionCompeteDelegate;
	TSharedRef<FOnlineSessionSearch> SearchSettings;


	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
};
