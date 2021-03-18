// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatComponent.h"
#include "Net/UnrealNetwork.h"


UCharacterStatComponent::UCharacterStatComponent()
{
	SetStatMapping();


}

void UCharacterStatComponent::SetStatMapping()
{
	Super::SetStatMapping();

	StatDataMap.Add( EGWStatType::Defense , &Defense );
	StatDataMap.Add( EGWStatType::Health , &Health );
	StatDataMap.Add( EGWStatType::HealthRegen , &HealthRegen );
	StatDataMap.Add( EGWStatType::Speed , &Speed );
	StatDataMap.Add( EGWStatType::Stamina , &Stamina );
	StatDataMap.Add( EGWStatType::StaminaRegen , &StaminaRegen );
	StatDataMap.Add( EGWStatType::UltraChargeWeight , &UltraChargeWeight );
	StatDataMap.Add( EGWStatType::UltraGaugeMax , &UltraGaugeMax );
	StatDataMap.Add( EGWStatType::BuffDuration , &BuffDuration );
	StatDataMap.Add( EGWStatType::TauntDuration , &TauntDuration );
	StatDataMap.Add( EGWStatType::EntangleDuration , &EntangleDuration );
	StatDataMap.Add( EGWStatType::SlowDuration , &SlowDuration );
	StatDataMap.Add( EGWStatType::IncReceiveHealing , &IncReceiveHealing );
	StatDataMap.Add( EGWStatType::IncGiveHealing , &IncGiveHealing );
	StatDataMap.Add( EGWStatType::IncChainHealing , &IncChainHealing );
	StatDataMap.Add( EGWStatType::IncWeaponHealing , &IncWeaponHealing );
	StatDataMap.Add( EGWStatType::SkillCooldown , &SkillCooldown );
	StatDataMap.Add( EGWStatType::ReceiveDamageReduction , &ReceiveDamageReduction );
	StatDataMap.Add( EGWStatType::ReceiveDamageIncrease , &ReceiveDamageIncrease );
	StatDataMap.Add( EGWStatType::WpEffectActivationChance , &WpEffectActivationChance );
	StatDataMap.Add( EGWStatType::IncDotRate , &IncDotRate );

}

void UCharacterStatComponent::InitCharacterStatComponent( UPARAM( Ref )const FGWCharaccterStatParam & DefaultStat )
{

	SetDefaultStat( DefaultStat.Defense   , EGWStatType::Defense   );
	SetDefaultStat( DefaultStat.Health    , EGWStatType::Health    );
	SetDefaultStat( DefaultStat.HealthRegen , EGWStatType::HealthRegen );
	SetDefaultStat( DefaultStat.Speed , EGWStatType::Speed );
	SetDefaultStat( DefaultStat.Stamina , EGWStatType::Stamina );
	SetDefaultStat( DefaultStat.StaminaRegen , EGWStatType::StaminaRegen );
	SetDefaultStat( DefaultStat.UltraChargeWeight , EGWStatType::UltraChargeWeight );
	SetDefaultStat( DefaultStat.UltraGaugeMax , EGWStatType::UltraGaugeMax );
	SetDefaultStat( DefaultStat.BuffDuration , EGWStatType::BuffDuration );
	SetDefaultStat( DefaultStat.TauntDuration , EGWStatType::TauntDuration );
	SetDefaultStat( DefaultStat.EntangleDuration , EGWStatType::EntangleDuration );
	SetDefaultStat( DefaultStat.SlowDuration , EGWStatType::SlowDuration );
	SetDefaultStat( DefaultStat.IncReceiveHealing , EGWStatType::IncReceiveHealing );
	SetDefaultStat( DefaultStat.IncGiveHealing , EGWStatType::IncGiveHealing );
	SetDefaultStat( DefaultStat.IncChainHealing , EGWStatType::IncChainHealing );
	SetDefaultStat( DefaultStat.SkillCooldown , EGWStatType::SkillCooldown );
	SetDefaultStat( DefaultStat.ReceiveDamageReduction , EGWStatType::ReceiveDamageReduction );
	SetDefaultStat( DefaultStat.ReceiveDamageIncrease , EGWStatType::ReceiveDamageIncrease );
	SetDefaultStat( DefaultStat.WpEffectActivationChance , EGWStatType::WpEffectActivationChance );
	SetDefaultStat( DefaultStat.IncDotRate , EGWStatType::IncDotRate );


	SetStatRangeDatas();
}

