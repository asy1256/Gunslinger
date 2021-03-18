// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP2EnumTypes.h"
#include "Engine/DataTable.h"
#include "GP2StructTypes.h"
#include "GP2DataStructTypes.generated.h"

class UAimOffsetBlendSpace;
class UAnimInstance;
class UBlendSpace;
class UAnimMontage;
class UAnimSequence;
class UAkAudioEvent;

/// PlayerDataType.h
///----------------------------------------------------------------------------
/// Name	:	FPlayerInfo
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWPlayerInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	FGWPlayerInfo()
	:
	UserSn        ( 0 ) ,
	InfoId        ( 0 ) ,
	CostumeInfoId ( 0 ) ,
	Name          ( TEXT( "" ) ) ,
	FaceInfoId    ( 0 ) ,
	HairInfoId    ( 0 ) ,
	BodyInfoId    ( 0 ) ,
	Slot01InfoId  ( 0 ) ,
	Slot02InfoId  ( 0 ) ,
	Slot03InfoId  ( 0 ) ,
	Team          ( 0 ) ,
	TeamSlotNo    ( 0 ) ,
	Level         ( 1 )
	{
	}

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	int32   UserSn;        ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	int32   InfoId;        /// 캐릭터 식별자

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	int32   CostumeInfoId; /// 코스튬 식별자

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	FString Name;          /// 캐릭터 이름

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	int32   FaceInfoId;    /// 얼굴파츠 식별자

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	int32   HairInfoId;    /// 헤어파츠 식별자

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	int32   BodyInfoId;    /// 몸통파트 식별자

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	int32   Slot01InfoId;  /// 1무기 식별자

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	int32   Slot02InfoId;  /// 2무기 식별자

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	int32   Slot03InfoId;  /// 3무기 식별자

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	int32   Team;          /// 팀 식별자

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	uint8   TeamSlotNo;    /// 팀 슬롯 인덱스

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info" )
	int32   Level;         /// 레벨

};

///----------------------------------------------------------------------------
/// Name	:	FPvpPlayerInfo
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWPvpPlayerInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWPvpPlayerInfo()
	:
	BaseInfoId   ( 0          ) ,
	Name         ( TEXT( "" ) ) ,
	Slot01InfoId ( 0          ) ,
	Slot02InfoId ( 0          ) ,
	Slot03InfoId ( 0          )        
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info(PVP)" )
	int                   BaseInfoId;   ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info(PVP)" )
	FString               Name;         ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info(PVP)" )
	int                   Slot01InfoId; /// 1무기 인덱스

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info(PVP)" )
	int                   Slot02InfoId; /// 2무기 인덱스

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info(PVP)" )
	int                   Slot03InfoId; /// 3무기 인덱스

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info(PVP)" )
	struct FGWCustomizeInfo RedTeam;      /// 레드팀 외형정보

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Player Info(PVP)" )
	struct FGWCustomizeInfo BlueTeam;     /// 블루팀 외형정보

};





