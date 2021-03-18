// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
// #include "LevelSequence.h"
// #include "MovieSceneSequencePlayer.h"
#include "GP2EnumTypes.h"
#include "SkillDataType.generated.h"










/* Skill Actor Info */
///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWSkillActorInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	FString                   Comment;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	TSubclassOf<class AActor> SpawnActorClass; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	float                     Duration;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	float                     TickInterval;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	EGWSpawnLocationType        SpawnLocType;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	FName                     SpawnSocketName; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	FVector                   SpawnLocOffset;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	FRotator                  SpawnRotOffset;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	float                     Param1;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	float                     Param2;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	float                     Param3;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	float                     Param4;          ///

};


/* Skill Effect info */
///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWSkillEffectInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillEffectData")
	FString     StringId;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillEffectData")
	EGWEffectType EffectType;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillEffectData")
	FString     StatusEffectId; ///
};







/* Status Effect Info */
///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWStatusEffectInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	UTexture2D*							ThumbTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	FString								StringId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	float								Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	float								TickInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	EGWAffectType							AffectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	bool								Stackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	int32								StackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	bool								Infinite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	class UParticleSystem*				ParticleEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	FName								EmitterSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	FVector								EmitterLocOffset;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
//	TSubclassOf<class UStatusEffectBase>	EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	float Param1; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	float Param2; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	float Param3; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffecData")
	float Param4; ///


};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWUltraSkillInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	/*UPROPERTY(EditAnywhere)
	ULevelSequence*                     LevelSequence; ///*/

	/*UPROPERTY(EditAnywhere)
	FMovieSceneSequencePlaybackSettings Setting;       ///*/

	UPROPERTY(EditAnywhere)
	FString                             Description;   ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWStatusEffectsInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	UTexture2D*      ThumbTexture;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FString          StringId;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float            Duration;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float            TickIntervar;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	EGWAffectType      AffectType;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	bool             bStackable;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	int              StackCount;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	bool             bInfinite;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	UParticleSystem* ParticleEmitter;   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	bool             ActorParam;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FName            EmitterSocketName; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FVector          EmitterLocOffset;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float            Param1;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float            Param2;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float            Param3;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float            Param4;            ///
};