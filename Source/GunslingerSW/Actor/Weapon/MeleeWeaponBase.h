// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "MeleeWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class GUNSLINGERSW_API AMeleeWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AMeleeWeaponBase();
	
public:
	virtual void FireBaseLogic() override;

	UFUNCTION()
	void OnMeleeAttack(bool isHold);

	UFUNCTION(Reliable, Server, WithValidation)
	void Server_MeleeAttack(bool isHold);
	void Server_MeleeAttack_Implementation(bool isHold);
	bool Server_MeleeAttack_Validate(bool isHold);
};
