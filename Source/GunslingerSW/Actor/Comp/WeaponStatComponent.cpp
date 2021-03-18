// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponStatComponent.h"
#include "Net/UnrealNetwork.h"

// Fill return true;out your copyright notice in the Description page of Project Settings.

/* Define a log category for error messages */
DEFINE_LOG_CATEGORY_STATIC( WeaponStatManager , Log , All );

UWeaponStatComponent::UWeaponStatComponent()
{
	SetStatMapping();
}

FGWWeaponStatParam UWeaponStatComponent::GetWeaponStatParam()
{
	FGWWeaponStatParam Stat = FGWWeaponStatParam();

	return Stat;
}

void UWeaponStatComponent::SetStatMapping()
{
	Super::SetStatMapping();
	
	StatDataMap.Add( EGWStatType::TreatValue ,          &TreatValue );
	StatDataMap.Add( EGWStatType::UltraChargerByShot ,  &UltraChargerByShot );
	StatDataMap.Add( EGWStatType::UltraChargerByHit ,   &UltraChargerByHit  );
	StatDataMap.Add( EGWStatType::TriggerCount ,        &TriggerCount  );
	StatDataMap.Add( EGWStatType::TriggerInterval ,     &TriggerInterval  );
	StatDataMap.Add( EGWStatType::ChargeTime ,          &ChargeTime  );
	StatDataMap.Add( EGWStatType::SpoolUpTime ,         &SpoolUpTime  );
	StatDataMap.Add( EGWStatType::FireInterval ,        &FireInterval  );
	StatDataMap.Add( EGWStatType::MaxSpread ,           &MaxSpread  );
	StatDataMap.Add( EGWStatType::MaxSpreadZoomIn ,     &MaxSpreadZoomIn  );
	StatDataMap.Add( EGWStatType::IncreaseSpreadAmount ,&IncreaseSpreadAmount  );
	StatDataMap.Add( EGWStatType::DecreaseSpreadSpeed , &DecreaseSpreadSpeed  );
	StatDataMap.Add( EGWStatType::MinDamage ,           &MinDamage );
	StatDataMap.Add( EGWStatType::MaxDamage ,           &MaxDamage  );
	StatDataMap.Add( EGWStatType::MinDamageScale ,      &MinDamageScale );
	StatDataMap.Add( EGWStatType::WeaponRange ,         &WeaponRange  );
	StatDataMap.Add( EGWStatType::MinDamageRange ,      &MinDamageRange  );
	StatDataMap.Add( EGWStatType::MaxDamageRange ,      &MaxDamageRange  );
	StatDataMap.Add( EGWStatType::DamageScale_Head ,    &DamageScale_Head  );
	StatDataMap.Add( EGWStatType::DamageScale_Upper ,   &DamageScale_Upper  );
	StatDataMap.Add( EGWStatType::DamageScale_Lower ,   &DamageScale_Lower  );
	StatDataMap.Add( EGWStatType::DamageScale_Arm ,     &DamageScale_Arm  );
	StatDataMap.Add( EGWStatType::MaxCarryAmmo ,        &MaxCarryAmmo  );
	StatDataMap.Add( EGWStatType::MagazineCapacity ,    &MagazineCapacity  );
	StatDataMap.Add( EGWStatType::InitialAmmo ,         &InitialAmmo  );
	StatDataMap.Add( EGWStatType::AmmoConsumption ,     &AmmoConsumption  );
	StatDataMap.Add( EGWStatType::ReloadTime ,          &ReloadTime  );
	StatDataMap.Add( EGWStatType::ReloadAmmoQuantity  , &ReloadAmmoQuantity  );
	StatDataMap.Add( EGWStatType::EquipTime ,           &EquipTime  );
	//StatDataMap.Add( EGWStat::ZoomOffset , TPair<double , double*>( 0 , ( double ) ZoomOffset ) );
	StatDataMap.Add( EGWStatType::ZoomFOV ,             &ZoomFOV  );
	StatDataMap.Add( EGWStatType::BuckshotCount ,       &BuckshotCount );
	StatDataMap.Add( EGWStatType::CriticalDamageRate ,  &CriticalDamageRate );
	StatDataMap.Add( EGWStatType::CriticalChance ,      &CriticalChance );
	StatDataMap.Add( EGWStatType::HeavyArmorDamage ,    &HeavyArmorDamage );
	StatDataMap.Add( EGWStatType::LightArmorDamage ,    &LightArmorDamage );
	StatDataMap.Add( EGWStatType::MediumArmorDamage ,   &MediumArmorDamage );
	StatDataMap.Add( EGWStatType::WeakPointDamage ,     &WeakPointDamage );
	StatDataMap.Add( EGWStatType::HeavyArmorRate ,      &HeavyArmorRate );
	StatDataMap.Add( EGWStatType::LightArmorRate ,      &LightArmorRate );
	StatDataMap.Add( EGWStatType::MediumArmorRate ,     &MediumArmorRate );
	StatDataMap.Add( EGWStatType::WeakPointRate ,       &WeakPointRate );
	StatDataMap.Add( EGWStatType::IncDamageToAll ,      &IncDamageToAll );
	StatDataMap.Add( EGWStatType::IncDamageToAR ,       &IncDamageToAR );
	StatDataMap.Add( EGWStatType::IncDamageToSMG ,      &IncDamageToSMG );
	StatDataMap.Add( EGWStatType::IncDamageToSR ,       &IncDamageToSR );
	StatDataMap.Add( EGWStatType::IncDamageToLC ,       &IncDamageToLC );
	StatDataMap.Add( EGWStatType::IncDamageToSG ,       &IncDamageToSG );
	StatDataMap.Add( EGWStatType::IncDamageToHG ,       &IncDamageToHG );
	StatDataMap.Add( EGWStatType::IncExplosionRadius ,  &IncExplosionRadius );

}

