// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissionBase.generated.h"

class AEntryPoint;

UCLASS()
class GUNSLINGERSW_API AMissionBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AMissionBase();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AEntryPoint* Entry;
};
