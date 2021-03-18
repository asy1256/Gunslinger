// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeWeaponBase.h"
//#include "CharacterBase.h"

// Net
#include "Net/UnrealNetwork.h"

AMeleeWeaponBase::AMeleeWeaponBase()
{
	
	// 델리게이트 바인딩
	//HoldFireDelegate.BindSP(this, &AMeleeWeaponBase::OnMeleeAttack);
	HoldFireDelegate.AddDynamic(this, &AMeleeWeaponBase::OnMeleeAttack);
}


void AMeleeWeaponBase::FireBaseLogic()
{

}


void AMeleeWeaponBase::OnMeleeAttack(bool isHold)
{
	Server_MeleeAttack(isHold);
}

void AMeleeWeaponBase::Server_MeleeAttack_Implementation(bool isHold)
{
	if (Role == ROLE_Authority)
	{
		if (isHold)
		{
			/*
			ACharacterBase* CharacterBase = Cast<ACharacterBase>(GetInstigator());
			if (CharacterBase)
			{
				CharacterBase->OnPlayAttackAnim();
			}
			*/
		}
	}
}

bool AMeleeWeaponBase::Server_MeleeAttack_Validate(bool isHold)
{
	return true;
}