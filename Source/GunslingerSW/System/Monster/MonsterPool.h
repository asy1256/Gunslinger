// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "./Data/MonsterDataType.h"
#include "MonsterPool.generated.h"

class UDataTable;
class ACharacterMonster;

UCLASS()
class GUNSLINGERSW_API AMonsterPool : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMonsterPool();

	virtual void PostInitializeComponents() override;

public:
	UFUNCTION(BlueprintCallable)
		bool SpawnMonster(const FName tablename, const FTransform transform, ACharacterMonster*& monster, bool& reuse);

private:
	ACharacterMonster* FindRestingMonster(FGWMonPoolData& pooldata);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable*											MonsterTable;

	UPROPERTY(VisibleAnywhere)
	TMap<FName, FGWMonPoolData>							PoolMap;
};
