// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GP2EnumTypes.h"
#include "GamePlayDataType.generated.h"



USTRUCT(BlueprintType)
struct FGWConnectUserInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		int UserSN;
	UPROPERTY(EditAnywhere)
		FString PlayerSessionID;
};



USTRUCT(BlueprintType)
struct FGWSpawnPoint
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		int UserSn;
	UPROPERTY(EditAnywhere)
		FTransform SpawnPoint;
};


USTRUCT(BlueprintType)
struct FGWMissionInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		EGWMissionType MissionType;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FName        TargetMonsterTag; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float        WaveTick;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		int          WaveTime;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float        TotalWaveCount;   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		int          KillCount;        ///
};

USTRUCT(BlueprintType)
struct FSetting
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float MouseSensitivity;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		bool  MouseInvertX;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		bool  MouseInvertY;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float MouseAcceleration; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float LookSensitivity;   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		bool  LookInvertX;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		bool  LookInvertY;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		bool  AutoAimSurpport;   ///
};


USTRUCT(BlueprintType)
struct FGWTeamInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FName        TeamName;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FLinearColor TeamColor; ///
};


USTRUCT(BlueprintType)
struct FGWVoiceInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		TArray< class USoundCue* > Voices; ///
};
USTRUCT(BlueprintType)
struct FGWVoiceLipSyncTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		class USoundBase* VoiceData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		UDataTable* LipSyncData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float LipScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		bool EnableFacial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		class UCurveFloat* EyeBrowAnger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float EyeBrowAngerScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		class UCurveFloat* SmileMouth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float SmileMouthScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		class UCurveFloat* SmlieRightMouth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float SmileRightMouthScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		class UCurveFloat* AngryFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float AngryFaceScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		class UCurveFloat* AngryEye;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float AngryEyeScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		class UCurveFloat* AngryLeftEye;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float AngryLeftEyeScale;
};


USTRUCT( BlueprintType )
struct FGWLipSyncVisemes : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Lip Synyc" )
	TArray< float > Visemes; ///
};



USTRUCT(BlueprintType)
struct FGWCommonInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float Value;
};


USTRUCT(BlueprintType)
struct FGWConstInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FString Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FString Desc;
};

USTRUCT(BlueprintType)
struct FGWQuestInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString         ChapterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName           ChapterNameID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D*     ChapterImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray< FName > QuestItemLists;

};

USTRUCT(BlueprintType)
struct FGWSequenceInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	/*UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	ULevelSequence*                     Sequence;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	FMovieSceneSequencePlaybackSettings Setting;             */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		TArray<FName>                       NeedStreamingLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float                               FadeInTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float                               FadeOutTime;
};

USTRUCT(BlueprintType)
struct FGWActorStatTypeInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		EActorStatType ActorStatType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		bool Percent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FString IconName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FString Description;

};

