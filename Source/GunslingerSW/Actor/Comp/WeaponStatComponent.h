// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Comp/GWStatComponent.h"
#include "Data/GP2DataStructTypes.h"
#include "WeaponStatComponent.generated.h"

/**
 * 
 */



USTRUCT( BlueprintType )
struct FGWWeaponStatParam 
{
	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		int32                            TreatValue;           ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		int32                            UltraChargerByShot;   ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		int32                            UltraChargerByHit;    ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		int32                            TriggerCount;         ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            TriggerInterval;      ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            ChargeTime;           ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            SpoolUpTime;          ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            FireInterval;         ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            MaxSpread;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            MaxSpreadZoomIn;  ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            IncreaseSpreadAmount; ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            DecreaseSpreadSpeed;  ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            MinDamage;            ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            MaxDamage;            ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            MinDamageScale;       ///  ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            WeaponRange;          ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            MinDamageRange;       ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            MaxDamageRange;       ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            DamageScale_Head;     ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            DamageScale_Upper;    ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            DamageScale_Lower;    ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            DamageScale_Arm;      ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		int32                            MaxCarryAmmo;         ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            MagazineCapacity;     ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		int32                            InitialAmmo;          ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		int32                            AmmoConsumption;      ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            ReloadTime;           ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		int32                            ReloadAmmoQuantity;   ///
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            EquipTime;            ///       
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                            ZoomFOV;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		FVector                         ZoomOffset;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		int32                           BuckshotCount;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                           CriticalDamageRate;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float                           CriticalChance;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float 	                        HeavyArmorDamage;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float 	                        LightArmorDamage;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float	                        MediumArmorDamage;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float	                        WeakPointDamage;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float 	                        HeavyArmorRate;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float 	                        LightArmorRate;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float	                        MediumArmorRate;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float	                        WeakPointRate;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float IncDamageToAll ;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float   IncDamageToAR ;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float	IncDamageToSMG ;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float	IncDamageToSR ;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float	IncDamageToLC ;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float	IncDamageToSG ;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float	IncDamageToHG ;
	UPROPERTY( BlueprintReadWrite , VisibleAnywhere )
		float	IncExplosionRadius ;

};

UCLASS( Blueprintable , BlueprintType , ClassGroup = ( Custom ) , meta = ( BlueprintSpawnableComponent ) )
class GUNSLINGERSW_API UWeaponStatComponent : public UGWStatComponent
{
	GENERATED_BODY()
	
public:

	UWeaponStatComponent();

private :

	UPROPERTY( Transient , Replicated )
	FGWStat  TreatValue;   
	UPROPERTY( Transient , Replicated )///
	FGWStat  UltraChargerByShot; 
	UPROPERTY( Transient , Replicated )///
	FGWStat  UltraChargerByHit; 
	UPROPERTY( Transient , Replicated )///
	FGWStat  TriggerCount;
	UPROPERTY( Transient , Replicated )///
	FGWStat  TriggerInterval;
	UPROPERTY( Transient , Replicated )///
	FGWStat  ChargeTime;
	UPROPERTY( Transient , Replicated )///
	FGWStat  SpoolUpTime;
	UPROPERTY( Transient , Replicated )///
	FGWStat  FireInterval;
	UPROPERTY( Transient , Replicated )///
	FGWStat  MaxSpread;
	UPROPERTY( Transient , Replicated )
	FGWStat  MaxSpreadZoomIn;
	UPROPERTY( Transient , Replicated )///
	FGWStat  IncreaseSpreadAmount;
	UPROPERTY( Transient , Replicated )///
	FGWStat  DecreaseSpreadSpeed;
	UPROPERTY( Transient , Replicated )///
	FGWStat  MinDamage;
	UPROPERTY( Transient , Replicated )///
	FGWStat  MaxDamage;
	UPROPERTY( Transient , Replicated )///
	FGWStat  MinDamageScale;
	UPROPERTY( Transient , Replicated )///  ///
	FGWStat  WeaponRange;
	UPROPERTY( Transient , Replicated )///
	FGWStat  MinDamageRange;
	UPROPERTY( Transient , Replicated )///
	FGWStat  MaxDamageRange;
	UPROPERTY( Transient , Replicated )///
	FGWStat  DamageScale_Head;
	UPROPERTY( Transient , Replicated )//
	FGWStat  DamageScale_Upper;
	UPROPERTY( Transient , Replicated )///
	FGWStat  DamageScale_Lower;
	UPROPERTY( Transient , Replicated )///
	FGWStat  DamageScale_Arm;
	UPROPERTY( Transient , Replicated )///
	FGWStat  MaxCarryAmmo;
	UPROPERTY( Transient , ReplicatedUsing = OnRepNotifyMagazineCapacity )///
	FGWStat  MagazineCapacity;
	UPROPERTY( Transient , Replicated )///
	FGWStat  InitialAmmo;
	UPROPERTY( Transient , Replicated )///
	FGWStat  AmmoConsumption;
	UPROPERTY( Transient , Replicated )///
	FGWStat  ReloadTime;
	UPROPERTY( Transient , Replicated )///
	FGWStat  ReloadAmmoQuantity;
	UPROPERTY( Transient , Replicated )///
	FGWStat  EquipTime;
	UPROPERTY( Transient , Replicated )///
	FGWStat  ZoomFOV;
	UPROPERTY( Transient , Replicated )
	FGWStat  BuckshotCount;;
	UPROPERTY( Transient , Replicated )
	FGWStat  CriticalDamageRate;
	UPROPERTY( Transient , Replicated )
	FGWStat  CriticalChance;
	UPROPERTY( Transient , Replicated )
	FGWStat   HeavyArmorDamage;
	UPROPERTY( Transient , Replicated )
	FGWStat   LightArmorDamage;
	UPROPERTY( Transient , Replicated )
	FGWStat   MediumArmorDamage;
	UPROPERTY( Transient , Replicated )
	FGWStat  WeakPointDamage;
	UPROPERTY( Transient , Replicated )
	FGWStat   HeavyArmorRate;
	UPROPERTY( Transient , Replicated )
	FGWStat    LightArmorRate;
	UPROPERTY( Transient , Replicated )
	FGWStat	  MediumArmorRate;
	UPROPERTY( Transient , Replicated )
	FGWStat	  WeakPointRate;
	UPROPERTY( Transient , Replicated )
	FGWStat IncDamageToAll ;
	UPROPERTY( Transient , Replicated )
	FGWStat   IncDamageToAR ;
	UPROPERTY( Transient , Replicated )
	FGWStat	IncDamageToSMG ;
	UPROPERTY( Transient , Replicated )
	FGWStat	IncDamageToSR ;
	UPROPERTY( Transient , Replicated )
	FGWStat	IncDamageToLC ;
	UPROPERTY( Transient , Replicated )
	FGWStat	IncDamageToSG ;
	UPROPERTY( Transient , Replicated )
	FGWStat	IncDamageToHG ;
	UPROPERTY( Transient , Replicated )
	FGWStat	IncExplosionRadius ;


