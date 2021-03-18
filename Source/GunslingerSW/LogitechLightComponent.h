// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LogitechLightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class GUNSLINGERSW_API ULogitechLightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULogitechLightComponent();

	UFUNCTION(BlueprintCallable, Category = "LogitechSDK")
	//bool UpdateLighting(const int redPercentage, const int greenPercentage, const int bluePercentage);
	bool UpdateLighting(const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, Category = "LogitechSDK")
	bool UpdateFlashLighting(const FLinearColor& colorParam, const int milliSecondsDuration, const int milliSecondsInterval);

	UFUNCTION(BlueprintCallable, Category = "LogitechSDK")
	bool UpdatePulseLighting(const FLinearColor& colorParam, const int milliSecondsDuration, const int milliSecondsInterval);

	UFUNCTION(BlueprintCallable, Category = "LogitechSDK")
	bool UpdateLightingfromBitmap(const TArray<uint8>& bitmap);

	UFUNCTION(BlueprintCallable, Category = "LogitechSDK")
	void LogitechShutDown();

	UFUNCTION(BlueprintCallable, Category = "LogitechSDK")
	bool IsAvailable();

	UFUNCTION(BlueprintCallable, Category = "LogitechSDK")
	bool LogitechInit();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
