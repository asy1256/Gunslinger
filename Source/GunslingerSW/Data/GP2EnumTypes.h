#pragma once

#include "CoreMinimal.h"
#include "GP2EnumTypes.generated.h"

UENUM( BlueprintType )
enum class EGWInfoType: uint8
{
	CharacterInfo, /// 
	WeaponInfo, /// 
	Max, /// 
};




//-----------------------------------------------------------------------------
/// 00. 입력시스템관련
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWInputKeyType : uint8
{
	Axis ,   ///
	Action , ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWInputLimit : uint8
{
	None ,        ///
	MoveLimit ,   ///
	AttackLimit , ///
	AllLimit ,    ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWShortKeyType : uint8
{
	Discard ,           ///
	Equip ,             ///
	Change ,            ///
	Unequip ,           ///
	Install ,           ///
	Uninstall ,         ///
	ToggleInformation , ///
	PrevMenu ,          ///
	NextMenu ,          ///
	Close ,             ///
	Back ,              ///
	SetToDefault ,      ///
	Click ,             ///
	Select ,            ///
	Cancel ,            ///
	Access ,            ///
	Complete ,          ///
	CreateRoom ,        ///
	Refresh ,           ///
	GameReady ,         ///
	GameStart ,         ///
	ChartStart ,        ///
};
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// 01. Character 관련
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWCardinalDirection : uint8
{
	North , ///
	East ,  ///
	West ,  ///
	South , ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWActionState : uint8
{
	None ,     ///
	Ready ,    ///
	Activate , ///
	Loop ,     ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWActionType : uint8
{
	Dash ,   ///
	Jump ,   ///
	Zoom ,   ///
	Attack , ///
	Skill ,  ///
};

///============================================================================
/// Name	: EGWActiveType
///============================================================================
UENUM( BlueprintType )
enum class EGWActiveType : uint8
{
	Passive , ///
	Active ,  ///
};

///============================================================================
/// Name	: EGWAnimSequence
///============================================================================
UENUM( BlueprintType )
enum class EGWAnimSequence : uint8
{
	NAdd ,               ///
	LFAdd ,              ///
	NPose ,              ///
	LFPose ,             ///
	LFToN ,              ///
	NToLF ,              ///
	PivotF ,             ///
	SprintBegin ,        ///
	SprintLoop ,         ///
	SprintStop ,         ///
	Land ,               ///
	LandHigh ,           ///
	JumpBeginIdle ,      ///
	JumpBeginRun ,       ///
	FallLoop ,           ///
	FallLoopHigh ,       ///
	AirSprintBegin ,     ///
	AirSprintLoop ,      ///
	AirJumpBegin ,       ///
	AirJumpLoop ,        ///
	LandAdditive ,       ///
	RespawnLoop ,        ///
	RespawnEnd ,         ///
	FirstSpawn ,         ///
	FirstSpawnLoop ,     ///
	FirstSpawnRecovery , ///
	Win ,                ///
	WinLoop ,            ///
	Defeat ,             ///
	DefeatLoop ,         ///
	Die ,                ///
	Knockback ,          ///
	CommonIdle ,         ///
	Stun ,               ///
	Shock ,              ///
	LFLand ,             ///
	LFLandHigh ,         ///
};

///============================================================================
/// Name	: EGWBlendSpaceAnim
///============================================================================
UENUM( BlueprintType )
enum class EGWBlendSpaceAnim : uint8
{
	LFMove ,        ///
	NMoveF ,        ///
	NMove ,         ///
	LFMoveAim ,     ///
	NLeanGrounded , ///
	NLeanDash ,     ///
	NLeanInAir ,    ///
	AirMoveAim ,    ///
	NStopLF ,       ///
	NStopRF ,       ///
	LFStop ,        ///
	Hit ,           ///
	HitInAir ,      ///
};

///============================================================================
/// Name	: EGWMovementMode
///============================================================================
UENUM( BlueprintType )
enum class EGWMovementMode : uint8
{
	None ,     ///
	Grounded , ///
	Falling ,  ///
	Ragdoll ,  ///
	Flying , ///
};

///============================================================================
/// Name	: EGWFallLoopMethod
///============================================================================
UENUM( BlueprintType )
enum class EGWFallLoopMethod : uint8
{
	Normal ,  ///
	AirDash , ///
	AirJump , ///
};

///============================================================================
/// Name	: EGWMachineState
///============================================================================
UENUM( BlueprintType )
enum class EGWMachineState : uint8
{
	FirstFX ,         ///
	Normal ,          ///
	Die ,             ///
	Respawn ,         ///
	MissionFinished , ///
};

///============================================================================
/// Name	: EGWMontage
///============================================================================
UENUM( BlueprintType )
enum class EGWMontage : uint8
{
	LFTurnL90 ,    ///
	LFTurnR90 ,    ///
	Fire ,         ///
	Reload ,       ///
	WeaponChange , ///
};

///============================================================================
/// Name	: EGWRotationMode
///============================================================================
UENUM( BlueprintType )
enum class EGWRotationMode : uint8
{
	VelocityDirection , /// 카메라 방향
	LookingDirection ,  /// 자유 방향

};

///============================================================================
/// Name	: EGWFootstepType
///============================================================================
UENUM( BlueprintType )
enum class EGWFootstepType : uint8
{
	Step ,   ///
	Walk ,   ///
	Run ,    ///
	Sprint , ///
	Pivot ,  ///
	Jump ,   ///
	Land ,   ///
};

///============================================================================
/// Name	: EGWIdleEntryState
///============================================================================
UENUM( BlueprintType )
enum class EGWIdleEntryState : uint8
{
	NIdle ,                 /// 
	LFIdle ,                /// 
	CIdle ,                 /// 
};

///============================================================================
/// Name	: EGWLocomotionState
///============================================================================
UENUM( BlueprintType )
enum class EGWLocomotionState : uint8
{
	None ,                  ///
	NotMoving ,             ///
	Moving ,                ///
	Pivot ,                 ///
	Stopping ,              ///
};

///============================================================================
/// Name	: EGWLocomotionState
///============================================================================
UENUM( BlueprintType )
enum class EGWMovementDirection : uint8
{
	Forward ,               ///
	Backward ,              ///
};

///============================================================================
/// Name	: EGWCharacterSlotType
///============================================================================
UENUM( BlueprintType )
enum class EGWCharacterSlotType : uint8
{
	First ,  ///
	Second , ///
	Third ,  ///
};

///============================================================================
/// Name	: EGWCharacterClass
///============================================================================
UENUM( BlueprintType )
enum class EGWCharacterClass : uint8
{
	None ,       ///
	Striker ,    ///
	Destroyer ,  ///
	Specialist , ///
	Shadow ,     ///
	Max ,        ///
};

UENUM( BlueprintType )
enum class EGWPCType : uint8
{
	PVE,  ///  
	PVP,   ///
	OBSERVER, /// 일단은 그냥.
};

///============================================================================
/// Name	: EGWJobType
///============================================================================
UENUM( BlueprintType )
enum class EGWJobType : uint8
{
	none = 0 , /// 무등급
	vanguard ,  ///
	sniper ,    ///
	supporter , ///
	buster ,    ///
};

///============================================================================
/// Name	: EGWSelectCharacterMode
///============================================================================
UENUM( BlueprintType )
enum class EGWSelectCharacterMode : uint8
{
	PlayerSelect ,    ///
	CharacterSelect , ///
	Max ,             ///
};


///============================================================================
/// Name	: EGWViewMode
///============================================================================
UENUM( BlueprintType )
enum class EGWViewMode : uint8
{
	LeftStance ,   ///
	CenterStance , ///
	RightStance ,  ///
};

///============================================================================
/// Name	: EGWWeaponSlot
///============================================================================
UENUM( BlueprintType )
enum class EGWWeaponSlot : uint8
{
	First ,  /// 1번무기슬롯
	Second , /// 2번무기슬롯
	Third ,  /// 3번무기슬롯
	Max ,    ///
};


//-----------------------------------------------------------------------------
// 02 몹 관련
///============================================================================
/// Name	: EGWLocomotionState
///============================================================================
UENUM( BlueprintType )
enum class EGWMobGrade : uint8
{
	Normal ,                ///
	Elite ,                 ///
	Boss ,                  ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWMobMoveType : uint8
{
	Ground ,                ///
	Fly ,                   ///
	Jump ,                  ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWMobRace : uint8
{
	Insecta ,               ///
	Animal ,                ///
	Colloid ,               ///
	Metallic ,              ///
	Evolver ,               ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWMobRoamingType : uint8
{
	Hold ,                  /// ///
	MoveAround ,
	MoveTarget ,            ///
	RoamingTarget ,         ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWMobSpawnActionType : uint8
{
	None ,                  ///
	MoveTo ,                ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWMonsterMoveType : uint8
{
	Ground ,                ///
	Fly ,                   ///
	Jump ,                  ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWSpawnPointState : uint8
{
	Deactive ,              ///
	ReadySpawn ,            ///
	Spawned ,               ///
};

//-----------------------------------------------------------------------------
// 03. 아이템관련
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWInstantItemType : uint8
{
	Heal ,                  ///
	UltimateGauge ,         ///
	Skill ,                 ///
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWInteractionType : uint8
{
	GetItem ,               ///
	Dialogue ,              ///
};

///
///============================================================================
/// Name	: 
///=
UENUM( BlueprintType )
enum class EGWItemOptionCalcType : uint8
{
	Add ,                   ///
	Multiply ,                   ///
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWItemOptionType : uint8
{
	FireInterval,
	Spread,
	SpreadZoom,
	InsectaDamage ,
	AnimalDamage,
	MetalicDamage,
	ColloidDamage,
	MagazineCapacity,
	ReloadTime,
	WeaponRange,
	MaxDamageRange,
	Defense,
	Health,
	RunSpeed,
	DashSpeed,
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWItemSubType : uint8
{
	HG,
	AR,
	SR,
	SG,
	SMG,
	HMG,
	LC,
	MW,
	Armor,
	WpModuleA,
	WpModuleB,
	WpModuleG,
	WpModuleD,
	CosModuleA,
	CosModuleB,
	CosModuleG,
	CosModuleD,
	Capsule,
	Material,
	UserExp,
	Cash,
	Money,
	CosUpper,
	CosLower,
	Accessory,

};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWItemType : uint8
{
	None ,
	Weapon ,                ///
	Armor ,                 ///
	WpModule ,             ///
	ArModule ,               ///
	Consumable ,            ///
	Material ,         ///
	Costume ,               ///
	UserExp ,                  ///
	Cash ,                 ///
	Money ,                  ///

};


//-----------------------------------------------------------------------------
//	04 총알관련
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWProjectileHitAction : uint8
{
	Explosion ,             ///
	Bounce ,                ///
	Attach ,                ///
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWProjectileType : uint8
{
	Normal ,                ///
	Explosion ,             ///
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWSearchAndAction : uint8
{
	None ,                  ///
	Explosion ,             ///
	Homing ,                ///
	StopSearch ,            ///
};


//-----------------------------------------------------------------------------
//	05 Skill
/** ESkillTargetType -> EGWSearchTarget */
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWSearchTarget : uint8
{
	None    UMETA( DisplayName = "None" ) ,          ///
	All     UMETA( DisplayName = "All" ) ,           ///
	Ally    UMETA( DisplayName = "Ally" ) ,          ///
	AllyWithMe   UMETA( DisplayName = "AllyWithMe" ) ,    ///
	Enemy    UMETA( DisplayName = "Enemy" ) ,         ///
	Self    UMETA( DisplayName = "Self" ) ,          ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWSkillCategoty : uint8
{
	WeaponSkill   UMETA( DisplayName = "WeaponSkill" ) ,   ///
	UltimateSkill  UMETA( DisplayName = "UltimateSkill" ) , ///
};

///============================================================================
/// Name	: EGWLocomotionState
///============================================================================
UENUM( BlueprintType )
enum class EGWSkillType : uint8
{
	Active    UMETA( DisplayName = "Active" ) ,        ///
	Passive    UMETA( DisplayName = "Passive" ) ,       ///
};

///============================================================================
/// Name	: EGWLocomotionState
///============================================================================
UENUM( BlueprintType )
enum class EGWPassiveConditionType : uint8
{
	Always    UMETA( DisplayName = "Always" ) ,        ///
	BelowHP    UMETA( DisplayName = "BelowHP" ) ,       ///
	Killed    UMETA( DisplayName = "Killed" ) ,        ///
	KeepAttack   UMETA( DisplayName = "KeepAttack" ) ,    ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWSkillDetailType : uint8
{
	Buff    UMETA( DisplayName = "Buff" ) ,          ///
	Projectile   UMETA( DisplayName = "Projectile" ) ,    ///
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWCastLocationType : uint8
{
	Character   UMETA( DisplayName = "Character" ) ,     ///
	Weapon    UMETA( DisplayName = "Weapon" ) ,        ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWCollisionType : uint8
{
	None    UMETA( DisplayName = "None" ) ,          ///
	Sphere    UMETA( DisplayName = "Sphere" ) ,        ///
	Line    UMETA( DisplayName = "Line" ) ,          ///
	Box     UMETA( DisplayName = "Box" ) ,           ///
	Cylinder   UMETA( DisplayName = "Cylinder" ) ,      ///
	Fan     UMETA( DisplayName = "Fan" ) ,           ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWBuffType : uint8
{
	Buff,
	DeBuff
};




//-----------------------------------------------------------------------------
//Weapon
/*
"무기의 종류 구분
#0: AssaultRifle
#1: ShotGun
#2: Launcher
#3: HeavyMachineGun
#4: SniperRifle
#5: SubMachineGun
#6: MechanicRifle
#7: MechanicPistol
#8: HandShotGun
#9: HandLauncher
#10: HandGun
#11: Melee"
*/
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWWeaponCategory : uint8
{
	AssaultRifle    UMETA( DisplayName = "AssaultRifle"    ), ///
	ShotGun         UMETA( DisplayName = "ShotGun"         ), ///
	Launcher        UMETA( DisplayName = "Launcher"        ), ///
	HeavyMachineGun UMETA( DisplayName = "HeavyMachineGun" ), ///
	SniperRifle     UMETA( DisplayName = "SniperRifle"     ), ///
	SubMachineGun   UMETA( DisplayName = "SubMachineGun"   ), ///
	MechanicRifle   UMETA( DisplayName = "MechanicRifle"   ), ///
	MechanicPistol  UMETA( DisplayName = "MechanicPistol"  ), ///
	HandShotGun     UMETA( DisplayName = "HandShotGun"     ), ///
	HandLauncher    UMETA( DisplayName = "HandLauncher"    ), ///
	HandGun         UMETA( DisplayName = "HandGun"         ), ///
	Melee           UMETA( DisplayName = "Melee"           ), ///
};


/*
대상에 대한 공격판정 타입
#0: HitScan: Line Trace, Box Trace 등의 즉각적인 히트 판정
#1: Projectile: 대상을 향해 날아가는 투사체 발사
*/
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWWeaponAttackType : uint8
{
	HitScan    UMETA( DisplayName = "HitScan"    ), ///
	Projectile UMETA( DisplayName = "Projectile" ), ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWTraceType : uint8
{
	Visible UMETA( DisplayName = "Visible" ) , ///
	Laser   UMETA( DisplayName = "Laser"   ) , ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWWeaponTriggerType : uint8
{
	SemiAuto    UMETA( DisplayName = "SemiAuto"    ), ///
	Auto        UMETA( DisplayName = "Auto"        ), ///
	Burst       UMETA( DisplayName = "Burst"       ), ///
	AutoSpool   UMETA( DisplayName = "AutoSpool"   ), ///
	Charge      UMETA( DisplayName = "Charge"      ), ///
	BurstCharge UMETA( DisplayName = "BurstCharge" ), ///
	Hold        UMETA( DisplayName = "Hold"        ), ///
	Buckshot    UMETA( DisplayName = "Buckshot"    ), ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWMagazineType : uint8
{
	None      UMETA( DisplayName = "None"     ) , ///
	Magazinr  UMETA( DisplayName = "Magazine" ) , ///
	Cooldown  UMETA( DisplayName = "Cooldown" ) , ///
	Charging  UMETA( DisplayName = "Charging" ) , ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWReloadType : uint8
{
	FULL    UMETA( DisplayName = "FULL" ) ,        ///
	SPLIT    UMETA( DisplayName = "SPLIT" ) ,       ///
};

/*
"서브 트리거 타입:  (우-클릭) 의 기능
#0: None: 기능없음
#1: Zoom: 일반적인 줌
#2: SniperZoom: 스코프를 사용한 스나이퍼 줌
#3: ToggleMech: 메카닉 피스톨 전용 "
*/
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWSubTriggerType : uint8
{
	None    UMETA( DisplayName = "None" ) ,        ///
	Zoom    UMETA( DisplayName = "Zoom" ) ,        ///
	SniperZoom   UMETA( DisplayName = "SniperZoom" ) ,  ///
	ToggleMech   UMETA( DisplayName = "ToggleMech" ) ,  ///
};

//-----------------------------------------------------------------------------
//Chat
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWChatMessageType : uint8
{
	ALLCHAT ,                                          ///
	TEAMCHAT ,                                         ///
	GUILD ,                                            ///
	WHISPER ,                                          ///
	NOTICE ,                                           ///
	SYSTEM ,                                           ///
	HELP ,                                             ///
};


//-----------------------------------------------------------------------------
//Word
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWCountryLanguage : uint8
{
	Korean ,                                           ///
	Japanese ,                                         ///
	English ,                                          ///
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWLocale : uint8
{
	Local ,                                            ///
	Jpn ,                                              ///
	Usa///
};

// Quest
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWQuestType : uint8
{
	Hunting ,
	Collection ,
	MapClear ,
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWQuestState : uint8
{
	NONE ,                                             ///
	Start ,                                            ///
	Clear ,                                            ///
	Complete ,                                         ///
	Cancel ,                                           ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWMessageBoxResult : uint8
{
	OK     UMETA( DisplayName = "OK" ) ,         ///
	CANCEL UMETA( DisplayName = "CANCEL" ) ,     ///

};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWMessageBoxStyle : uint8
{
	Ok ,                                               ///
	OkCancel ,                                         ///
	YesNo ,                                            ///
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWGaitType : uint8
{
	Walking ,                                          ///
	Running ,                                          ///
	Sprinting ,                                        ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum  class EGWGame : uint8
{
	Title ,                                            ///
	SelectCharacter ,                                  ///
	Replay ,                                           ///
	Tutorial ,                                         ///
	VisualLobby ,                                      ///
	Match ,                                            ///

};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWGameState : uint8
{
	Ready ,                                            ///
	Playing ,                                          ///
	Result ,                                           ///
	End ,                                              ///
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWPVE_TargetDifficulty : uint8
{
	Easy ,                                             ///
	Normal ,                                           ///
	Hard ,                                             ///
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWResult : uint8
{
	WIN ,                                              ///
	LOSE ,                                             ///
	DRAW ,                                             ///
	Success ,                                          ///
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWRewardType : uint8
{
	FixedReward ,                                      ///
	RandomReward ,                                     ///
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWTimerType : uint8
{
	DecreseTimer ,                                     ///
	IncreseTimer ,                                     ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EActorStatType : uint8
{
	MoveSpeed ,                                        ///
	WalkSpeedRate ,                                    ///
	RunSpeedRate ,                                     ///
	DashSpeedRate ,                                    ///
	AllSpeedRate ,                                     ///
	Defense ,                                          ///
	DefenseWeight ,                                    ///
	MaxHp ,                                            ///
	MaxHpWeight ,                                      ///
	HPRegen ,                                          ///
	HPRegenWeight ,                                    ///
	MaxShield ,                                        ///
	ShieldRegen ,                                      ///
	MaxShieldWeight ,                                  ///
	UltraGaugeMax ,                                    ///
	UltraChargeWeight ,                                ///
	UltraBonusDamageWeight ,                           ///
	Stamina ,                                          ///
	DetectRange ,                                      ///
	DetectRangeWeight ,                                ///
};


///////////////////////////////////////////////////////////////////////////////
/// 
///////////////////////////////////////////////////////////////////////////////
UENUM( BlueprintType )
enum class EGWChatType : uint8
{
	ALL     UMETA( DisplayName = "ALL" ) ,     ///
	TEAM    UMETA( DisplayName = "TEAM" ) ,    ///
	GUILD    UMETA( DisplayName = "GUILD" ) ,   ///
	WHISPER    UMETA( DisplayName = "WHISPER" ) , ///
	NOTICE    UMETA( DisplayName = "NOTICE" ) ,  ///
	SYSTEM    UMETA( DisplayName = "SYSTEM" ) ,  ///
	HELP    UMETA( DisplayName = "HELP" ) ,    ///
};






///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWMissionType : uint8
{
	AllSpawnAllClear ,   ///
	WaveSpawnTimeClear , ///
	WaveSpawnAllClear ,  ///
	BossKill ,           ///
	SubWave ,            ///
};


/////
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWSpawnLocationType : uint8
{
	Custom				UMETA( DisplayName = "Custom" ) ,
	Character			UMETA( DisplayName = "Character" ) ,
	Weapon				UMETA( DisplayName = "Weapon" )
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWAffectType : uint8
{
	None    UMETA( DisplayName = "None" ) , ///
	InfiniteAmmo ,                        ///
	IncCurWpAttack ,                      ///
	IncAllWpDmg ,                         ///
	BindDotAttack ,                       ///
	DotDamage ,                           ///
	IncMoveSpeed ,                        ///
	DotHeal ,                             ///
	Exhaustion ,                          ///
	Stun ,                                ///
	Shock ,                               ///
	IncDefense ,                          ///
	DecDefense ,                          ///
	NanoRobots ,                          ///
	InitCoolTime ,                        ///
	SnareShot ,                           ///
	Hiding ,                              ///
	NanoExplosion ,                       ///
	DecCurWpAttack ,                      ///
	DecAllWpDmg ,                         ///
	DecMoveSpeed ,                        ///
	DotDamage2 ,                          ///

};


///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWEffectType : uint8
{
	Buff				UMETA( DisplayName = "Buff" )
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class	EGWDamageTypes : uint8
{
	Type_None      = 0  UMETA( DisplayName = "Default" ),   
	Type_Stun      = 1  UMETA( DisplayName = "Stun" ),      
	Type_Shock     = 2  UMETA( DisplayName = "Shock" ),     
	Type_KnockBack = 3  UMETA( DisplayName = "KnockBack" ), 
	Type_Freezing  = 4  UMETA( DisplayName = "Freezing" ),  
	Type_Dummy01   = 5  UMETA( DisplayName = "Dummy01" ),   
	Type_Dummy02   = 6  UMETA( DisplayName = "Dummy02" ),   
	Type_Dummy03   = 7  UMETA( DisplayName = "Dummy03" ),   
};



///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class	EGWCameraMode : uint8
{
	Default, ///
	Zoom,    ///
	Run,     ///
	Sprint,  ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM(BlueprintType)
enum class EGWDamageProperty : uint8
{
	KnockBack      UMETA(DisplayName = "KonckBack"),

};

///============================================================================
/// Name	: 
///============================================================================
UENUM(BlueprintType)
enum class EGWTeam : uint8
{
	NONE,
	RED,
	BLUE
};

UENUM(BlueprintType)
enum class ETeam : uint8
{
	NONE,
	RED,
	BLUE
};


///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWWeaponParts : uint8
{
	SniperScope    UMETA( DisplayName = "SniperScope" ) ,  
	LaserSight     UMETA( DisplayName = "LaserSight" ) ,
};

///============================================================================
/// Name	:  삭제필요
///============================================================================
UENUM( BlueprintType )
enum class EWeaponAttachType : uint8
{
	Both      UMETA( DisplayName = "Both" ) ,  /// 양손 장착 가능 타입
	Left      UMETA( DisplayName = "Left" ) ,  /// 왼손 장착 가능 타입
	Right     UMETA( DisplayName = "Right" ) , /// 오른손 장착 가능 타입
};

UENUM(BlueprintType)
enum class EGWWeaponAttachType : uint8
{
	Both      UMETA(DisplayName = "Both"),  /// 양손 장착 가능 타입
	Left      UMETA(DisplayName = "Left"),  /// 왼손 장착 가능 타입
	Right     UMETA(DisplayName = "Right"), /// 오른손 장착 가능 타입
};


/// 정리 필요.
///============================================================================
/// Name	: 
///============================================================================
//UENUM( BlueprintType )
//enum GAMEMODE
//{
//	PVP ,
//	PVE ,
//	TUTORIAL
//};

///============================================================================
/// Name	:  
///============================================================================
//UENUM( BlueprintType )
//enum class EGameMode : uint8
//{
//	PVP					UMETA( DisplayName = "PVP" ) ,
//	PVE					UMETA( DisplayName = "PVE" ) ,
//	TUTORIAL			UMETA( DisplayName = "TUTORIAL" )
//};

///============================================================================
/// Name	: EGAME_MODE=>EGWGameMode 변경예정
///============================================================================
UENUM(BlueprintType)
enum class EGAME_MODE : uint8
{
	PVP,
	PVE,
	TUTORIAL,
};

UENUM(BlueprintType)
enum class EGWGameMode : uint8
{
	PVP					UMETA(DisplayName = "PVP"),
	PVE					UMETA(DisplayName = "PVE"),
	TUTORIAL			UMETA(DisplayName = "TUTORIAL"),
//	PvpTestForDev1vs1	UMETA(DisplayName = "PvpTestForDev1vs1"),
//	PveTestForDev2Party	UMETA(DisplayName = "PveTestForDev2Party")
};


UENUM(BlueprintType)
enum class EGWGamePVPRule : uint8
{
	None				UMETA(DisplayName = "None"),
	Deathmatch			UMETA(DisplayName = "Deathmatch"),
	Capture				UMETA(DisplayName = "Capture")
};


UENUM( BlueprintType )
enum class EGWModuleSlotType : uint8
{
	CommonAll       UMETA( DisplayName = "CommonAll" ) ,
	CommonAlpha     UMETA( DisplayName = "CommonAlpha" ) ,
	CommonBeta      UMETA( DisplayName = "CommonBeta" ) ,
	CommonGamma     UMETA( DisplayName = "CommonGamma" ) ,
	CommonDelta     UMETA( DisplayName = "CommonDelta" ) ,
	WeaponAll       UMETA( DisplayName = "WeaponAll" ) ,
	WeaponAlpha     UMETA( DisplayName = "WeaponAlpha" ) ,
	WeaponBeta      UMETA( DisplayName = "WeaponBeta" ) ,
	WeaponGamma     UMETA( DisplayName = "WeaponGamma" ) ,
	WeaponDelta     UMETA( DisplayName = "WeaponDelta" ) ,
	WearableAll     UMETA( DisplayName = "WearableAll" ) ,
	WearableAlpha   UMETA( DisplayName = "WearableAlpha" ) ,
	WearableBeta    UMETA( DisplayName = "WearableBeta" ) ,
	WearableGamma   UMETA( DisplayName = "WearableGamma" ) ,
	WearableDelta   UMETA( DisplayName = "WearableDelta" ) ,
};


UENUM( meta = ( Bitflags , UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class EGWPlayerStateFlag
{
	ECB_None          = 0 ,
	ECB_Fire          = 1 << 0 ,
	ECB_WeaponChange  = 1 << 1 ,
	ECB_Reload        = 1 << 2 ,
	ECB_Zoom          = 1 << 3 ,
	ECB_WeaponSkill   = 1 << 4 ,
	ECB_UltraSkill    = 1 << 5 ,
	ECB_ForceDash     = 1 << 6 ,
	ECB_LoopDash      = 1 << 7 ,
	ECB_ForceAirJump  = 1 << 8 ,
	ECB_LoopAirJump   = 1 << 9 ,
	ECB_ALL           =   EGWPlayerStateFlag::ECB_Fire      | EGWPlayerStateFlag::ECB_WeaponChange | EGWPlayerStateFlag::ECB_Reload   | EGWPlayerStateFlag::ECB_Zoom         | EGWPlayerStateFlag::ECB_WeaponSkill | EGWPlayerStateFlag::ECB_UltraSkill 
	                    | EGWPlayerStateFlag::ECB_ForceDash | EGWPlayerStateFlag::ECB_LoopDash | EGWPlayerStateFlag::ECB_ForceAirJump | EGWPlayerStateFlag::ECB_LoopAirJump,

	ECB_CanFireCondition          = EGWPlayerStateFlag::ECB_WeaponChange | EGWPlayerStateFlag::ECB_WeaponSkill | EGWPlayerStateFlag::ECB_UltraSkill  | EGWPlayerStateFlag::ECB_ForceDash  | EGWPlayerStateFlag::ECB_ForceAirJump ,
	ECB_CanWeaponChangeCondition  = EGWPlayerStateFlag::ECB_WeaponChange | EGWPlayerStateFlag::ECB_WeaponSkill | EGWPlayerStateFlag::ECB_UltraSkill  | EGWPlayerStateFlag::ECB_ForceDash  | EGWPlayerStateFlag::ECB_ForceAirJump ,
	ECB_CanReloadCondition        = EGWPlayerStateFlag::ECB_WeaponChange | EGWPlayerStateFlag::ECB_Reload      | EGWPlayerStateFlag::ECB_WeaponSkill | EGWPlayerStateFlag::ECB_UltraSkill | EGWPlayerStateFlag::ECB_ForceDash     | EGWPlayerStateFlag::ECB_ForceAirJump ,
	ECB_CanZoomCondition          = EGWPlayerStateFlag::ECB_WeaponChange | EGWPlayerStateFlag::ECB_Zoom        | EGWPlayerStateFlag::ECB_WeaponSkill | EGWPlayerStateFlag::ECB_UltraSkill | EGWPlayerStateFlag::ECB_ForceDash     | EGWPlayerStateFlag::ECB_ForceAirJump ,
	ECB_CanWeaponSkillCondition   = EGWPlayerStateFlag::ECB_WeaponChange | EGWPlayerStateFlag::ECB_WeaponSkill | EGWPlayerStateFlag::ECB_UltraSkill  | EGWPlayerStateFlag::ECB_ForceDash  | EGWPlayerStateFlag::ECB_ForceAirJump ,
	ECB_CanUltraSkilCondition     = EGWPlayerStateFlag::ECB_WeaponChange | EGWPlayerStateFlag::ECB_WeaponSkill | EGWPlayerStateFlag::ECB_UltraSkill  | EGWPlayerStateFlag::ECB_ForceDash  | EGWPlayerStateFlag::ECB_ForceAirJump ,
	ECB_CanForceDashCondition     = EGWPlayerStateFlag::ECB_WeaponChange | EGWPlayerStateFlag::ECB_WeaponSkill | EGWPlayerStateFlag::ECB_UltraSkill  | EGWPlayerStateFlag::ECB_ForceDash  | EGWPlayerStateFlag::ECB_ForceAirJump ,
	ECB_CanLoopDashCondition      = EGWPlayerStateFlag::ECB_ALL,
	ECB_CanForceAirJumpCondition  = EGWPlayerStateFlag::ECB_WeaponChange | EGWPlayerStateFlag::ECB_WeaponSkill | EGWPlayerStateFlag::ECB_UltraSkill  | EGWPlayerStateFlag::ECB_ForceDash  | EGWPlayerStateFlag::ECB_ForceAirJump ,
	ECB_CanLoopJumpCondition      = EGWPlayerStateFlag::ECB_ALL,

};
ENUM_CLASS_FLAGS( EGWPlayerStateFlag )

UENUM( BlueprintType )
enum class EGWPlayerState : uint8
{
	None ,
	Fire,
	WeaponChange,
	Reload,
	Zoom,
	WeaponSkill ,
	UltraSkill ,
	ForceDash,
	LoopDash ,
	ForceAirJump ,
	LoopAirJump,

};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWStatType : uint8
{
	None,
	//CharacterStat//   
	Defense                       UMETA( DisplayName = "Ch_Defense" ) ,
	Health                        UMETA( DisplayName = "Ch_Health" ) ,
	HealthRegen                   UMETA( DisplayName = "Ch_HealthRegen" ) ,
	Speed                         UMETA( DisplayName = "Ch_Speed" ) ,
	Stamina                       UMETA( DisplayName = "Ch_Stamina" ) ,
	StaminaRegen                  UMETA( DisplayName = "Ch_StaminaRegen" ) ,
	UltraChargeWeight             UMETA( DisplayName = "Ch_UltraChargeWeight" ) ,
	UltraGaugeMax                 UMETA( DisplayName = "Ch_UltraGaugeMax" ) ,
	BuffDuration                  UMETA( DisplayName = "Ch_BuffDuration" ) ,
	TauntDuration                 UMETA( DisplayName = "Ch_TauntDuration" ) ,
	EntangleDuration              UMETA( DisplayName = "Ch_EntangleDuration" ) ,
	SlowDuration                  UMETA( DisplayName = "Ch_SlowDuration" ) ,
	IncReceiveHealing             UMETA( DisplayName = "Ch_IncReceiveHealing" ) ,
	IncGiveHealing                UMETA( DisplayName = "Ch_IncGiveHealing" ) ,
	IncChainHealing               UMETA( DisplayName = "Ch_IncChainHealing" ) ,
	IncWeaponHealing              UMETA( DisplayName = "Ch_IncWeaponHealing" ) ,
	SkillCooldown                 UMETA( DisplayName = "Ch_SkillCooldown" ) ,
	ReceiveDamageReduction        UMETA( DisplayName = "Ch_ReceiveDamageReduction" ) ,
	ReceiveDamageIncrease         UMETA( DisplayName = "Ch_ReceiveDamageIncrease" ) ,
	WpEffectActivationChance      UMETA( DisplayName = "Ch_WpEffectActivationChance" ) ,
	IncDotRate                    UMETA( DisplayName = "Ch_IncDotRate" ) ,
	//WeaponStat//
	TreatValue ,
	UltraChargerByShot ,
	UltraChargerByHit ,
	TriggerCount ,
	TriggerInterval ,
	ChargeTime ,
	SpoolUpTime ,
	FireInterval ,
	MaxSpread ,
	MaxSpreadZoomIn ,
	IncreaseSpreadAmount ,
	DecreaseSpreadSpeed ,
	MinDamage ,
	MaxDamage ,
	MinDamageScale ,
	WeaponRange ,
	MinDamageRange ,
	MaxDamageRange ,
	DamageScale_Head ,
	DamageScale_Upper ,
	DamageScale_Lower ,
	DamageScale_Arm ,
	MaxCarryAmmo ,
	MagazineCapacity ,
	InitialAmmo ,
	AmmoConsumption ,
	ReloadTime ,
	ReloadAmmoQuantity ,
	EquipTime ,
	ZoomOffset ,
	ZoomFOV ,
	BuckshotCount,
	CriticalDamageRate,
	CriticalChance,
	HeavyArmorDamage,
	LightArmorDamage,
	MediumArmorDamage,
	HeavyArmorRate,
	LightArmorRate,
	MediumArmorRate,
	WeakPointDamage,
	WeakPointRate ,
	IncDamageToAll,
	IncDamageToAR,
	IncDamageToSMG,
	IncDamageToSR,
	IncDamageToLC,
	IncDamageToSG,
	IncDamageToHG,
	IncExplosionRadius,
};
///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWStatCalculateType : uint8
{
	Add ,
	Multiply ,
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWOptionTarget : uint8
{
	Character,
	Weapon,
};

///============================================================================
/// Name	: EGWCustomizeMaterialOrder
///============================================================================
UENUM( BlueprintType )
enum class EGWCustomizeMaterialOrder : uint8
{
	Skin,      ///
	Eye,       ///
	Eyelashes, ///
	Eyebrows,  ///
	Occlusion, ///
	Max,       ///
};

///============================================================================
/// Name	: EGWCustomizeHairMaterialOrder
///============================================================================
UENUM( BlueprintType )
enum class EGWCustomizeHairMaterialOrder : uint8
{
	Skin ,      ///
	Max ,       ///
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWCustomizeTargetMorphOrder : uint8
{
	face_none_01_001,    /// 0
	face_none_01_002,    /// 0
	face_none_01_003,    /// 0
	face_none_01_004,    /// 0
	face_none_01_005,    /// 0
	forehead_none_03,    /// 0
	forehead_none_04,    /// 0
	forehead_none_05,    /// 0
	brow_none_03,        /// 0
	brow_none_04,        /// 0
	brow_none_05,        /// 0
	brow_none_13,        /// 0
	brow_frontbrow_11,   /// 0
	brow_frontbrow_03,   /// 0
	brow_frontbrow_04,   /// 0
	brow_frontbrow_05,   /// 0
	brow_rearbrow_11,    /// 0
	brow_rearbrow_03,    /// 0
	brow_rearbrow_04,    /// 0
	brow_rearbrow_05,    /// 0
	brow_glabella_03,    /// 0
	brow_glabella_05,    /// 0
	eye_none_01,         /// 0
	eye_none_01_001,     /// 1
	eye_none_01_002,     /// 0
	eye_none_01_003,     /// 0
	eye_none_01_004,     /// 0
	eye_none_01_005,     /// 0
	eye_none_01_006,     /// 0
	eye_none_06,         /// 0
	eye_none_03,         /// 0
	eye_none_04,         /// 0
	eye_none_05,         /// 0
	eye_none_13,         /// 0
	eye_topeyelid_03,    /// 0
	eye_topeyelid_04,    /// 0
	eye_downeyelid_04,   /// 0
	eye_downeyelid_12_p, /// 0
	eye_downeyelid_12_m, /// 0
	eye_innereye_03,     /// 0
	eye_innereye_04,     /// 0
	eye_innereye_12_p,   /// 0
	eye_innereye_12_m,   /// 0
	eye_taileye_03,      /// 0
	eye_taileye_04,      /// 0
	ear_none_01_001,     /// 1
	ear_none_01_002,     /// 0
	ear_none_01_003,     /// 0
	ear_none_01_004,     /// 0
	ear_none_01_005,     /// 0
	ear_none_01_006,     /// 0
	ear_none_06,         /// 0
	ear_none_03,         /// 0
	ear_none_04,         /// 0
	ear_none_05,         /// 0
	ear_none_13,         /// 0
	nose_none_01_001,    /// 1
	nose_none_01_002,    /// 0
	nose_none_01_003,    /// 0
	nose_none_01_004,    /// 0
	nose_none_01_005,    /// 0
	nose_none_01_006,    /// 0
	nose_none_06,        /// 0
	nose_none_03,        /// 0
	nose_none_04,        /// 0
	nose_none_05,        /// 0
	nose_bridge_05,      /// 0
	nose_edge_06,        /// 0
	nose_edge_04,        /// 0
	nose_tip_06,         /// 0
	nose_tip_03,         /// 0
	nose_tip_04,         /// 0
	nose_tip_05,         /// 0
	cheekbone_none_06,   /// 0
	cheekbone_none_03,   /// 0
	cheekbone_none_04,   /// 0
	cheekbone_none_05,   /// 0
	chin_none_01_001,    /// 1
	chin_none_01_002,    /// 0
	chin_none_01_003,    /// 0
	chin_none_01_004,    /// 0
	chin_none_01_005,    /// 0
	chin_none_01_006,    /// 0
	chin_none_06,        /// 0
	chin_none_03,        /// 0
	chin_none_04,        /// 0
	chin_none_05,        /// 0
	chin_cheek_06,       /// 0
	chin_tip_06,         /// 0
	chin_tip_03,         /// 0
	chin_tip_04,         /// 0
	chin_tip_05,         /// 0
	mouth_none_01_001,   /// 1
	mouth_none_01_002,   /// 0
	mouth_none_01_003,   /// 0
	mouth_none_01_004,   /// 0
	mouth_none_01_005,   /// 0
	mouth_none_01_006,   /// 0
	mouth_none_06,       /// 0
	mouth_none_03,       /// 0
	mouth_none_04,       /// 0
	mouth_none_05,       /// 0
	mouth_none_13,       /// 0
	mouth_toplip_13,     /// 0
	mouth_lowerlip_13,   /// 0
	mouth_angle_13,      /// 0
	mouth_philtrum_04,   /// 0
	profile_mass_06,     /// 0
	profile_detail_06,   /// 0
	profile_fat_12_p,    /// 0
	profile_fat_12_m,    /// 0
	profile_bust_12_p,   /// 0
	profile_bust_12_m,   /// 0
	profile_hip_06,      /// 0
	max,                 /// 114
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWCustomizeTargetScalarOrder : uint8
{
	skin_age_06,         /// 0
	eye_iris_06,         /// 1
	eye_iris_07,         /// 1
	eye_pupil_06,        /// 1
	mouth_none_08,       /// 0
	skin_none_08,        /// 0
	muscle_detail_06,    /// 0
	browmakeup_none_09,  /// 3
	browmakeup_none_10,  /// 3
	eyemakeup_none_09,   /// 0
	eyemakeup_none_10,   /// 0
	lipmakeup_none_09,   /// 0
	lipmakeup_none_10,   /// 0
	facemakeup_none_09,  /// 0 누락
	facemakeup_none_10,  /// 0 누락
	profile_bodyhair_09, /// 0
	chin_beard_09,       /// 0
	eyeline_none_09 , 	 /// 2020.12.21
  eyeline_none_10 ,    /// 2020.12.21
	eyehighlight_none_09, /// 2020.12.21
	eyehighlight_none_10, /// 2020.12.21
	max,                 /// 17
};

///============================================================================
/// Name	: 
///============================================================================
UENUM( BlueprintType )
enum class EGWCustomizeTargetVectorOrder : uint8
{
	brow_none_02,       /// 3
	eye_iris_02,        /// 1
	eye_pupil_02,       /// ? 0
	skin_none_02,       /// 0
	browmakeup_none_02, /// 3
	eyemakeup_none_02,  /// 0
	lipmakeup_none_02,  /// 0
	facemakeup_none_02, /// 0 누락 8
	eyeline_none_02 ,   /// 2020.12.21
	eyehighlight_none_02, /// 2020.12.21
	max,                ///
};


///============================================================================
/// Name	: T_EGWCustomizeTextureOrder + 00x
///============================================================================
UENUM( BlueprintType )
enum class EGWCustomizeTargetTextureOrder : uint8
{
	brow_none_01 ,       /// 3
	eye_iris_01 ,        /// 1
	eye_pupil_01 ,       /// 1
	skin_none_01 ,       /// 0
	browmakeup_none_01 , /// 3
	eyemakeup_none_01 ,  /// 0
	lipmakeup_none_01 ,  /// 0
	facemakeup_none_01 , /// 0 누락
	tattoo_none_01 ,     /// 0 9
	eyeline_none_01 ,    /// 2020.12.21 
	eyehighlight_none_01 , /// 2020.12.21
	max ,                ///
};