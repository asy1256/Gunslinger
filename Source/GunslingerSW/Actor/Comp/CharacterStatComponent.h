// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Comp/GWStatComponent.h"
#include "CharacterStatComponent.generated.h"

/**
 * 
 */

/** 캐릭터에 사용되는 스텟 파람*/
USTRUCT( BlueprintType )
struct FGWCharaccterStatParam
{
	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float                            Defense;           ///

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float                            Health;   ///

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float                            HealthRegen;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float                            Speed;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float                            Stamina;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float                            StaminaRegen;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float                            UltraChargeWeight;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float                            UltraGaugeMax;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float BuffDuration ;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float TauntDuration ;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float EntangleDuration ;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float SlowDuration ;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float IncReceiveHealing ;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float IncGiveHealing ;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float IncChainHealing ;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float IncWeaponHealing ;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float SkillCooldown ;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float ReceiveDamageReduction ;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float ReceiveDamageIncrease ;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float WpEffectActivationChance ;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		float IncDotRate ;

};

UCLASS( Blueprintable , BlueprintType , ClassGroup = ( Custom ) , meta = ( BlueprintSpawnableComponent ) )
class GUNSLINGERSW_API UCharacterStatComponent : public UGWStatComponent
{
	GENERATED_BODY()

public:

	UCharacterStatComponent();

private:

	UPROPERTY( Transient , Replicated  )
		FGWStat   Defense;           ///

	UPROPERTY( Transient , Replicated )
		FGWStat   Health;   ///

	UPROPERTY( Transient , Replicated )
		FGWStat   HealthRegen;         ///

	UPROPERTY( Transient , ReplicatedUsing  =  OnRepNotifySpeed)
		FGWStat   Speed;

	UPROPERTY( Transient , Replicated )
		FGWStat   Stamina;

	UPROPERTY( Transient , Replicated )
		FGWStat   StaminaRegen;

	UPROPERTY( Transient , Replicated )

		FGWStat   UltraChargeWeight;

	UPROPERTY( Transient , Replicated )
		FGWStat   UltraGaugeMax;

	UPROPERTY( Transient , Replicated )
		FGWStat BuffDuration ;
	UPROPERTY( Transient , Replicated )
		FGWStat TauntDuration ;
	UPROPERTY( Transient , Replicated )
		FGWStat EntangleDuration ;
	UPROPERTY( Transient , Replicated )
		FGWStat SlowDuration ;
	UPROPERTY( Transient , Replicated )
		FGWStat IncReceiveHealing ;
	UPROPERTY( Transient , Replicated )
		FGWStat IncGiveHealing ;
	UPROPERTY( Transient , Replicated )
		FGWStat IncChainHealing ;
	UPROPERTY( Transient , Replicated )
		FGWStat IncWeaponHealing ;
	UPROPERTY( Transient , Replicated )
		FGWStat SkillCooldown ;
	UPROPERTY( Transient , Replicated )
		FGWStat ReceiveDamageReduction ;
	UPROPERTY( Transient , Replicated )
		FGWStat ReceiveDamageIncrease ;
	UPROPERTY( Transient , Replicated )
		FGWStat WpEffectActivationChance ;
	UPROPERTY( Transient , Replicated )
		FGWStat IncDotRate ;

	
protected:

	virtual void SetStatMapping() override;

	UFUNCTION( BlueprintImplementableEvent , Category = "CharacterStat|Function" )
	void CharacterSpeedRateChangeEvent();

public:

	/** 캐릭터 스텟 컴포넌트 초기화
	 * @param DefaultStat - 초기 캐릭터 스탯 데이터
	 */
	UFUNCTION( BlueprintCallable , Category = "CharacterStat|Function" )
	void InitCharacterStatComponent( UPARAM( Ref )const FGWCharaccterStatParam& DefaultStat );

private:

	UFUNCTION()
	void OnRepNotifySpeed();

public:

	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetDefence();
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetHealth();
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetHealthRegen();
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetSpeed();
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetStamina();
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetStaminaRegen();
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetUltraChargeWeight();
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetUltraGaugeMax();
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetBuffDuration() ;
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetTauntDuration() ;
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetEntangleDuration() ;
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetSlowDuration() ;
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetIncReceiveHealing() ;
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetIncGiveHealing() ;
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetIncChainHealing() ;
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetIncWeaponHealing() ;
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetSkillCooldown() ;
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetReceiveDamageReduction() ;
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetReceiveDamageIncrease() ;
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetWpEffectActivationChance ();
	UFUNCTION( BlueprintPure , Category = "CharacterStat" )
		float GetIncDotRate() ;



};
