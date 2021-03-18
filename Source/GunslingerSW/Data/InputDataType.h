// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GP2EnumTypes.h"
#include "InputCoreTypes.h"
#include "Paper2DClasses.h"
#include "InputDataType.generated.h"

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWKeyboardCorlorArray : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float         Name;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<uint8> Color; ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWKeyIcon : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKey                  Key;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UPaperSprite*> IconArray; ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWKeyMappingInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText         KeyName;                ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName         KeySettingName;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKey          KeyboardKey;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKey          GamepadKey;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGWInputKeyType KeyTyep;                ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float         Scale;                  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool          bGamePadMappingEnable;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool          bKeyboardMappingEnable; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool          bShowInGame;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool          bShowLobby;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString       Description;            ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWShortKeyInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FKey>          KeyArray;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText                 KeyName;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText                 Description;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGWShortKeyType         ShorkeyType;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UPaperSprite*> KeyboardIcon; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UPaperSprite*> PS4Icon;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UPaperSprite*> XBOXIcon;     ///
};



///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWInputKeyInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FKey          Key; /// 

};

