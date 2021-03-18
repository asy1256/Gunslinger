// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DetectorBase.generated.h"

DECLARE_DELEGATE_OneParam(FOnEnter, AActor*)
DECLARE_DELEGATE_OneParam(FOnExit, AActor*)

UCLASS()
class GUNSLINGERSW_API ADetectorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADetectorBase();
	virtual void CollisionToggle() {}

public:
	FOnEnter	OnEnter;
	FOnExit		OnExit;

protected:
	bool CollisionFlag;
};
