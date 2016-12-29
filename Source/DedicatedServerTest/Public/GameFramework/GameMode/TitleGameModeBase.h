// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "TitleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERTEST_API ATitleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;

	virtual void BeginPlay() override;
	
	
	
};
