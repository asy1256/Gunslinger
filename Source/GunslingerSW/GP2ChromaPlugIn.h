// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GP2ChromaPlugIn.generated.h"


/**
 * 
 */


UCLASS()
class GUNSLINGERSW_API UGP2ChromaPlugIn : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsInitialized", Keywords = "Return true if the blueprint library is initialized"), Category = "ChromaSDK Wrap")
	static bool IsInitialized();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ClearAll", Keywords = "Clear all devices"), Category = "ChromaSDK Wrap")
	static void ClearAll();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Init", Keywords = "Initialize the ChromaSDK"), Category = "ChromaSDK Wrap")
	static int32 ChromaSDKInit();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "UnInit", Keywords = "Uninitialize the ChromaSDK"), Category = "ChromaSDK Wrap")
	static int32 ChromaSDKUnInit();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PlayAnimations", Keywords = "Play an array of *.chroma Animations"), Category = "ChromaSDK Wrap")
	static void PlayAnimations(const TArray<FString>& animationNames, bool loop);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PlayAnimation", Keywords = "Play the *.chroma Animation"), Category = "ChromaSDK Wrap")
	static void PlayAnimation(const FString& animationName, bool loop);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsAnimationPlaying", Keywords = "Is the *.chroma Animation playing?"), Category = "ChromaSDK Wrap")
	static bool IsAnimationPlaying(const FString& animationName);

};
