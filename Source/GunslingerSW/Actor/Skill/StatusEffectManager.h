// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

//#include "StatusEffectBase.h"

#include "Data/SkillDataType.h"

#include "StatusEffectManager.generated.h"


class UStatusEffectBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUNSLINGERSW_API UStatusEffectManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusEffectManager();



public:
	//TMap<EGWAffectType, UStatusEffectBase> DicStatusEffects;

	TMap<EGWAffectType, UStatusEffectBase*> Dic;

public:
	bool HasAuthority() const;



	bool CheckComponent(const FString& SkillEffectId);

	UStatusEffectBase* FindStatusEffectComponent(EGWAffectType AffectType);

	void AddStatusEffect(UStatusEffectBase* StatusEffectComponet, FString SkillEffectId, AController* InstigatorController);

	void RemoveStatusEffect(EGWAffectType AffectType);
	
};
