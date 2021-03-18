// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LogitechSDKBPLibrary.generated.h"


/**
 * 
 */
UCLASS()
class GUNSLINGERSW_API ULogitechSDKBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

		//ULogitechSDKBPLibrary();

	UFUNCTION(BlueprintCallable, Category = "LogitechG")
	static bool LogitechGInit();

	UFUNCTION(BlueprintCallable, Category = "LogitechG")
	static bool UpdateLighting(const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, Category = "LogitechG")
	static bool UpdateFlashLighting(const FLinearColor& colorParam, const int milliSecondsDuration, const int milliSecondsInterval);

	UFUNCTION(BlueprintCallable, Category = "LogitechG")
	static bool UpdatePulseLighting(const FLinearColor& colorParam, const int milliSecondsDuration, const int milliSecondsInterval);
	
private:


	
	
};
