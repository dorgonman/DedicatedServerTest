// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "TitlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERTEST_API ATitlePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATitlePlayerController();
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
