// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaskBase.generated.h"

class ULevelSequence;
class ADetectorBase;
class ALocationMarker;

UCLASS()
class GUNSLINGERSW_API ATaskBase : public AActor
{
	GENERATED_BODY()
	
public:
	ATaskBase();
	virtual void PrepareTask();

protected:
	virtual void BeginPlay() override;

	virtual void ActivateTask() {}
	virtual void DeactivateTask();
	void CompleteTask();
	void StartSequencePlay();

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	bool											AutoPrepare;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ATaskBase*									NextTask;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ADetectorBase*									TriggerActor;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ALocationMarker*								Marker;

	// TODO : 시퀀서 자체를 서버에서 클라로 던지는건 말이 안된다. 실행해야할 시퀀서의 정보(ex] 인덱스)를 전달하는게 맞을것 같다.
	// NOTE : Task 시작전 재생할 시퀀서
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ULevelSequence*									BegineSequence;

	// NOTE : Task 완수후 재생할 시퀀서
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ULevelSequence*									EndSequence;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	bool											SealOff;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<AActor*>									ShieldingActors;
};
