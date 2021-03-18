// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SkillInterface.generated.h"

/**
 * 
 */
UINTERFACE(BlueprintType)
class USkillInterface : public UInterface
{
	GENERATED_BODY()

};


class ISkillInterface
{
	GENERATED_BODY()

public:
	

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "SKill Owner Info")
	float GetDefence();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "SKill Owner Info")
	float GetDamage();

	/*UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SKill Owner Info")
	TArray<class USkillComponent*> GetSkillComponent() const;*/

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SKill Owner Info")
	uint8 GetTeamId();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SKill Owner Info")
	float GetMaxHP();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SKill Owner Info")
	bool GetIsDead();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SKill Owner Info")
	USkeletalMeshComponent* GetOwnerMesh();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SKill Owner Info")
	USkeletalMeshComponent* GetCurWeaponMesh();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "SKill Owner Info")
	bool GetIsHiding();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "SKill Owner Info")
	bool GetIsShock();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "SKill Owner Info")
	bool GetIsStun();

};