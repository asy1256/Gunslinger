// Fill out your copyright notice in the Description page of Project Settings.

#include "StatusEffectManager.h"
#include "Engine/World.h"
#include "StatusEffectBase.h"


/* Define a log category for error messages */
DEFINE_LOG_CATEGORY_STATIC(StatusEffectManager, Log, All);


// Sets default values for this component's properties
UStatusEffectManager::UStatusEffectManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	bReplicates = true;
}


bool UStatusEffectManager::HasAuthority() const
{
	AActor* OwnerActor = GetOwner();

	if (OwnerActor)
	{
		if (OwnerActor->HasAuthority())
		{
			return true;
		}
	}

	return false;
}



bool UStatusEffectManager::CheckComponent(const FString& SkillEffectId)
{
	/*
	bool IsValid = false;
	UDataManager* DataManager = UGameBlueprintFunctionLibrary::GetDataManager();
	if (DataManager)
	{
		FST_StatusEffectInfo OutInfo;
		if (DataManager->GetStatusEffectInfo(OutInfo, SkillEffectId))
		{
			return Dic.Contains(OutInfo.AffectType);
		}
	}
	*/
	return false;
}

UStatusEffectBase* UStatusEffectManager::FindStatusEffectComponent(EGWAffectType AffectType)
{

	return *Dic.Find(AffectType);
}

void UStatusEffectManager::AddStatusEffect(UStatusEffectBase* StatusEffectComponet, FString SkillEffectId, AController* InstigatorController)
{
	if (StatusEffectComponet)
	{
		/*
		UDataManager* DataManager = UGameBlueprintFunctionLibrary::GetDataManager();
		if (DataManager)
		{
			FST_StatusEffectInfo OutInfo;
			if (DataManager->GetStatusEffectInfo(OutInfo, SkillEffectId))
			{
				Dic.Add(OutInfo.AffectType, StatusEffectComponet);

				StatusEffectComponet->Server_SetInstigator(InstigatorController);

				StatusEffectComponet->Multi_InitStatusEffect(SkillEffectId);

				UE_LOG(StatusEffectManager, Warning, TEXT("New Status Effect (GM)"));

				// Todo : add Widget

			}
		}
		*/
	}
}

void UStatusEffectManager::RemoveStatusEffect(EGWAffectType AffectType)
{

	Dic.Remove(AffectType);
}