	UPROPERTY( BlueprintReadWrite , VisibleAnywhere , Category = "WeaponStat" , meta = ( AllowPrivateAccess = "true" ) )
	FVector  ZoomOffset;

protected:

	virtual void SetStatMapping() override;


	UFUNCTION( BlueprintImplementableEvent , Category = "CharacterStat|Function" )
	void MagazineCapacityChangeEvent();
private:
     
	UFUNCTION()
	void OnRepNotifyMagazineCapacity();

public:
	/** 웨폰 스텟 컴포넌트 초기화
	 * @param DefaultStat - 초기 웨폰 스탯 데이터
	 * @param WeaponSlotIndex - 초기화 시킬 웨폰 슬롯
	 */
	UFUNCTION( BlueprintCallable , Category = "CharacterStat|Function" )
	void InitWeaponStatComponent( UPARAM( Ref )const FGWWeaponStatParam& DefaultStat , int32 SlotIndex );

	UFUNCTION( BlueprintPure , Category = "WeaponStat|Function" )
	FGWWeaponStatParam GetWeaponStatParam();

public:

	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		int32 GetTreatValue();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		int32 GetUltraChargerByShot();     
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		int32 GetUltraChargerByHit();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		int32 GetTriggerCount();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		int32 GetInitialAmmo();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		int32 GetMaxCarryAmmo();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		int32 GetAmmoConsumption();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetTriggerInterval();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetChargeTime();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetSpoolUpTime();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetFireInterval();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetMaxSpread();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetMaxSpreadZoomIn();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetIncreaseSpreadAmount();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetDecreaseSpreadSpeed();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetMinDamage();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetMaxDamage();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetMinDamageScale();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetWeaponRange();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetMinDamageRange();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetMaxDamageRange();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetDamageScale_Head();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetDamageScale_Upper();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetDamageScale_Lower();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetDamageScale_Arm();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetMagazineCapacity();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetReloadTime();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetEquipTime();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetZoomFOV();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		int32 GetBuckshotCount();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetCriticalDamageRate();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetCriticalChance();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetHeavyArmorDamage();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetLightArmorDamage();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetMediumArmorDamage();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float GetWeakPointDamage();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float   GetHeavyArmorRate();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float    GetLightArmorRate();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float	GetMediumArmorRate();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float	GetWeakPointRate();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float   GetIncDamageToAll();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float   GetIncDamageToAR() ;
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float	GetIncDamageToSMG() ;
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float	GetIncDamageToSR() ;
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float	GetIncDamageToLC();
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float	GetIncDamageToSG() ;
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float	GetIncDamageToHG() ;
	UFUNCTION( BlueprintPure , Category = "WeaponStat" )
		float	GetIncExplosionRadius() ;
};