void UWeaponStatComponent::OnRepNotifyMagazineCapacity()
{
	MagazineCapacityChangeEvent();
}


void UWeaponStatComponent::InitWeaponStatComponent( UPARAM( Ref )const FGWWeaponStatParam& DefaultStat , int32 SlotIndex )
{

	SetDefaultStat( DefaultStat.TreatValue ,           EGWStatType::TreatValue );
	SetDefaultStat( DefaultStat.UltraChargerByShot ,   EGWStatType::UltraChargerByShot );
	SetDefaultStat( DefaultStat.UltraChargerByHit ,    EGWStatType::UltraChargerByHit );
	SetDefaultStat( DefaultStat.TriggerCount ,         EGWStatType::TriggerCount );
	SetDefaultStat( DefaultStat.TriggerInterval ,      EGWStatType::TriggerInterval );
	SetDefaultStat( DefaultStat.ChargeTime ,           EGWStatType::ChargeTime );
	SetDefaultStat( DefaultStat.SpoolUpTime ,          EGWStatType::SpoolUpTime );
	SetDefaultStat( DefaultStat.FireInterval ,         EGWStatType::FireInterval );
	SetDefaultStat( DefaultStat.MaxSpread ,            EGWStatType::MaxSpread );
	SetDefaultStat( DefaultStat.MaxSpreadZoomIn ,      EGWStatType::MaxSpreadZoomIn );
	SetDefaultStat( DefaultStat.IncreaseSpreadAmount , EGWStatType::IncreaseSpreadAmount );
	SetDefaultStat( DefaultStat.DecreaseSpreadSpeed ,  EGWStatType::DecreaseSpreadSpeed );
	SetDefaultStat( DefaultStat.MinDamage ,            EGWStatType::MinDamage );
	SetDefaultStat( DefaultStat.MaxDamage ,            EGWStatType::MaxDamage );
	SetDefaultStat( DefaultStat.MinDamageScale ,       EGWStatType::MinDamageScale );
	SetDefaultStat( DefaultStat.WeaponRange ,          EGWStatType::WeaponRange );
	SetDefaultStat( DefaultStat.MinDamageRange ,       EGWStatType::MinDamageRange );
	SetDefaultStat( DefaultStat.MaxDamageRange ,       EGWStatType::MaxDamageRange );
	SetDefaultStat( DefaultStat.DamageScale_Head ,     EGWStatType::DamageScale_Head );
	SetDefaultStat( DefaultStat.DamageScale_Upper ,    EGWStatType::DamageScale_Upper );
	SetDefaultStat( DefaultStat.DamageScale_Lower ,    EGWStatType::DamageScale_Lower );
	SetDefaultStat( DefaultStat.DamageScale_Arm ,      EGWStatType::DamageScale_Arm );
	SetDefaultStat( DefaultStat.MaxCarryAmmo ,         EGWStatType::MaxCarryAmmo );
	SetDefaultStat( DefaultStat.MagazineCapacity ,     EGWStatType::MagazineCapacity );
	SetDefaultStat( DefaultStat.InitialAmmo ,          EGWStatType::InitialAmmo );
	SetDefaultStat( DefaultStat.AmmoConsumption ,      EGWStatType::AmmoConsumption );
	SetDefaultStat( DefaultStat.ReloadTime ,           EGWStatType::ReloadTime );
	SetDefaultStat( DefaultStat.ReloadAmmoQuantity ,   EGWStatType::ReloadAmmoQuantity );
	SetDefaultStat( DefaultStat.EquipTime ,            EGWStatType::EquipTime );
	SetDefaultStat( DefaultStat.ZoomFOV ,              EGWStatType::ZoomFOV );
	SetDefaultStat( DefaultStat.BuckshotCount ,        EGWStatType::BuckshotCount );
	SetDefaultStat( DefaultStat.CriticalDamageRate ,   EGWStatType::CriticalDamageRate );
	SetDefaultStat( DefaultStat.CriticalChance ,       EGWStatType::CriticalChance );
	SetDefaultStat( DefaultStat.HeavyArmorDamage ,     EGWStatType::HeavyArmorDamage );
	SetDefaultStat( DefaultStat.LightArmorDamage ,     EGWStatType::LightArmorDamage );
	SetDefaultStat( DefaultStat.MediumArmorDamage ,    EGWStatType::MediumArmorDamage );
	SetDefaultStat( DefaultStat.WeakPointDamage ,      EGWStatType::WeakPointDamage );
	SetDefaultStat( DefaultStat.HeavyArmorRate ,       EGWStatType::HeavyArmorRate );
	SetDefaultStat( DefaultStat.LightArmorRate ,       EGWStatType::LightArmorRate );
	SetDefaultStat( DefaultStat.MediumArmorRate ,      EGWStatType::MediumArmorRate );
	SetDefaultStat( DefaultStat.WeakPointRate ,        EGWStatType::WeakPointRate );
	SetDefaultStat( DefaultStat.IncDamageToAll ,       EGWStatType::IncDamageToAll );
	SetDefaultStat( DefaultStat.IncDamageToAR ,        EGWStatType::IncDamageToAR );
	SetDefaultStat( DefaultStat.IncDamageToSMG ,       EGWStatType::IncDamageToSMG );
	SetDefaultStat( DefaultStat.IncDamageToSR ,        EGWStatType::IncDamageToSR );
	SetDefaultStat( DefaultStat.IncDamageToLC ,        EGWStatType::IncDamageToLC );
	SetDefaultStat( DefaultStat.IncDamageToSG ,        EGWStatType::IncDamageToSG );
	SetDefaultStat( DefaultStat.IncDamageToHG ,        EGWStatType::IncDamageToHG );
	SetDefaultStat( DefaultStat.IncExplosionRadius ,   EGWStatType::IncExplosionRadius );

	ZoomOffset = DefaultStat.ZoomOffset;

	SetStatRangeDatas();
}

