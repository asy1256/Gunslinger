// Fill out your copyright notice in the Description page of Project Settings.


#include "GWGameState.h"

void AGWGameState::SetMonsterCount(const int count)
{
	if (HasAuthority() == true)
	{ MTC_SetMonsterCount(count); }
}

void AGWGameState::MTC_SetMonsterCount_Implementation(const int count)
{
	MonsterCount = count;
	if (HasAuthority() == false)
	{
		if (OnChangeMonsterCount.IsBound() == true)
		{ OnChangeMonsterCount.Broadcast(MonsterCount);	}
	}
}