// Fill out your copyright notice in the Description page of Project Settings.


#include "LogitechSDKBPLibrary.h"
#if !WITH_GAMELIFT && PLATFORM_WINDOWS
#include "ILogitechG.h"
#endif


ULogitechSDKBPLibrary::ULogitechSDKBPLibrary(const FObjectInitializer& ObjectInitializer) //___HACK_UE4_VERSION_4_9_OR_GREATER
	: Super(ObjectInitializer)
{
#if !WITH_GAMELIFT && PLATFORM_WINDOWS
	FModuleManager::LoadModuleChecked<IModuleInterface>("LogitechG");

	if (ILogitechG::IsAvailable())
	{
		ILogitechG::Get().LedInit();
	}
#endif
}



bool ULogitechSDKBPLibrary::LogitechGInit()
{
#if WITH_GAMELIFT || PLATFORM_PS4
	return true;
#else
	FModuleManager::LoadModuleChecked<IModuleInterface>("LogitechG");
	//ILogitechG::Get().StartupModule();

	if (ILogitechG::IsAvailable())
	{
		return ILogitechG::Get().LedInit();
	}

	return false;
#endif
}

bool ULogitechSDKBPLibrary::UpdateLighting(const FLinearColor & colorParam)
{
#if WITH_GAMELIFT || PLATFORM_PS4
	return true;
#else
	ILogitechG::Get().LedInit();
	return ILogitechG::Get().LedSetLightingByFColor(colorParam.ToFColor(false));
#endif
}

bool ULogitechSDKBPLibrary::UpdateFlashLighting(const FLinearColor & colorParam, const int milliSecondsDuration, const int milliSecondsInterval)
{
#if WITH_GAMELIFT || PLATFORM_PS4
	return true;
#else
	ILogitechG::Get().LedInit();
	return ILogitechG::Get().LedFlashLightingByFColor(colorParam.ToFColor(false), milliSecondsDuration, milliSecondsInterval);
#endif
}

bool ULogitechSDKBPLibrary::UpdatePulseLighting(const FLinearColor & colorParam, const int milliSecondsDuration, const int milliSecondsInterval)
{
#if WITH_GAMELIFT || PLATFORM_PS4
	return true;
#else
	ILogitechG::Get().LedInit();
	return ILogitechG::Get().LedPulseLightingByFColor(colorParam.ToFColor(false), milliSecondsDuration, milliSecondsInterval);
#endif
}