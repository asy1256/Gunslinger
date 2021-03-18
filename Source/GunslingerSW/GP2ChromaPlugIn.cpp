// Fill out your copyright notice in the Description page of Project Settings.

#include "GP2ChromaPlugIn.h"
#if defined( USING_CHROMA )
#include "ChromaSDKPluginBPLibrary.h"
#endif 
#include "GunslingerSW.h"


bool UGP2ChromaPlugIn::IsInitialized()
{
#if defined( USING_CHROMA )
	return UChromaSDKPluginBPLibrary::IsInitialized();
#else
	return false;
#endif
}

void UGP2ChromaPlugIn::ClearAll()
{
#if defined( USING_CHROMA )
	UChromaSDKPluginBPLibrary::ClearAll();
#endif
}

int32 UGP2ChromaPlugIn::ChromaSDKInit()
{
#if defined( USING_CHROMA )
	return UChromaSDKPluginBPLibrary::ChromaSDKInit();
#else
	return -1;
#endif
}

int32 UGP2ChromaPlugIn::ChromaSDKUnInit()
{
#if defined( USING_CHROMA )
	return UChromaSDKPluginBPLibrary::ChromaSDKUnInit();
#else
	return -1;
#endif
}

void UGP2ChromaPlugIn::PlayAnimations(const TArray<FString>& animationNames, bool loop)
{
#if defined( USING_CHROMA )
	UChromaSDKPluginBPLibrary::PlayAnimations(animationNames, loop);
#endif 
}

void UGP2ChromaPlugIn::PlayAnimation(const FString& animationName, bool loop)
{
#if defined( USING_CHROMA )
	UChromaSDKPluginBPLibrary::PlayAnimation(animationName, loop);
#endif
}

bool UGP2ChromaPlugIn::IsAnimationPlaying(const FString& animationName)
{
#if defined( USING_CHROMA )
	return UChromaSDKPluginBPLibrary::IsAnimationPlaying(animationName);
#else
	return false;
#endif
}