///----------------------------------------------------------------------------
/// Name	: 
///----------------------------------------------------------------------------
/////// Animation /////////
///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWAnimationListInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWAnimationListInfo()
	:
	NAdd               ( nullptr ) ,
	LFAdd              ( nullptr ) ,
	NPose              ( nullptr ) ,
	LFPose             ( nullptr ) ,
	NToLF              ( nullptr ) ,
	LFToN              ( nullptr ) ,
	LFMove             ( nullptr ) ,
	NMoveF             ( nullptr ) ,
	NMove              ( nullptr ) ,
	LFMoveAim          ( nullptr ) ,
	NLeanGrounded      ( nullptr ) ,
	NLeanDash          ( nullptr ) ,
	NLeanInAir         ( nullptr ) ,
	AirMoveAim         ( nullptr ) ,
	NStopLF            ( nullptr ) ,
	NStopRF            ( nullptr ) ,
	LFStop             ( nullptr ) ,
	PivotF             ( nullptr ) ,
	SprintBegin        ( nullptr ) ,
	SprintLoop         ( nullptr ) ,
	SprintStop         ( nullptr ) ,
	Land               ( nullptr ) ,
	LandHigh           ( nullptr ) ,
	FallLoop           ( nullptr ) ,
	FallLoopHigh       ( nullptr ) ,
	JumpBegin          ( nullptr ) ,
	AirSprintStart     ( nullptr ) ,
	AirSprintLoop      ( nullptr ) ,
	AirJumpBegin       ( nullptr ) ,
	AirJumpLoop        ( nullptr ) ,
	AimOffset          ( nullptr ) ,
	LFTurnL90          ( nullptr ) ,
	LFTurnR90          ( nullptr ) ,
	Fire               ( nullptr ) ,
	Reload             ( nullptr ) ,
	WeaponChange       ( nullptr ) ,
	LandAdditive       ( nullptr ) ,
	JumpBeginRun       ( nullptr ) ,
	RespawnLoop        ( nullptr ) ,
	RespawnEnd         ( nullptr ) ,
	FirstSpawn         ( nullptr ) ,
	FirstSpawnLoop     ( nullptr ) ,
	FirstSpawnRecovery ( nullptr ) ,
	Win                ( nullptr ) ,
	WinLoop            ( nullptr ) ,
	Defeat             ( nullptr ) ,
	DefeatLoop         ( nullptr ) ,
	Die                ( nullptr ) ,
	Knockback          ( nullptr ) ,
	Hit                ( nullptr ) ,
	HitInAir           ( nullptr ) ,
	CommonIdle         ( nullptr ) ,
	Stun               ( nullptr ) ,
	Shock              ( nullptr ) ,
	LFLand             ( nullptr ) ,
	LFLandHigh         ( nullptr )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        NAdd;               ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        LFAdd;              ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        NPose;              ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        LFPose;             ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        NToLF;              ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        LFToN;              ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          LFMove;             ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          NMoveF;             ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          NMove;              ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          LFMoveAim;          ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          NLeanGrounded;      ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          NLeanDash;          ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          NLeanInAir;         ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          AirMoveAim;         ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          NStopLF;            ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          NStopRF;            ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          LFStop;             ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        PivotF;             ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        SprintBegin;        ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        SprintLoop;         ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        SprintStop;         ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        Land;               ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        LandHigh;           ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        FallLoop;           ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        FallLoopHigh;       ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        JumpBegin;          ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        AirSprintStart;     ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        AirSprintLoop;      ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        AirJumpBegin;       ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        AirJumpLoop;        ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAimOffsetBlendSpace* AimOffset;          ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimMontage*         LFTurnL90;          ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimMontage*         LFTurnR90;          ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimMontage*         Fire;               ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimMontage*         Reload;             ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimMontage*         WeaponChange;       ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        LandAdditive;       ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        JumpBeginRun;       ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        RespawnLoop;        ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        RespawnEnd;         ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        FirstSpawn;         ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        FirstSpawnLoop;     ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        FirstSpawnRecovery; ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        Win;                ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        WinLoop;            ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        Defeat;             ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        DefeatLoop;         ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        Die;                ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        Knockback;          ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          Hit;                ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UBlendSpace*          HitInAir;           ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        CommonIdle;         ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        Stun;               ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        Shock;              ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Animation List Info" )
	UAnimSequence*        LFLand;             ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Animation List Info" )
	UAnimSequence*        LFLandHigh;         ///
};



