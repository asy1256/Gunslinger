// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GP2EnumTypes.h"
#include "ItemDataType.h"
#include "Animation/AnimMontage.h"
#include "Animation/BlendSpaceBase.h"
#include "CharacterDataType.generated.h"

//////////// Character //////////////




///============================================================================
/// Name	: FCharacterExpInfo
///============================================================================
USTRUCT(BlueprintType)
struct FGWCharacterExpInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWCharacterExpInfo()
	:
	ExpForLevelUp( 0 )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Exp" )
	int32 ExpForLevelUp; /// 레벨업 필요경험치
};







///////// ProxyCharacter ////////////
///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWProxyCharacterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWProxyCharacterInfo()
		:
		Name( "" ),
		Anim( nullptr )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString                            Name; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	TSubclassOf< class UAnimInstance > Anim; ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWProxyCameraLevel
{
	GENERATED_BODY()

public:
	FGWProxyCameraLevel()
		:
		FOV( 0.0f ) ,
		Location( FVector::ZeroVector ) ,
		Rotation( FRotator( 0,0,0 ) )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float    FOV;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FVector  Location; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FRotator Rotation; ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWProxyCameraSetting: public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWProxyCameraSetting()
	:
	Desc( "" )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString           Desc;   ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	struct FGWProxyCameraLevel Level1; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	struct FGWProxyCameraLevel Level2; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	struct FGWProxyCameraLevel Level3; ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWLobbyWidgetInfo: public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWLobbyWidgetInfo()
	/*:
	MenuName( TEXT( "" ) ) ,
	WidgetClass( nullptr )*/
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FText                            MenuName;    ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	TSubclassOf< class UUserWidget > WidgetClass; ///
};




///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWCameraSettings : public FTableRowBase
{
	GENERATED_BODY()


public:
	FGWCameraSettings()
	:               
	TargetArmLength ( 0.0f ) ,
	CameraLagSpeed  ( 0.0f ) ,
	SocketOffset    ( FVector::ZeroVector ) ,
	Fov             ( 0.0f )
	{
	}

public:
	UPROPERTY(EditAnywhere)
	float   TargetArmLength; ///

	UPROPERTY(EditAnywhere)
	float   CameraLagSpeed;  ///

	UPROPERTY(EditAnywhere)
	FVector SocketOffset;    ///

	UPROPERTY(EditAnywhere)
	float   Fov;             ///
};


///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWComboInfo
{
	GENERATED_BODY()

public:
	FGWComboInfo()
	:
	Animation      ( nullptr ),
	SavaAttackTime ( 0.0f ),
	ResetComboTime ( 0.0f )
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Animation;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float         SavaAttackTime; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float         ResetComboTime; ///
};





////////////NPC///////////
///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWNpcInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWNpcInfo()
	:
	NPCImage( nullptr )
	{
	}

public:
	UPROPERTY(EditAnywhere)
	FName       NPCName;       ///

	UPROPERTY(EditAnywhere)
	FName       NPCNameID;     ///

	UPROPERTY(EditAnywhere)
	FName       NPCPosition;   ///

	UPROPERTY(EditAnywhere)
	FName       NPCPositionID; ///

	UPROPERTY(EditAnywhere)
	UTexture2D* NPCImage;      ///
};


///========================================================================================================================================================
/// 통합 또는 삭제예정
///========================================================================================================================================================

//////Character Custom /////
///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWCostumeInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWCostumeInfo()
	:           
	Mesh        ( nullptr ),
	ThubTexture ( nullptr )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString        Desc;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	USkeletalMesh* Mesh;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	UTexture2D*    ThubTexture; ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWCostume : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWCostume()
	:
	HairPartsId( 0 ) ,
	FacePartsID( 0 ) ,
	BodyPartsID( 0 )
	{
	}

public:
	UPROPERTY( EditAnywhere )
		int     HairPartsId; ///

	UPROPERTY( EditAnywhere )
		int     FacePartsID; ///

	UPROPERTY( EditAnywhere )
		int     BodyPartsID; ///

	UPROPERTY( EditAnywhere )
		FString Description; ///
};


