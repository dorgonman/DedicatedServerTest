// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"

#include "Interfaces/OnlineSessionInterface.h"
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
	
private:
	// The delegate executed by the online subsystem
	FOnFindSessionsCompleteDelegate Delegate;

	// Handle to the registered OnFindSessionsComplete delegate
	FDelegateHandle DelegateHandle;
	TSharedRef<FOnlineSessionSearch> SearchSettings;
};
