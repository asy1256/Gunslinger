// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "GP2EnumTypes.h"
#include "Engine/Texture2D.h"
#include "Engine/StaticMesh.h"
#include "Sound/SoundCue.h"
#include "ItemDataType.generated.h"


///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWItemInfo : public FTableRowBase
{
	GENERATED_BODY()


public:
	FGWItemInfo()
	:
	Name                ( "" ) ,
	Description         ( "" ),
	ThubTexture         ( nullptr ) ,
	ItemType            ( EGWItemType::None ) ,
	ItemSubType         ( EGWItemSubType::SMG ) ,
	ReferenceKey        ( 0 ) ,
	itemTier            ( 1 ) ,
	bInventoryStackable ( false ) ,
	bAllowDelete        ( true ) ,
	MaxStackQuantity    ( 99 ) ,
	ItemOptionGroupId   ( TEXT( "" ) ) ,
	ItemOptionNum       ( 0 ) ,
	ItemUniqueOptionId  ( 0 ) ,
	bRandomOption       ( true ) ,
	Price               ( 1000 ) ,
	Durability          ( 1000 ) ,
	CharacterId         ( 0 ),
	Cost                ( 0 ),
	CostLimit           ( 0 )
	{
	}


public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		FString      Name;                ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		FString      Description;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		UTexture2D*  ThubTexture;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		EGWItemType    ItemType;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		EGWItemSubType ItemSubType;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		int32        ReferenceKey;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		int32        itemTier;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		bool         bInventoryStackable; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		bool         bAllowDelete;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		int32        MaxStackQuantity;    ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		FString      ItemOptionGroupId;   ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		int32        ItemOptionNum;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		int32        ItemUniqueOptionId;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		bool         bRandomOption;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		int32        Price;               ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		int32        Durability;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		int32        CharacterId;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		int32        Cost;         ///
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemInfo" )
		int32        CostLimit;         ///

};

///============================================================================
/// Name	: 
///============================================================================
//USTRUCT(BlueprintType)
//struct FGWPCQuestItem
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest")
//	FName TargetItemID = FName(); ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest")
//	int32 MaxCount     = 0;       ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest")
//	int32 CurrentCount = 0;       ///
//};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWDefultItemCount
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID = FName(); ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count  = 0;       ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWQuestItemInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	FString                         QuestItemName        = TEXT("");            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	FName                           QuestItemNameID      = TEXT("");            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	EGWQuestType                      QuestType            = EGWQuestType::Hunting; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	TArray<struct FGWDefultItemCount> TargetList           ;                    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	TArray<struct FGWDefultItemCount> RewardItemList       ;                    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	FName                           RewardItemID         = TEXT("");            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	TArray<FName>                   MapInfoIds           ;                    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	FName                           NPCID                = TEXT("");            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	FString                         QuestDescription     = TEXT("");            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	FString                         QuestDescriptionID   = TEXT("");            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	FString                         CompletDescription   = TEXT("");            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	FName                           CompletDescriptionId = TEXT("");            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	int32                           RewardExp            = 0;                   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData/Quest/Info")
	int32                           RewardMoney          = 0;                   ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWDropItemInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D*      Icon       ;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32            ItemRefId  = 0;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32            ItemAmount = 0;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh*     ItemMesh   ;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ItemFX     ;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float            LifeTime   = 0.0f; ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWInstantItemInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString          TempName        = TEXT("");               ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGWInstantItemType EffectApplyType = EGWInstantItemType::Heal; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString          Skill_ID        = TEXT("");               ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float            EffectDuration  = 0.5f;                   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float            TickInterval    = 0.0f;                   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* VFX             ;                       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue*       SFX             ;                       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName            AttachPoinName  = TEXT("Bip001-Pelvis");  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector          LocationOffset  = FVector::ZeroVector;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float            Param1          = 0.0f;                   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float            Param2          = 0.0f;                   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float            Param3          = 0.0f;                   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float            Param4          = 0.0f;                   ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32         Uid            = 0; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32         ItemId         = 0; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> OptionIdList   ;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32         UniqueOptionId = 0; ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWItemBoxInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString          Name          = TEXT("DefaultName"); ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32            Durability    = 1000;                ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float            InnerRadius   = 150.0f;              ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float            OuterRadius   = 250.0f;              ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* DestroyEffect ;                    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName>DropItemId;///

};

/*
///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	int32           Uid        = 0;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	int32           ItemId     = 0;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	int32           Amount     = 0;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	int32           Durability = 0;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	TArray<int32>   OptionIds  ;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	TArray<FString> PartIds    ;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	bool            bIsEquiped = false; ///

};
*/
///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWItemOptionInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
		EGWOptionTarget OptionApplyTarget;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
		EGWStatType OptionType;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
		EGWStatCalculateType CalculateType;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
		float Value_1;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
		float Value_2;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
		float Value_3;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
		float Value_4;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
		FString Description;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
		FString StringId;

	FGWItemOptionInfo() : Value_1( 0.0f ) , Value_2( 0.0f ) , Value_3( 0.0f ) , Description( "" ) , StringId( "" )
	{
	}
	///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWItemOptionGroupInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32         GroupId = 0; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> Options ;  ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWRewardItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RefItemId  = TEXT(""); ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinCount   = 0;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxCount   = 0;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RandomRate = 0;        ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWRewardData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FGWRewardItem RewardItem;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32              MinItemCount = 0; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32              MaxItemCount = 0; ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWBuildingDestroyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FGWRewardItem RewardItem;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32              MinItemCount = 0; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32              MaxItemCount = 0; ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWSeamData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	AActor*               ConnetBulid;        ///

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshDecalComponent; ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWSeamSettingData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UStaticMesh* MeshDacal;          ///

	UPROPERTY(EditAnywhere)
	AActor*      ConnectActor;       ///

	UPROPERTY(EditAnywhere)
	FTransform   ReleativeTransform; ///
};

