// Fill out your copyright notice in the Description page of Project Settings.

#include "GP2SingletonLibrary.h"
#include "GunslingerSW.h"

void Gp2SingletonStartup()
{
}

void Gp2SingletonCleanup()
{
}


UGP2SingletonLibrary::UGP2SingletonLibrary()
{
}

UGP2GameInstance* UGP2SingletonLibrary::GetGp2GameInst()
{
	if ( !GEngine )
		return nullptr;

#if WITH_EDITOR

	const TIndirectArray< FWorldContext >& WorldContextArray = GEngine->GetWorldContexts();
	for ( int32 i = 0 ; i < WorldContextArray.Num() ; ++i )
	{
		const FWorldContext& worldContext = WorldContextArray[ i ];

		if ( worldContext.WorldType == EWorldType::PIE ||
			worldContext.WorldType == EWorldType::Game )
		{
			return Cast< UGP2GameInstance >( worldContext.OwningGameInstance );
		}
	}

	return nullptr;

#else

#ifndef UE_SERVER
	UGameEngine* GameEngine = Cast< UGameEngine >( GEngine );
	if ( !GameEngine )
		return nullptr;

	return Cast< UGP2GameInstance >( GameEngine->GameInstance );
#endif 
#endif

	return nullptr;
}