/// CharacterDataType.h
///============================================================================
/// Name	: FCharacterInfo
///============================================================================
USTRUCT( BlueprintType )
struct FGWCharacterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWCharacterInfo()
	:                 
	MaxLevel          ( 0 ) ,
	MinDefence        ( 0.0f ) ,
	MaxDefence        ( 0.0f ) ,
	DefenceFactor     ( 0.0f ) ,
	MinHp             ( 0.0f ) ,
	MaxHp             ( 0.0f ) ,
	HpFactor          ( 0.0f ) ,
	HpRegen           ( 0.0f ) ,
	UltraGaugeMax     ( 0.0f ) ,
	UltraChargeWeight ( 0.0f ) ,
	MinStamina        ( 0.0f ) ,
	MaxStamina        ( 0.0f ) ,
	StaminaFactor     ( 0.0f ) ,
	StaminaRegen      ( 0.0f ) ,
	WSlot1            ( EGWItemSubType::SMG ) ,
	WSlot2            ( EGWItemSubType::SMG ) ,
	WSlot3            ( EGWItemSubType::SMG ) ,
	UltraSkill        ( nullptr ) ,
	PVP               ( false ) ,
	ForceDashTime     ( 0.0f ) ,
	ForceAirJumpTime  ( 0.0f ) ,
	FootstepSound     ( nullptr ) ,
	ThumbTexture1     ( nullptr ) ,
	ThumbTexture2     ( nullptr ) ,
	ThumbTexture3     ( nullptr ) ,
	ThumbTexture4     ( nullptr )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	FString                           CharacterName;     ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	int32                             MaxLevel;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	struct FGWSpeed                            Speed;             ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	struct FGWAcceleration                     Acceleration;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	struct FGWDeceleration                     Deceleration;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	struct FGWFriction                         Friction;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             MinDefence;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             MaxDefence;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             DefenceFactor;     ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             MinHp;             ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             MaxHp;             ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             HpFactor;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             HpRegen;           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             UltraGaugeMax;     ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             UltraChargeWeight; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             MinStamina;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             MaxStamina;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             StaminaFactor;     ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             StaminaRegen;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	TSubclassOf<class ACharacterBase> CharacterClass;    ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	EGWItemSubType                      WSlot1;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	EGWItemSubType                      WSlot2;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	EGWItemSubType                      WSlot3;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	class UAnimSequence*              UltraSkill;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	bool                              PVP;               ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             ForceDashTime;     ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	float                             ForceAirJumpTime;  ///
	
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	class UAkAudioEvent*              FootstepSound;     ///
	
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	class UTexture2D*                 ThumbTexture1;     ///
	
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	class UTexture2D*                 ThumbTexture2;     ///
	
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	class UTexture2D*                 ThumbTexture3;     ///
	
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Character Info" )
	class UTexture2D*                 ThumbTexture4;     ///

};

///============================================================================
/// Name	:	FFacialInfo
///============================================================================
USTRUCT( BlueprintType )
struct FGWFacialInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWFacialInfo()
	:
	FacialTerm           ( 1.0f    ) ,
	EnableFacial         ( false   ) ,
	EyeBrowAnger         ( nullptr ) ,
	EyeBrowAngerScale    ( 1.0f    ) ,
	SmileMouth           ( nullptr ) ,
	SmileMouthScale      ( 1.0f    ) ,
	SmlieRightMouth      ( nullptr ) ,
	SmileRightMouthScale ( 1.0f    ) ,
	AngryFace            ( nullptr ) ,
	AngryFaceScale       ( 1.0f    ) ,
	AngryEye             ( nullptr ) ,
	AngryEyeScale        ( 1.0f    ) ,
	AngryLeftEye         ( nullptr ) ,
	AngryLeftEyeScale    ( 1.0f    )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	float        FacialTerm;           ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	bool         EnableFacial;         ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	UCurveFloat* EyeBrowAnger;         ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	float        EyeBrowAngerScale;    ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	UCurveFloat* SmileMouth;           ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	float        SmileMouthScale;      ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	UCurveFloat* SmlieRightMouth;      ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	float        SmileRightMouthScale; ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	UCurveFloat* AngryFace;            ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	float        AngryFaceScale;       ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	UCurveFloat* AngryEye;             ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	float        AngryEyeScale;        ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	UCurveFloat* AngryLeftEye;         ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Facial Info" )
	float        AngryLeftEyeScale;    ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWCharacterCameraInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWCharacterCameraInfo()
	:
	CharacterInfoId ( 0 ) ,
	Mode            ( EGWCameraMode::Default ) ,
	TargetArmLength ( 0.0f ) ,
	SocketOffset    ( FVector::ZeroVector ) ,
	TargetOffset    ( FVector::ZeroVector ) ,
	UseCameralag    ( true ) ,
	CameraLagSpeed  ( 0.0f ) ,
	FOV             ( 0.0f )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Character Camera Info" )
	int         CharacterInfoId; ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Character Camera Info" )
	FString     Description;     ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Character Camera Info" )
	EGWCameraMode Mode;            ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Character Camera Info" )
	float       TargetArmLength; ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Character Camera Info" )
	FVector     SocketOffset;    ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Character Camera Info" )
	FVector     TargetOffset;    ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Character Camera Info" )
	bool        UseCameralag;    ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Character Camera Info" )
	float       CameraLagSpeed;  ///

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "|Character Camera Info" )
	float       FOV;             ; ///
};
















