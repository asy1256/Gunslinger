// Fill out your copyright notice in the Description page of Project Settings.

#include "LogitechLightComponent.h"

#if !WITH_GAMELIFT && PLATFORM_WINDOWS 
#include "ILogitechG.h"
#endif

// Sets default values for this component's properties
ULogitechLightComponent::ULogitechLightComponent()
{
#if !WITH_GAMELIFT && PLATFORM_WINDOWS
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	FModuleManager::LoadModuleChecked<IModuleInterface>("LogitechG");
	 
	if (ILogitechG::IsAvailable())
	{
		ILogitechG::Get().LedInit();
	}
	// ...
#endif
}


// Called when the game starts
void ULogitechLightComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool ULogitechLightComponent::UpdateLighting(const FLinearColor& colorParam)
{
#if WITH_GAMELIFT || PLATFORM_PS4
	return true;
#else
	return ILogitechG::Get().LedSetLightingByFColor(colorParam.ToFColor(false));
#endif
}

bool ULogitechLightComponent::UpdateFlashLighting(const FLinearColor & colorParam, const int milliSecondsDuration, const int milliSecondsInterval)
{
#if WITH_GAMELIFT || PLATFORM_PS4
	return true;
#else
	return ILogitechG::Get().LedFlashLightingByFColor(colorParam.ToFColor(false), milliSecondsDuration, milliSecondsInterval);
#endif
}

bool ULogitechLightComponent::UpdatePulseLighting(const FLinearColor & colorParam, const int milliSecondsDuration, const int milliSecondsInterval)
{
#if WITH_GAMELIFT || PLATFORM_PS4
	return true;
#else
	return ILogitechG::Get().LedPulseLightingByFColor(colorParam.ToFColor(false), milliSecondsDuration, milliSecondsInterval);
#endif
}

bool ULogitechLightComponent::UpdateLightingfromBitmap(const TArray<uint8>& bitmap)
{
	/*
	#define BUFF_S 504
	int size = bitmap.Num();	

	unsigned char buffer[BUFF_S];	
	for (int i = 0; i < BUFF_S, i<size; i++)
	{
		buffer[i] = (unsigned char)bitmap[i];
	}

	return ILogitechG::Get().LedSetLightingFromBitmap(buffer);

	*/
	
#if WITH_GAMELIFT || PLATFORM_PS4
	return true;
#else
	return ILogitechG::Get().LedSetLightingFromBitmap(bitmap.GetData());
#endif
}

void ULogitechLightComponent::LogitechShutDown()
{
#if !WITH_GAMELIFT && PLATFORM_WINDOWS
	ILogitechG::Get().LedShutdown();
#endif
}

bool ULogitechLightComponent::IsAvailable()
{
#if WITH_GAMELIFT || PLATFORM_PS4
	return true;
#else
	return ILogitechG::IsAvailable();
#endif
}

bool ULogitechLightComponent::LogitechInit()
{
#if WITH_GAMELIFT || PLATFORM_PS4
	return true;
#else
	return ILogitechG::Get().LedInit();
#endif
}


// Called every frame
void ULogitechLightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

