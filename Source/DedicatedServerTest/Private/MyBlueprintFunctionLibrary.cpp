// Fill out your copyright notice in the Description page of Project Settings.

#include "DedicatedServerTest.h"
#include "MyBlueprintFunctionLibrary.h"





void UMyBlueprintFunctionLibrary::AddOnScreenDebugMessage(const char* format, ...) {
	char buf[1024];
	va_list argptr;
	va_start(argptr, format);
	vsprintf_s(buf, format, argptr);
	va_end(argptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,
		FString("LOG: ") + buf);
}



FRotator UMyBlueprintFunctionLibrary::GetCameraDirection(APlayerController* PC)
{
	return PC->PlayerCameraManager->GetCameraRotation();
}