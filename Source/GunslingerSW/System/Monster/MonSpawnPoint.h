// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "./Data/MonsterDataType.h"
#include "MonSpawnPoint.generated.h"

class USkeletalMeshComponent;
class ACharacterMonster;

UCLASS()
class GUNSLINGERSW_API AMonSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:
	AMonSpawnPoint();

public:
	const bool GetSpawnName(const int32& wavecount IN, const FName*& name OUT);
	const int32 GetWaveCount() { return SpawnList.Num(); }

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	void SetPreviewMesh();
#endif

public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere, Category = "SpawnPoint: DevData")
	USkeletalMeshComponent* PreviewMesh;

	UPROPERTY(EditInstanceOnly, Category = "SpawnPoint: DevData", meta = (ClampMin = 0))
	int32					PreviewIndex;

	UPROPERTY(EditDefaultsOnly, Category = "SpawnPoint: DevData", BlueprintReadOnly)
	UDataTable*				SpawnTable;
#endif

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "SpawnPoint: SystemData", meta = (AllowPrivateAccess = "true"))
	TArray<FName>			RowNames;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "SpawnPoint: SystemData", meta = (AllowPrivateAccess = "true"))
	TArray<int32>			SpawnList;
};
