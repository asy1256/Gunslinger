// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "StageDataType.generated.h"

/**
 * 
 */









USTRUCT(BlueprintType)
struct FGWRoomData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int     No;            ///

	UPROPERTY(EditAnywhere)
	FString MasterName;    ;///

	UPROPERTY(EditAnywhere)
	FString GameSessionID; ;///

	UPROPERTY(EditAnywhere)
	FString Map;           ;///
};


USTRUCT(BlueprintType)
struct FGWSubLevel
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString LevelName; ;///
};

USTRUCT(BlueprintType)
struct FGWStreamLevelInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StreamLevelData")
	FName					SubLevelName;

};


USTRUCT(BlueprintType)
struct FGWLoadLevel : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<struct FGWSubLevel> SubLevelInfos; ;///
};


USTRUCT(BlueprintType)
struct FGWStageLoadingInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UTexture2D* Image; ;///
};

USTRUCT(BlueprintType)
struct FGWWorldInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString           Name;         ;///

	UPROPERTY(EditAnywhere)
	FString           Description;  ;///

	UPROPERTY(EditAnywhere)
	class UTexture2D* ThumbTexture; ;///

	UPROPERTY(EditAnywhere)
	FString           MapData;      ;///
};

USTRUCT(BlueprintType)
struct FGWTutorialPageInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Tutorial Page Info" )
	int               PageNumber;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Tutorial Page Info" )
	bool              bIsSuccess;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Tutorial Page Info" )
	FText             Message;               ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Tutorial Page Info" )
	class UTexture2D* KeyBoardIcon;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Tutorial Page Info" )
	class UTexture2D* GamePadIcon;           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Tutorial Page Info" )
	int               MessgeFontSize;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Tutorial Page Info" )
	float             ImageSizeRate;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Tutorial Page Info" )
	FName             MessageID;             ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Tutorial Page Info" )
	float             InvisibleDelaySeconds; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Tutorial Page Info" )
	float             NextWaveDelay;         ///
};



USTRUCT(BlueprintType)
struct FGWTutorialInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString                   TutorialName;       ;///

	UPROPERTY(EditAnywhere)
	TArray<struct FGWTutorialPageInfo> TutorialPagesInfo;  ;///

	UPROPERTY(EditAnywhere)
	bool                      bIsTutorialSuccess; ;///
};
















USTRUCT(BlueprintType)
struct FGWMapInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MapName;   ;///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StageName; ;///

};
