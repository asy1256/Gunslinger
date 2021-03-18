// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../Data/MonsterDataType.h"
#include "GP2AiController.generated.h"

/**
 *
 */
UCLASS()
class GUNSLINGERSW_API AGP2AiController : public AAIController
{
	GENERATED_BODY()
public:
	AGP2AiController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* Pawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override;

	UFUNCTION(BlueprintCallable, Category = "Perception")
		void SetNewSightData();

	UFUNCTION(BLueprintCallable, Category = "Perception")
		void SetSightData(const FGWSightData& data);

	UFUNCTION()
		void OnPawnDetected(TArray<AActor*> DetectedPawns);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AILoseSightRadius = AISightRadius + 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 90.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UAISenseConfig_Sight* SightConfig;

};
