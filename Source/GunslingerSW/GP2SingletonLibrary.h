// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GP2GameInstance.h"
#include "GP2SingletonLibrary.generated.h"


void Gp2SingletonStartup();
void Gp2SingletonCleanup();

UCLASS()
class GUNSLINGERSW_API UGP2SingletonLibrary
	:
	public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UGP2SingletonLibrary();

public:
	UFUNCTION( BlueprintPure , Category = "GUNS2 Singleton" )
	static UGP2GameInstance* GetGp2GameInst();
};

inline UGP2GameInstance* GetGameInstPtr()
{
	return UGP2SingletonLibrary::GetGp2GameInst();
}