//////////////////// Stat Getter //////////////////////

int32 UWeaponStatComponent::GetTreatValue()        { return TreatValue.GetTotalStatValue(); }

int32 UWeaponStatComponent::GetUltraChargerByShot(){return UltraChargerByShot.GetTotalStatValue();}

int32 UWeaponStatComponent::GetUltraChargerByHit() {return UltraChargerByHit.GetTotalStatValue();}

int32 UWeaponStatComponent::GetTriggerCount()      {return TriggerCount.GetTotalStatValue();}

int32 UWeaponStatComponent::GetMaxCarryAmmo()      {return TriggerInterval.GetTotalStatValue();}

int32 UWeaponStatComponent::GetAmmoConsumption()   {return AmmoConsumption.GetTotalStatValue();}

int32 UWeaponStatComponent::GetInitialAmmo()       { return InitialAmmo.GetTotalStatValue(); }

float UWeaponStatComponent::GetTriggerInterval()   {return TriggerInterval.GetTotalStatValue();}

float UWeaponStatComponent::GetChargeTime()        {return ChargeTime.GetTotalStatValue();}

float UWeaponStatComponent::GetSpoolUpTime()       {return SpoolUpTime.GetTotalStatValue();}

float UWeaponStatComponent::GetFireInterval()      {return FireInterval.GetTotalStatValue();}

