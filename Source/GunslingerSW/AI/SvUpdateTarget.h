// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SvUpdateTarget.generated.h"

/**
 * 
 */
UCLASS()
class GUNSLINGERSW_API USvUpdateTarget : public UBTService
{
	GENERATED_BODY()
	
	USvUpdateTarget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector								TargetKey;
};
