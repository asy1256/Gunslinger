// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_MonsterDissolve.generated.h"

UCLASS(const, hidecategories = Object, collapsecategories, meta = (DisplayName = "Monster Dissolve"))
class GUNSLINGERSW_API UAnimNotify_MonsterDissolve : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool DoReverse;
};