float UWeaponStatComponent::GetMaxSpread()         {return MaxSpread.GetTotalStatValue();}

float UWeaponStatComponent::GetMaxSpreadZoomIn()      {return MaxSpreadZoomIn.GetTotalStatValue();}

float UWeaponStatComponent::GetIncreaseSpreadAmount() { return IncreaseSpreadAmount.GetTotalStatValue(); }

float UWeaponStatComponent::GetDecreaseSpreadSpeed(){return DecreaseSpreadSpeed.GetTotalStatValue(); }

float UWeaponStatComponent::GetMinDamage()         { return MinDamage.GetTotalStatValue();}

float UWeaponStatComponent::GetMaxDamage()         { return MaxDamage.GetTotalStatValue();        }

float UWeaponStatComponent::GetMinDamageScale()    { return MinDamageScale.GetTotalStatValue();   }

float UWeaponStatComponent::GetWeaponRange()       { return WeaponRange.GetTotalStatValue();      }

float UWeaponStatComponent::GetMinDamageRange()    { return MinDamageRange.GetTotalStatValue();   }

float UWeaponStatComponent::GetMaxDamageRange()    { return MaxDamageRange.GetTotalStatValue();   }

float UWeaponStatComponent::GetDamageScale_Head()  { return DamageScale_Head.GetTotalStatValue(); }

float UWeaponStatComponent::GetDamageScale_Upper() { return DamageScale_Upper.GetTotalStatValue();}

float UWeaponStatComponent::GetDamageScale_Lower() { return DamageScale_Lower.GetTotalStatValue();}

float UWeaponStatComponent::GetDamageScale_Arm()   { return DamageScale_Arm.GetTotalStatValue();  }

float UWeaponStatComponent::GetMagazineCapacity()  { return MagazineCapacity.GetTotalStatValue(); }

float UWeaponStatComponent::GetReloadTime()        { return ReloadTime.GetTotalStatValue();       }

float UWeaponStatComponent::GetEquipTime()         { return EquipTime.GetTotalStatValue();        }

float UWeaponStatComponent::GetZoomFOV()           { return ZoomFOV.GetTotalStatValue();          }

int32 UWeaponStatComponent::GetBuckshotCount()     { return BuckshotCount.GetTotalStatValue();     }

float UWeaponStatComponent::GetCriticalDamageRate(){return CriticalDamageRate.GetTotalStatValue();}

float UWeaponStatComponent::GetCriticalChance()    { return CriticalChance.GetTotalStatValue(); }

float UWeaponStatComponent::GetHeavyArmorDamage()  { return HeavyArmorDamage.GetTotalStatValue(); }

float UWeaponStatComponent::GetLightArmorDamage()  { return LightArmorDamage.GetTotalStatValue(); }

float UWeaponStatComponent::GetMediumArmorDamage() { return MediumArmorDamage.GetTotalStatValue();}

float UWeaponStatComponent::GetWeakPointDamage()   { return WeakPointDamage.GetTotalStatValue();  }

float UWeaponStatComponent::GetHeavyArmorRate()   {return HeavyArmorRate.GetTotalStatValue();    }

float UWeaponStatComponent::GetLightArmorRate()   { return LightArmorRate.GetTotalStatValue(); }

float UWeaponStatComponent::GetMediumArmorRate()  {return MediumArmorRate.GetTotalStatValue(); }

float UWeaponStatComponent::GetWeakPointRate()
{
	return WeakPointRate.GetTotalStatValue();
}

float UWeaponStatComponent::GetIncDamageToAll()    { return IncDamageToAll.GetTotalStatValue(); }

float UWeaponStatComponent::GetIncDamageToAR()
{
	return IncDamageToAR.GetTotalStatValue();
}

float UWeaponStatComponent::GetIncDamageToSMG()
{
	return IncDamageToSMG.GetTotalStatValue();
}

float UWeaponStatComponent::GetIncDamageToSR()
{
	return IncDamageToSR.GetTotalStatValue();
}

float UWeaponStatComponent::GetIncDamageToLC()
{
	return IncDamageToLC.GetTotalStatValue();
}

float UWeaponStatComponent::GetIncDamageToSG()
{
	return IncDamageToSG.GetTotalStatValue();
}

