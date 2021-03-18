// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocationMarker.generated.h"

class UWidgetComponent;

UCLASS()
class GUNSLINGERSW_API ALocationMarker : public AActor
{
	GENERATED_BODY()
	
public:
	ALocationMarker();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(NetMulticast, Reliable)
	void ToggleVisible();
	void ToggleVisible_Implementation();

private:
	void CalDistance();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent*								Widget;
	//Distance between marker and player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float											Distance;
	bool											VisibleFlag;
	APlayerController*								Plcon;
};
