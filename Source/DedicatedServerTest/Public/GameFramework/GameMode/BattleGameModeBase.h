// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "BattleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEDICATEDSERVERTEST_API ABattleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABattleGameModeBase();
	virtual void BeginPlay() override;

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	TSubclassOf<AGameSession> GetGameSessionClass() const override;
public:

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	//	TSubclassOf<ACharacter> MasterCharacterClass;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
		//TSubclassOf<ACharacter> VisitorCharacterClass;

private:
	TArray<APlayerController*> PlayerControllerList;
	
	
};
