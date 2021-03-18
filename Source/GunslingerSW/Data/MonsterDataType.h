// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GP2EnumTypes.h"
#include "MonsterDataType.generated.h"

class ACharacterMonster;
class UBehaviorTree;
class UAnimMontage;
class USkeletalMesh;


///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWMonster_EQS_Info : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float EQS_InnerRadius;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float EQS_OuterRadius;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float EQS_ArcAngle;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float EQS_ClampingMin;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float EQS_ClampingMax;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float EQS_FloatValueMax;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float EQS_ItemHeightOffset; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float EQS_Param01;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float EQS_Param02;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float EQS_Param03;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float EQS_Param04;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float EQS_Param05;          ///
};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWMonsterSkillInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FString                     Name;                 ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	EGWSkillType                  SkillType;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	int                         Level;                ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                       Range;                ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FString                     SkillFunction;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                       SkillDuration;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                       SuperArmorDuration;   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	int                         SkillTargetType;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	bool                        AllowAnotherAttack;   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	bool                        LockMovement;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                       CoolTime;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                       Damage;               ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FString                     Param1;               ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FString                     Param2;               ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FString                     Param3;               ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FString                     Param4;               ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FString                     Param5;               ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FString                     Param6;               

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	class UAnimMontage*         Animation;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	TSubclassOf< class AActor > Projectile;           ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FName                       ProjectileTableIndex; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	TArray<FString>             SkillEffectID;        ///

};

///============================================================================
/// Name	: 
///============================================================================
USTRUCT(BlueprintType)
struct FGWMonsterStateInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FString                                Mob_ID;                ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	int                                    Mob_Level;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	EGWMobGrade                              Mob_Grade;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FName                                  Mob_Name;              ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                                  Mob_Health;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                                  Mob_Defense;           ///

	// check - BP_Monster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	TSubclassOf< class ACharacterMonster > Mob_ClassBP;           ///

	// UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	//  비헤이비어트리 Mob_BrainBT;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                                  Mob_CSight;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                                  Mob_BSight;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	EGWMobMoveType                           Mob_MoveType;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                                  Mob_CSpeed;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                                  Mob_BSpeed;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	bool                                   Mob_Aggressive;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FName                                  Mob_PassiveSkill;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	TArray<FName>                          Mob_Skill;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	int                                    Mob_TeamId;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	class UTexture2D*                      Mob_Image;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FString                                Mob_Info;              ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FName                                  Mob_RewardID;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	int                                    Mob_RewardExp;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	int                                    Mob_RewardMoney;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	EGWMobRace                               Mob_Race;              ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                                  Mob_Attack;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	TArray<EGWAffectType>                    Mob_ImmuneList;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	TArray<EGWMobSpawnActionType>            Mob_SpawnActionType;   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                                  Mob_BattleInnerRadius; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	float                                  Mob_BattleOuterRadius; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	EGWMobRoamingType                        Mob_RoamingType;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	FName                                  Mob_EQSID;             ///
};

///============================================================================
// NOTE : 몬스터의 등급 / 추가 By.안성용
///============================================================================
UENUM(BlueprintType)
enum class EGWGrade : uint8
{
	NORMAL,
	ELITE,
	BOSS
};

///============================================================================
// NOTE : 몬스터가 사용할 시각정보 구조체 / 추가 By.안성용
///============================================================================
USTRUCT(BlueprintType)
struct FGWSightData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float									SightRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float									LoseRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float									SightAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float									MaxAge;
};

///============================================================================
// NOTE : 몬스터의 필수정보를 담은 구조체 / 추가 By.안성용
///============================================================================
USTRUCT(BlueprintType)
struct FGWMonData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGWGrade								Grade;

	// TODO : 몬스터에게 레벨을 부여할지는 애매합니다. 사용여부를 확실히 해야합니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int										Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float									MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float									CurHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float									Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float									Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "Move speed in battle state"))
	float									Cspeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "Default move speed"))
	float									Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage*							SpawnAnim;
};

///============================================================================
// NOTE : 몬스터를 생성할때 사용하는 구조체 / 추가 By.안성용
///============================================================================
USTRUCT(BlueprintType)
struct FGWMonSpawnData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName									Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D*								Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName									Info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacterMonster>			Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBehaviorTree*							BtAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool									Aggressive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGWSightData							SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGWMonData								MonData;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//EGWMoveType MoveType;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//EGWRoamingType RoamingType;
};

USTRUCT(BlueprintType)
struct FGWMonPoolData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FGWMonSpawnData							SpawnData;

	UPROPERTY(VisibleAnywhere)
	TArray<ACharacterMonster*>				MonPool;
};