///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWParts
{
	GENERATED_BODY()


public:
	FGWParts()
	:     
	Face  ( 0       ) ,
	Hair  ( 0       ) ,
	Body  ( 0       ) ,
	Thumb ( nullptr )
	{
	}

public:
	UPROPERTY( EditAnywhere )
		int         Face;  ///

	UPROPERTY( EditAnywhere )
		int         Hair;  ///

	UPROPERTY( EditAnywhere )
		int         Body;  ///

	UPROPERTY( EditAnywhere )
		UTexture2D* Thumb; ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWPVPPresetCharacterInfo : public FTableRowBase
{
	GENERATED_BODY()


public:
	FGWPVPPresetCharacterInfo()
	:
	WeaponId1( 0 ) ,
	WeaponId2( 0 ) ,
	WeaponId3( 0 )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	int    WeaponId1;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	int    WeaponId2;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	int    WeaponId3;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	struct FGWParts RedTeamPreset;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	struct FGWParts BlueTeamPreset; ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWPreset : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWPreset()
	:
	Weapon( 0 )
	{
	}

public:
	UPROPERTY( EditAnywhere )
		TArray<struct FGWParts> Parts;       ///

	UPROPERTY( EditAnywhere )
		int            Weapon;      ///

	UPROPERTY( EditAnywhere )
		FString        Description; ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWVirtualCharacter : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWVirtualCharacter()
	:
	CharacterInfoId ( 0 ) ,
	CostumeInfoId   ( 0 ) ,
	FaceInfoId      ( 0 ) ,
	HairInfoId      ( 0 ) ,
	BodyInfoId      ( 0 )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	int         CharacterInfoId; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	int         CostumeInfoId;   ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	FString     Name;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	int         FaceInfoId;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	int         HairInfoId;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	int         BodyInfoId;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	TArray<int> WeaponSlot;      ///
};


///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWCharacterParts : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWCharacterParts()
		:
		Mesh( nullptr )
	{
	}

public:
	UPROPERTY( EditAnywhere )
		USkeletalMesh* Mesh;        ///

	UPROPERTY( EditAnywhere )
		FString        Description; ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWCharacterSlot
{
	GENERATED_BODY()

public:
	FGWCharacterSlot ()
	:             
	SlotIndex     ( 0 ) ,
	InfoId        ( 0 ) ,
	CostumeInfoId ( 0 )
	{
	}

public:
	UPROPERTY( EditAnywhere )
		int     SlotIndex;     ///
	UPROPERTY( EditAnywhere )
		int     InfoId;        ///
	UPROPERTY( EditAnywhere )
		int     CostumeInfoId; ///
	UPROPERTY( EditAnywhere )
		FString Name;          ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWCharacterExInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWCharacterExInfo()
	:       
	Thumb1  ( nullptr ) ,
	Thumb2  ( nullptr ) ,
	Thumb3  ( nullptr ) ,
	Ability ( nullptr )
	{
	}

public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "CharacterInfo/EX" )
		FName       Name;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "CharacterInfo/EX" )
		FName       Desc;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "CharacterInfo/EX" )
		FName       PrimaryWeapon; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "CharacterInfo/EX" )
		UTexture2D* Thumb1;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "CharacterInfo/EX" )
		UTexture2D* Thumb2;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "CharacterInfo/EX" )
		UTexture2D* Thumb3;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "CharacterInfo/EX" )
		UTexture2D* Ability;       ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWPCInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWPCInfo()
	:             
	Mesh          ( nullptr ) ,
	ThumbTexture  ( nullptr ) ,
	ThumbTexture2 ( nullptr ) ,
	ThumbTexture3 ( nullptr ) ,
	ThumbTexture4 ( nullptr )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	USkeletalMesh*                     Mesh;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	TSubclassOf< class UAnimInstance > Animation;     ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	UTexture2D*                        ThumbTexture;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	UTexture2D*                        ThumbTexture2; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	UTexture2D*                        ThumbTexture3; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	UTexture2D*                        ThumbTexture4; ///

};