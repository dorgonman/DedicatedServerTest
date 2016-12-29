// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERTEST_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();
	virtual void Init() override;

#if WITH_EDITOR
	/* Called to initialize the game instance for PIE instances of the game */
	virtual bool InitializePIE(bool bAnyBlueprintErrors, int32 PIEInstance, bool bRunAsDedicated) override;

	virtual bool StartPIEGameInstance(ULocalPlayer* LocalPlayer, bool bInSimulateInEditor, bool bAnyBlueprintErrors, bool bStartInSpectatorMode) override;

#endif

	virtual void StartGameInstance() override;
	virtual bool JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults) override;
	virtual bool JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult) override;

	virtual void FindAndJoinSessions();
public:
	UFUNCTION()
	virtual void OnFindSessionsComplete(bool bSuccess);
	virtual void OnJoinSessionsComplete(FName sessionName, EOnJoinSessionCompleteResult::Type eSessionType);
private:
	// The delegate executed by the online subsystem
	FOnFindSessionsCompleteDelegate FindSessionCompeteDelegate;
	TSharedRef<FOnlineSessionSearch> SearchSettings;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	bool bJoinCompleted = false;
	
};