/// WordDataType.h
///----------------------------------------------------------------------------
/// Name	:	FBadwordInfo
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWBadwordInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Badword Info" )
		FString Badword; ;///
};

///----------------------------------------------------------------------------
/// Name	:	FStringInfo
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWStringInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "String Info" )
	FString Kr; ;///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "String Info" )
	FString Us; ;///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "String Info" )
	FString Jp; ;///
};

///----------------------------------------------------------------------------
/// Name	:	FServerErrorCode - need change
///----------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FGWServerErrorCode : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ServerErrorCode" )
	FString ErrorCode; ;///
};





/// ChatDataType.h
///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWChatColor : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "ChatData" )
		FSlateColor Color; ///

};





/// SkillDataType.h
///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWSkillInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWSkillInfo()
	:
	ThumbTexture          ( nullptr ) ,
	DisplayName           ( TEXT( "" ) ) ,
	DisplayDescription    ( TEXT( "" ) ) ,
	SkillCategory         ( EGWSkillCategoty::UltimateSkill ) ,
	SpawnActorId          ( TEXT( "" ) ) ,
	SkillType             ( EGWSkillType::Active ) ,
	SkillDamageRate       ( 0.0f ) ,
	PassiveConditionType  ( EGWPassiveConditionType::Always ) ,
	PassiveConditionParam ( 0.0f ) ,
	SkillTargetType       ( EGWSearchTarget::All ) ,
	SkillDetailType       ( EGWSkillDetailType::Buff ) ,
	CastLocationType      ( EGWCastLocationType::Character ) ,
	CastLocOffset         ( FVector::ZeroVector ) ,
	CastRotOffset         ( FRotator( 0 , 0 , 0 ) ) ,
	SkillCollisionType    ( EGWCollisionType::Box ) ,
	ProjectileClass       ( nullptr ) ,
	FireCount             ( 0 ) ,
	FireInterval          ( 0.0f ) ,
	FireAngle             ( 0.0f ) ,
	DirectionOffset       ( FRotator( 0 , 0 , 0 ) ) ,
	SkillDuration         ( 0.0f ) ,
	CastTime              ( 0.0f ) ,
	CoolTime              ( 0.0f ) ,
	ActiveAnimation       ( nullptr ) ,
	ActiveSound           ( nullptr ) ,
	ActivePS              ( nullptr ) ,
	ActiveCameraAnim      ( nullptr ) ,
	EffectLocOffset       ( FVector::ZeroVector ) ,
	MuzzleFlashPS         ( nullptr ) ,
	MuzzleFlashSound      ( nullptr ) ,
	CameraShake           ( nullptr )
	{
	}


public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Skill Info" )
	class UTexture2D* ThumbTexture;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	FString                            DisplayName;           ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	FString                            DisplayDescription;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	EGWSkillCategoty                     SkillCategory;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	FString                            SpawnActorId;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	TArray<FString>                    SkillEffectIds;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	EGWSkillType                         SkillType;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	float                              SkillDamageRate;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	EGWPassiveConditionType              PassiveConditionType;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	float                              PassiveConditionParam; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	EGWSearchTarget                      SkillTargetType;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	EGWSkillDetailType                   SkillDetailType;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	EGWCastLocationType                  CastLocationType;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	FName                              SkillSocketName;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	FVector                            CastLocOffset;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	FRotator                           CastRotOffset;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	EGWCollisionType                     SkillCollisionType;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	struct FGWCollisionParam                    CollisionParam;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	TSubclassOf<class AProjectileBase> ProjectileClass;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	int32                              FireCount;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	float                              FireInterval;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	float                              FireAngle;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	FRotator                           DirectionOffset;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	float                              SkillDuration;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	float                              CastTime;              ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	float                              CoolTime;              ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	class UAnimMontage*                ActiveAnimation;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	class USoundCue*                   ActiveSound;           ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	class UParticleSystem*             ActivePS;              ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	class UCameraAnim*                 ActiveCameraAnim;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	FName                              EffectSocketName;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	FVector                            EffectLocOffset;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	class UParticleSystem*             MuzzleFlashPS;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	class USoundCue*                   MuzzleFlashSound;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info")
	TSubclassOf<class UCameraShake>    CameraShake;           ///

	
};