void UCharacterStatComponent::OnRepNotifySpeed()
{
	if(GetOwnerRole() < ROLE_Authority)
	{
		APawn* OwnerPawn = Cast<APawn>( GetOwner() );

		if( OwnerPawn != nullptr && OwnerPawn->IsLocallyControlled() == true )
		{
		CharacterSpeedRateChangeEvent();
		}
	}
}

float UCharacterStatComponent::GetDefence()  { return Defense.GetTotalStatValue();  }

float UCharacterStatComponent::GetHealth()   { return Health.GetTotalStatValue();   }

float UCharacterStatComponent::GetHealthRegen(){return HealthRegen.GetTotalStatValue();}

float UCharacterStatComponent::GetSpeed(){return Speed.GetTotalStatValue();}

float UCharacterStatComponent::GetStamina(){return Stamina.GetTotalStatValue();}

float UCharacterStatComponent::GetStaminaRegen(){	return StaminaRegen.GetTotalStatValue();}

float UCharacterStatComponent::GetUltraChargeWeight(){	return UltraChargeWeight.GetTotalStatValue();}

float UCharacterStatComponent::GetUltraGaugeMax(){return UltraGaugeMax.GetTotalStatValue();}

float UCharacterStatComponent::GetBuffDuration()
{
	return BuffDuration.GetTotalStatValue();
}

float UCharacterStatComponent::GetTauntDuration()
{
	return TauntDuration.GetTotalStatValue();
}

float UCharacterStatComponent::GetEntangleDuration()
{
	return EntangleDuration.GetTotalStatValue();
}

float UCharacterStatComponent::GetSlowDuration()
{
	return SlowDuration.GetTotalStatValue();
}

float UCharacterStatComponent::GetIncReceiveHealing()
{
	return IncReceiveHealing.GetTotalStatValue();
}

float UCharacterStatComponent::GetIncGiveHealing()
{
	return IncGiveHealing.GetTotalStatValue();
}

float UCharacterStatComponent::GetIncChainHealing()
{
	return IncChainHealing.GetTotalStatValue();
}

float UCharacterStatComponent::GetIncWeaponHealing()
{
	return IncWeaponHealing.GetTotalStatValue();
}

float UCharacterStatComponent::GetSkillCooldown()
{
	return SkillCooldown.GetTotalStatValue();
}

float UCharacterStatComponent::GetReceiveDamageReduction()
{
	return ReceiveDamageReduction.GetTotalStatValue();
}

float UCharacterStatComponent::GetReceiveDamageIncrease()
{
	return ReceiveDamageIncrease.GetTotalStatValue();
}

float UCharacterStatComponent::GetWpEffectActivationChance()
{
	return WpEffectActivationChance.GetTotalStatValue();
}

float UCharacterStatComponent::GetIncDotRate()
{
	return IncDotRate.GetTotalStatValue();
}

void UCharacterStatComponent::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( UCharacterStatComponent , Defense );
	DOREPLIFETIME( UCharacterStatComponent , Health );
	DOREPLIFETIME( UCharacterStatComponent , HealthRegen );
	DOREPLIFETIME( UCharacterStatComponent , Speed );
	DOREPLIFETIME( UCharacterStatComponent , Stamina );
	DOREPLIFETIME( UCharacterStatComponent , StaminaRegen );
	DOREPLIFETIME( UCharacterStatComponent , UltraChargeWeight );
	DOREPLIFETIME( UCharacterStatComponent , UltraGaugeMax );
	DOREPLIFETIME( UCharacterStatComponent , BuffDuration );
	DOREPLIFETIME( UCharacterStatComponent , TauntDuration );
	DOREPLIFETIME( UCharacterStatComponent , EntangleDuration );
	DOREPLIFETIME( UCharacterStatComponent , SlowDuration );
	DOREPLIFETIME( UCharacterStatComponent , IncReceiveHealing );
	DOREPLIFETIME( UCharacterStatComponent , IncGiveHealing );
	DOREPLIFETIME( UCharacterStatComponent , IncChainHealing );
	DOREPLIFETIME( UCharacterStatComponent , IncWeaponHealing );
	DOREPLIFETIME( UCharacterStatComponent , SkillCooldown );
	DOREPLIFETIME( UCharacterStatComponent , ReceiveDamageReduction );
	DOREPLIFETIME( UCharacterStatComponent , ReceiveDamageIncrease );
	DOREPLIFETIME( UCharacterStatComponent , WpEffectActivationChance );
	DOREPLIFETIME( UCharacterStatComponent , IncDotRate );
}