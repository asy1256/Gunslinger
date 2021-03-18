// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EntryPoint.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FOnTriggered, AEntryPoint, OnTriggered);

class UBoxComponent;

UCLASS()
class GUNSLINGERSW_API AEntryPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AEntryPoint();

	//UFUNCTION(BlueprintCallable)
	//FOnTriggered& GetTrigerDelegate() { return OnTriggered; }

	UPROPERTY(BlueprintAssignable)
	FOnTriggered OnTriggered;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Box;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool Disposable;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool Triggered;
};
