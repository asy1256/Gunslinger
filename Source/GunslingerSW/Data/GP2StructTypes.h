// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP2EnumTypes.h"
#include "GP2StructTypes.generated.h"


class UAnimInstance;
class USkeletalMesh;
class UTexture2D;


//UPROPERTY
//EditAnywhere | VisibleAnywhere
//Replicated
//ReplicatedUsing = FunctionName
//Transient
//Category
//BlueprintReadOnly
//BlueprintReadWrite

/// ItemDataType.h
///----------------------------------------------------------------------------
/// Name	:	FPCQuestItem
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWPCQuestItem
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemData/Quest" )
		FName TargetItemID = FName(); ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemData/Quest" )
		int32 MaxCount = 0;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ItemData/Quest" )
		int32 CurrentCount = 0;       ///
};



/// PlayerDataType.h
///----------------------------------------------------------------------------
/// Name	:	FPlayerCharacterInfo - Decrpyted
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWPlayerCharacterInfo
{
	GENERATED_BODY()

public:
	FGWPlayerCharacterInfo()
	:             
	Mesh          ( nullptr ) ,
	ThumbTexture  ( nullptr ) ,
	ThumbTexture2 ( nullptr ) ,
	ThumbTexture3 ( nullptr ) ,
	ThumbTexture4 ( nullptr )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerData" )
	USkeletalMesh*             Mesh;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerData" )
	TSubclassOf<UAnimInstance> Animation;     ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerData" )
	UTexture2D*                ThumbTexture;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerData" )
	UTexture2D*                ThumbTexture2; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerData" )
	UTexture2D*                ThumbTexture3; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerData" )
	UTexture2D*                ThumbTexture4; ///
};


///----------------------------------------------------------------------------
/// Name	:	FPlayerQuestData
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWPlayerQuestData
{
	GENERATED_BODY()


public:
	FGWPlayerQuestData()
	:
	QuestType  ( EGWQuestType::Hunting ) ,
	QuestState ( EGWQuestState::NONE )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerData/Quest" )
	FName                QuestItemID; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerData/Quest" )
	EGWQuestType           QuestType;   ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerData/Quest" )
	EGWQuestState          QuestState;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerData/Quest" )
	TArray< struct FGWPCQuestItem> TargetList;  ///

};



/// CharacterDataType.h
///----------------------------------------------------------------------------
/// Name	:	FCustomizeInfo
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWCustomizeInfo
{
	GENERATED_BODY()

public:
	FGWCustomizeInfo()
	:
	FaceInfoId( 0 ) ,
	HairInfoId( 0 ) ,
	DressInfoId( 0 )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	int FaceInfoId;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	int HairInfoId;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	int DressInfoId; ///
};

///----------------------------------------------------------------------------
/// Name	: FSpeed
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWSpeed
{
	GENERATED_BODY()

public:
	FGWSpeed()
	:
	Walking( 600.0f ) ,
	Running( 600.0f ) ,
	Sprinting( 600.0f ) ,
	Jumping( 600.0f )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Speed" )
	float Walking;   ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Speed" )
	float Running;   ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Speed" )
	float Sprinting; ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Speed" )
	float Jumping;   ///
};

///----------------------------------------------------------------------------
/// Name	: FAcceleration
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWAcceleration
{
	GENERATED_BODY()


public:
	FGWAcceleration()
	:
	Walking( 600.0f ) ,
	Running( 600.0f ) ,
	Sprinting( 600.0f )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Acceleration" )
	float Walking;   ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Acceleration" )
	float Running;   ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Acceleration" )
	float Sprinting; ///
};


///----------------------------------------------------------------------------
/// Name	: FDeceleration
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWDeceleration
{
	GENERATED_BODY()

public:
	FGWDeceleration()
	:
	Walking( 600.0f ) ,
	Running( 600.0f ) ,
	Sprinting( 600.0f )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Deceleration" )
	float Walking;   ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Deceleration" )
	float Running;   ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Deceleration" )
	float Sprinting; ///
};

///----------------------------------------------------------------------------
/// Name	: FFriction
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWFriction
{
	GENERATED_BODY()

public:
	FGWFriction()
	:
	Walking( 600.0f ) ,
	Running( 600.0f ) ,
	Sprinting( 600.0f )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Friction" )
	float Walking;   ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Friction" )
	float Running;   ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Character Friction" )
	float Sprinting; ///

};



///============================================================================
/// Name	:	
///============================================================================
USTRUCT( BlueprintType )
struct FGWPivotParams
{
	GENERATED_BODY()

public:
	FGWPivotParams()
	:
	PivotDirection               ( 0.0f ) ,
	CompletedMovementDirection   ( EGWMovementDirection::Forward ) ,
	CompletedStartTime           ( 0.0f ) ,
	InterruptedMovementDirection ( EGWMovementDirection::Forward ) ,
	InterruptedStartTime         ( 0.0f )
	{
	}

public:
	UPROPERTY( EditAnywhere )
	float              PivotDirection;               ///

	UPROPERTY( EditAnywhere )
	EGWMovementDirection CompletedMovementDirection;   ///

	UPROPERTY( EditAnywhere )
	float              CompletedStartTime;           ///

	UPROPERTY( EditAnywhere )
	EGWMovementDirection InterruptedMovementDirection; ///

	UPROPERTY( EditAnywhere )
	float              InterruptedStartTime;         ///
};




/// skilldatatype.h
///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWCollisionParam
{
	GENERATED_BODY()

public:
	FGWCollisionParam()
	:
	Radius ( 0.0f ) ,
	Width  ( 0.0f ) ,
	Height ( 0.0f ) ,
	Length ( 0.0f ) ,
	Angle  ( 0.0f ) ,
	Roll   ( 0.0f ) ,
	Pitch  ( 0.0f ) ,
	Yaw    ( 0.0f )
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionParam")
	float Radius; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionParam")
	float Width;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionParam")
	float Height; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionParam")
	float Length; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionParam")
	float Angle;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionParam")
	float Roll;   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionParam")
	float Pitch;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionParam")
	float Yaw;    ///
};


/// ChatDataType.h
///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWChatMessageData
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ChatData" )
		FText     Sender;   ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ChatData" )
		FText     Text;     ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ChatData" )
		EGWChatType ChatType; ///

};



USTRUCT( BlueprintType )
struct FGWLobbyChannelInfo
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "LobbyChannel Info" )
	int     Id;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "LobbyChannel Info" )
	FString IpAddress; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "LobbyChannel Info" )
	int     UserCount; ///

};