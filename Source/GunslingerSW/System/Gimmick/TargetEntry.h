// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/Gimmick/EntryPoint.h"
#include "TargetEntry.generated.h"

class ACharacterBase;

/**
 * 
 */
UCLASS()
class GUNSLINGERSW_API ATargetEntry : public AEntryPoint
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void Enter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACharacterBase> TargetClass;
};
