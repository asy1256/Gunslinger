// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Data/GamePlayDataType.h"
#include "GP2_DamageTypeBase.generated.h"
/**
 * 
 */

UENUM( BlueprintType )
enum class EDamageCauserType : uint8
{
	GE_Normal       UMETA( DisplayName = "Normal" ),
	GE_Penetration    UMETA(DisplayName = "Penetration"),
	GE_Impact UMETA( DisplayName = "Impact"),
	GE_Explosion  UMETA( DisplayName = "Explosion" ),
	GE_Plasma  UMETA( DisplayName = "Plasma" ) ,
};

UCLASS()
class GUNSLINGERSW_API UGP2_DamageTypeBase : public UDamageType
{
	GENERATED_BODY()
	

protected:

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite , Category = "DamageTypeData" )
	EDamageCauserType DamageCauserType;

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite , Category ="DamageTypeData")
	class USoundCue* HitSound;

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite , Category = "DamageTypeData")
	class UParticleSystem* HitFx;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DamageTypeData")
    FName  DamageTypeName = TEXT("");

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite , Category = "DamageTypeData" )
	float LightArmorRate;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite , Category = "DamageTypeData" )
	float MediumArmorRate;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite , Category = "DamageTypeData" )
	float HeavyArmorRate;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite , Category = "DamageTypeData" )
	float WeakPointRate;

public:

};
