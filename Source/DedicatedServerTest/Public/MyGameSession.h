// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameSession.h"
#include "MyGameSession.generated.h"

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERTEST_API AMyGameSession : public AGameSession
{
	GENERATED_BODY()
	
public:
	/** Allow a dedicated server a chance to register itself with an online service */
	virtual void RegisterServer() override;

	virtual bool GetSessionJoinability(FName InSessionName, FJoinabilitySettings& OutSettings) override;

	

	virtual FString ApproveLogin(const FString& Options) override;
};
