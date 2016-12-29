// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameSession.h"
#include "BattleGameSession.generated.h"

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERTEST_API ABattleGameSession : public AGameSession
{
	GENERATED_BODY()

public:
	/** Allow a dedicated server a chance to register itself with an online service */
	virtual void RegisterServer() override;

	virtual bool GetSessionJoinability(FName InSessionName, FJoinabilitySettings& OutSettings) override;


	/**
	* Travel to a session URL (as client) for a given session
	*
	* @param ControllerId controller initiating the session travel
	* @param SessionName name of session to travel to
	*
	* @return true if successful, false otherwise
	*/
	virtual bool TravelToSession(int32 ControllerId, FName InSessionName) override;


	virtual FString ApproveLogin(const FString& Options) override;
	
	
	
};
