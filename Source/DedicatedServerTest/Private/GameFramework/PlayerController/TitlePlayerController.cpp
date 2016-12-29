// Fill out your copyright notice in the Description page of Project Settings.

#include "DedicatedServerTest.h"
#include "TitlePlayerController.h"





//check void FOnlineSubsystemModule::LoadDefaultSubsystem(), it will try to get OnlineSubsystem section in DefaultEngine.ini: 
// DefaultPlatformService=Horizon
// DefaultPlatformService_Windows = Steam
// Try to get DefaultPlatformService_Windows, if not then get DefaultPlatformService


ATitlePlayerController::ATitlePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

}


void ATitlePlayerController::BeginPlay()
{
	Super::BeginPlay();

	//EOnJoinSessionCompleteResult::Type eSessionType;
	//UE_LOG(LogTemp, Log, TEXT("numSessions: %d"), (int)eSessionType);
	/*IOnlineVoicePtr VoiceInterface = Online::GetVoiceInterface();
	if (VoiceInterface.IsValid()) {
	VoiceInterface->RegisterLocalTalker(0);
	VoiceInterface->StopNetworkedVoice(0);
	VoiceInterface->StartNetworkedVoice(0);
	}
	FAudioDeviceManager* DeviceManager = GEngine->GetAudioDeviceManager();

	if (DeviceManager && !DeviceManager->IsPlayAllDeviceAudio())
	{
	DeviceManager->TogglePlayAllDeviceAudio();
	}*/
}