/// WeaponDataType.h
///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWWeaponInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWWeaponInfo()
	:                    
	TempName             ( TEXT( "" ) ) ,
	Tier                 ( 0 ) ,
	Category             ( EGWWeaponCategory::AssaultRifle ) ,
	TreatValue           ( 0 ) ,
	UltraChargerByShot   ( 0 ) ,
	UltraChargerByHit    ( 0 ) ,
	FireType             ( EGWWeaponAttackType::HitScan ) ,
	TraceType            ( EGWTraceType::Visible ) ,
	ProjectileBaseClass  ( nullptr ) ,
	BuckshotCount        ( 1 ) ,
	TriggerType          ( EGWWeaponTriggerType::SemiAuto ) ,
	TriggerCount         ( 1 ) ,
	TriggerInterval      ( 0.0f ) ,
	ChargeTime           ( 0.0f ) ,
	SpoolUpTime          ( 0.0f ) ,
	FireInterval         ( 0.0f ) ,
	MaxSpread            ( 0.0f ) ,
	MaxSpreadZoomIn      ( 0.0f ) ,
	IncreaseSpreadAmount ( 0.0f ) ,
	DecreaseSpreadSpeed  ( 0.0f ) ,
	MinDamage            ( 0.0f ) ,
	MaxDamage            ( 0.0f ) ,
	MinDamageScale       ( 0.0f ) ,
	DamageType           ( nullptr ) ,
	WeaponRange          ( 0.0f ) ,
	MinDamageRange       ( 0.0f ) ,
	MaxDamageRange       ( 0.0f ) ,
	DamageScale_Head     ( 0.0f ) ,
	DamageScale_Upper    ( 0.0f ) ,
	DamageScale_Lower    ( 0.0f ) ,
	DamageScale_Arm      ( 0.0f ) ,
	MagazineType         ( EGWMagazineType::None ) ,
	MaxCarryAmmo         ( 0 ) ,
	MagazineCapacity     ( 0 ) ,
	InitialAmmo          ( 0 ) ,
	AmmoConsumption      ( 0 ) ,
	ReloadTime           ( 0.0f ) ,
	ReloadType           ( EGWReloadType::FULL ) ,
	ReloadAmmoQuantity   ( 0 ) ,
	EquipTime            ( 0.0f ) ,
	WeaponSkill          ( TEXT( "" ) ) ,
	ZoomOffset           ( FVector::ZeroVector ) ,
	ZoomFOV              ( 0.0f ) ,
	WeaponClass          ( nullptr )
	{
	}

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	FString                          TempName;             ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	int32                            Tier;                 ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	EGWWeaponCategory                  Category;             ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	int32                            TreatValue;           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	int32                            UltraChargerByShot;   ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	int32                            UltraChargerByHit;    ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	EGWWeaponAttackType                FireType;             ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	EGWTraceType                       TraceType;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	TSubclassOf<AProjectileBase>           ProjectileBaseClass;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	int32                            BuckshotCount;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	EGWWeaponTriggerType               TriggerType;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	int32                            TriggerCount;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            TriggerInterval;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            ChargeTime;           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            SpoolUpTime;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            FireInterval;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            MaxSpread;     
	
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            MaxSpreadZoomIn;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            IncreaseSpreadAmount; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            DecreaseSpreadSpeed;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            MinDamage;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            MaxDamage;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            MinDamageScale;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	TSubclassOf<AProjectileBase>     DamageType;           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            WeaponRange;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            MinDamageRange;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            MaxDamageRange;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            DamageScale_Head;     ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            DamageScale_Upper;    ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            DamageScale_Lower;    ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            DamageScale_Arm;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	EGWMagazineType                    MagazineType;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	int32                            MaxCarryAmmo;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	int32                            MagazineCapacity;     ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	int32                            InitialAmmo;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	int32                            AmmoConsumption;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            ReloadTime;           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	EGWReloadType                      ReloadType;           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	int32                            ReloadAmmoQuantity;   ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                            EquipTime;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	FString                          WeaponSkill;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	FVector                          ZoomOffset;           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Weapon Info" )
	float                          ZoomFOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info")
	TSubclassOf< class AWeaponBase > WeaponClass;          ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWWeaponSkillInfo : public FTableRowBase
{
	GENERATED_BODY()


public:
	FGWWeaponSkillInfo()
	:
	SkillThumbnail      ( nullptr                ) ,
	DisplayName         ( TEXT( "" )             ) ,
	Description         ( TEXT( "" )             ) ,
	Level               ( 1                      ) ,
	Cooldown            ( 0.0f                   ) ,
	SkillDuration       ( 0.0f                   ) ,
	SkillTargetType     ( EGWSearchAndAction::None ) ,
	bAllowPrimaryAttack ( false                  ) ,
	Damage              ( 0.0f                   ) ,
	Param1              ( 0.0f                   ) ,
	Param2              ( 0.0f                   ) ,
	Param3              ( 0.0f                   ) ,
	Param4              ( 0.0f                   ) ,
	Param5              ( 0.0f                   )                 
	{
	}

public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	UTexture2D*      SkillThumbnail;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	FString          DisplayName;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	FString          Description;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	int32            Level;               ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	float            Cooldown;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	float            SkillDuration;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	EGWSearchAndAction SkillTargetType;     ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	bool             bAllowPrimaryAttack; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	float            Damage;              ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	float            Param1;              ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	float            Param2;              ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	float            Param3;              ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	float            Param4;              ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
	float            Param5;              ///

};





