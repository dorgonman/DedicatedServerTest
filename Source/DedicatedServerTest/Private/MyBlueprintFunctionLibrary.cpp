// Fill out your copyright notice in the Description page of Project Settings.
#include "MyBlueprintFunctionLibrary.h"
#include "DedicatedServerTest.h"






void UMyBlueprintFunctionLibrary::AddOnScreenDebugMessage(const char* format, ...) {

}



FRotator UMyBlueprintFunctionLibrary::GetCameraDirection(APlayerController* PC)
{
	return PC->PlayerCameraManager->GetCameraRotation();
}