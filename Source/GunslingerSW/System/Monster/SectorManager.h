// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SectorManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnWaveComplete);

class AMonSpawnPoint;
class ACharacterMonster;

UCLASS()
class GUNSLINGERSW_API ASectorManager : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASectorManager();

	virtual void PostInitializeComponents() override;
	void StartSpawning();
	FOnWaveComplete& GetWaveCompleteDelegate() { return OnWaveComplete; }

protected:
	void DecreaseMonsterCount(ACharacterMonster* deactivatemon);

private:
	void NextWaveCheck();
	void SpawnMonster();
	void SpawnComplete();

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TArray<AMonSpawnPoint*>		SpawnPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int32						MonCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int32						TotalWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int32						CurrentWave;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ClampMin = 0, ToolTip = "Next wave begins automatically after a delay. if the value is 0, current wave must be completed"))
		float						WaveDelay;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool						LoopEnable;

	FTimerHandle SpawnTimer;
	FOnWaveComplete OnWaveComplete;

};