/// StageDataType.h
USTRUCT( BlueprintType )
struct FGWStageInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWStageInfo()
	:
	Using            ( false          ) ,
	GameMode         ( EGWGameMode::PVP ) ,
	PlayTime         ( 0              ) ,
	MinPlayer        ( 0              ) ,
	MaxPlayer        ( 0              ) ,
	MinimapTexture   ( nullptr        ) ,
	MinimapDimension ( 5000           ) ,
	Thumb            ( nullptr        ) ,
	RewardExp        ( 0              ) ,
	RewardMoney      ( 0              )
	{
	}


public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	bool              Using;            /// ;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	FString           StageName;        /// ;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	EGWGameMode         GameMode;         /// ;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	int32             PlayTime;         /// ;  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	int32             MinPlayer;        /// = 2; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	int32             MaxPlayer;        ///  = 4; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	class UTexture2d* MinimapTexture;   ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	FName             SequenceId;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	int32             MinimapDimension; /// = 5000;///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	class UTexture2d* Thumb;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	FName             LevelName;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	FText             Country;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	FString           LevelFulPath;     ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	int32             RewardExp;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	int32             RewardMoney;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stage Info" )
	FName             RewardID;         ///

};


/// UIDataType.h
///============================================================================
/// Name	: 
///============================================================================
USTRUCT( BlueprintType )
struct FGWResolutionInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Resolution Info" )
		FIntPoint Resolution;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Resolution Info" )
		FIntPoint Ratio;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
		FText Description;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , meta = ( ToolTip = "0 = 특수 | 1 = 4:3 | 2 = 16:9 | 3 = 16:10 | 4 = 21:9 입니다" ) , Category = "Resolution Info" )
		int RatioType;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , meta = ( ToolTip = "데이터 테이블의 몇번째 행에 위치한지 저장하는 변수입니다." ) , Category = "Resolution Info" )
		int Index;
};


USTRUCT( BlueprintType )
struct FGWChannelInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Channel Info" )
	FString Name; /// 채널 이름

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Channel Info" )
	uint8 GroupId; /// 그룹 id - 1 부터 시작

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Channel Info" )
	uint8 ItemId; /// 아이템 id - 0 부터 시작

};