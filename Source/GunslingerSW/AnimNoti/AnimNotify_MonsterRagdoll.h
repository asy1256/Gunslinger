// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_MonsterRagdoll.generated.h"

/**
 * 
 */
UCLASS(const, hidecategories = Object, collapsecategories, meta = (DisplayName = "Monster Ragdoll"))
class GUNSLINGERSW_API UAnimNotify_MonsterRagdoll : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
