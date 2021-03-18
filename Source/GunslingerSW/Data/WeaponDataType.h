// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GP2EnumTypes.h"
#include "GameFramework/DamageType.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Texture2D.h"
#include "WeaponDataType.generated.h"

/*
USTRUCT(BlueprintType)
struct FGWWeaponInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	FString                        TempName;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	int32                          Tier;                 ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	EWEaponCatagory                Category;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	int32                          TreatValue;           ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	int32                          UltraChargerByShot;   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	int32                          UltraChargerByHit;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	EGWWeaponAttackType              FireType;             ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	EGWTraceType                     TraceType;            ///

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	//class AProjectileBase*         ProjectileBaseClass;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	int32                          BuckshotCount;        ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	EGWWeaponTriggerType             TriggerType;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	int32                          TriggerCount;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          TriggerInterval;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          ChargeTime;           ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          SpoolUpTime;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          FireInterval;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          MaxSpread;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          IncreaseSpreadAmount; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          DecreaseSpreadSpeed;  ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          MinDamage;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          MaxDamage;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          MinDamageScale;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	UDamageType*                   DamageType;           ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          WeaponRange;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          MinDamageRange;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          MaxDamageRange;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          DamageScale_Head;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          DamageScale_Upper;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          DamageScale_Lower;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          DamageScale_Arm;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	EGWMagazineType                  MagazineType;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	int32                          MaxCarryAmmo;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	int32                          MagazineCapacity;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	int32                          InitialAmmo;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	int32                          AmmoConsumption;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          ReloadTime;           ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	EGWReloadType                    ReloadType;           ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	int32                          ReloadAmmoQuantity;   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	float                          EquipTime;            ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	FString                        WeaponSkill;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	FVector                        ZoomOffset;           ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	bool                           Enable_LaserSight;    

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	//TSubclassOf<class AWeaponBase> WeaponClass;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	bool                           TwoHand;              ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Info")
	EGWSubTriggerType                SubTriggerType;       ///

};
*/

USTRUCT(BlueprintType)
struct FGWAttachWeaponInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Attach Weapon Info")
	FString        WeaponKey;   ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Attach Weapon Info")
	FString        SocketNameL; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Attach Weapon Info")
	USkeletalMesh* WeaponMeshL; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Attach Weapon Info")
	FString        SocketNameR; ///

};

//
//USTRUCT(BlueprintType)
//struct FGWWeaponSkillInfo : public FTableRowBase
//{
//	GENERATED_BODY()
//
//
//public:
//	FGWWeaponSkillInfo()
//		:
//		SkillThumbnail      ( nullptr                ) ,
//		DisplayName         ( TEXT( "" )             ) ,
//		Description         ( TEXT( "" )             ) ,
//		Level               ( 1                      ) ,
//		Cooldown            ( 0.0f                   ) ,
//		SkillDuration       ( 0.0f                   ) ,
//		SkillTargetType     ( EGWSearchAndAction::None ) ,
//		bAllowPrimaryAttack ( false                  ) ,
//		Damage              ( 0.0f                   ) ,
//		Param1              ( 0.0f                   ) ,
//		Param2              ( 0.0f                   ) ,
//		Param3              ( 0.0f                   ) ,
//		Param4              ( 0.0f                   ) ,
//		Param5              ( 0.0f                   )
//	{
//	}
//
//public:
//
//	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Weapon Skill Info" )
//	UTexture2D*      SkillThumbnail;      ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	FString          DisplayName;         ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	FString          Description;         ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	int32            Level;               /// 
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	float            Cooldown;            ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	float            SkillDuration;       ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	EGWSearchAndAction SkillTargetType;     ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	bool             bAllowPrimaryAttack; ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	float            Damage;              ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	float            Param1;              ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	float            Param2;              ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	float            Param3;              ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	float            Param4;              ///
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Weapon Skill Info")
//	float            Param5;              ///
//
//};

USTRUCT(BlueprintType)
struct FGWDefaultWeapon : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Default Weapon" )
	int Weapon01; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Default Weapon" )
	int Weapon02; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|Default Weapon" )
	int Weapon03; ///
};

USTRUCT(BlueprintType)
struct FGWWeaponLinkEx : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|WeaponLink Ex" )
	FString WeaponInfoKey; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|WeaponLink Ex" )
	AActor* WeaponMesh;    ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Struct|WeaponLink Ex" )
	bool    TwoHand;       ///
};