float UWeaponStatComponent::GetIncDamageToHG()
{
	return IncDamageToHG.GetTotalStatValue();
}

float UWeaponStatComponent::GetIncExplosionRadius()
{
	return IncExplosionRadius.GetTotalStatValue();
}


void UWeaponStatComponent::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( UWeaponStatComponent , TreatValue );
	DOREPLIFETIME( UWeaponStatComponent , UltraChargerByShot );
	DOREPLIFETIME( UWeaponStatComponent , UltraChargerByHit );
	DOREPLIFETIME( UWeaponStatComponent , TriggerCount );
	DOREPLIFETIME( UWeaponStatComponent , TriggerInterval );
	DOREPLIFETIME( UWeaponStatComponent , ChargeTime );
	DOREPLIFETIME( UWeaponStatComponent , SpoolUpTime );
	DOREPLIFETIME( UWeaponStatComponent , FireInterval );
	DOREPLIFETIME( UWeaponStatComponent , MaxSpread );
	DOREPLIFETIME( UWeaponStatComponent , MaxSpreadZoomIn );
	DOREPLIFETIME( UWeaponStatComponent , IncreaseSpreadAmount );
	DOREPLIFETIME( UWeaponStatComponent , DecreaseSpreadSpeed );
	DOREPLIFETIME( UWeaponStatComponent , MinDamage );
	DOREPLIFETIME( UWeaponStatComponent , MaxDamage );
	DOREPLIFETIME( UWeaponStatComponent , MinDamageScale );
	DOREPLIFETIME( UWeaponStatComponent , WeaponRange );
	DOREPLIFETIME( UWeaponStatComponent , MinDamageRange );
	DOREPLIFETIME( UWeaponStatComponent , MaxDamageRange );
	DOREPLIFETIME( UWeaponStatComponent , DamageScale_Head );
	DOREPLIFETIME( UWeaponStatComponent , DamageScale_Upper );
	DOREPLIFETIME( UWeaponStatComponent , DamageScale_Lower );
	DOREPLIFETIME( UWeaponStatComponent , DamageScale_Arm );
	DOREPLIFETIME( UWeaponStatComponent , MaxCarryAmmo );
	DOREPLIFETIME( UWeaponStatComponent , MagazineCapacity );
	DOREPLIFETIME( UWeaponStatComponent , InitialAmmo );
	DOREPLIFETIME( UWeaponStatComponent , AmmoConsumption );
	DOREPLIFETIME( UWeaponStatComponent , ReloadTime );
	DOREPLIFETIME( UWeaponStatComponent , ReloadAmmoQuantity );
	DOREPLIFETIME( UWeaponStatComponent , EquipTime );
	DOREPLIFETIME( UWeaponStatComponent , ZoomFOV );
	DOREPLIFETIME( UWeaponStatComponent , BuckshotCount );
	DOREPLIFETIME( UWeaponStatComponent , CriticalDamageRate );
	DOREPLIFETIME( UWeaponStatComponent , CriticalChance );
	DOREPLIFETIME( UWeaponStatComponent , HeavyArmorDamage );
	DOREPLIFETIME( UWeaponStatComponent , LightArmorDamage );
	DOREPLIFETIME( UWeaponStatComponent , MediumArmorDamage );
	DOREPLIFETIME( UWeaponStatComponent , WeakPointDamage );
	DOREPLIFETIME( UWeaponStatComponent , HeavyArmorRate );
	DOREPLIFETIME( UWeaponStatComponent , LightArmorRate );
	DOREPLIFETIME( UWeaponStatComponent , MediumArmorRate );
	DOREPLIFETIME( UWeaponStatComponent , WeakPointRate );
	DOREPLIFETIME( UWeaponStatComponent , IncDamageToAll );
	DOREPLIFETIME( UWeaponStatComponent , IncDamageToAR );
	DOREPLIFETIME( UWeaponStatComponent , IncDamageToSMG );
	DOREPLIFETIME( UWeaponStatComponent , IncDamageToSR );
	DOREPLIFETIME( UWeaponStatComponent , IncDamageToLC );
	DOREPLIFETIME( UWeaponStatComponent , IncDamageToSG );
	DOREPLIFETIME( UWeaponStatComponent , IncDamageToHG );
	DOREPLIFETIME( UWeaponStatComponent , IncExplosionRadius );

}