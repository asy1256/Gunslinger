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

	// TODO : ������ ��ü�� �������� Ŭ��� �����°� ���� �ȵȴ�. �����ؾ��� �������� ����(ex] �ε���)�� �����ϴ°� ������ ����.
	// NOTE : Task ������ ����� ������
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ULevelSequence*									BegineSequence;

	// NOTE : Task �ϼ��� ����� ������
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ULevelSequence*									EndSequence;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	bool											SealOff;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<AActor*>									ShieldingActors;
};
