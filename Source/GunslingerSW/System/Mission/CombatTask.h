// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/Mission/TaskBase.h"
#include "CombatTask.generated.h"

class ASectorManager;

/**
 * 
 */
UCLASS()
class GUNSLINGERSW_API ACombatTask : public ATaskBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	virtual void ActivateTask() override;

private:
	UFUNCTION()
	void EnterActorCheck(AActor* EnterActor);

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ASectorManager* SpawnManager;
};
