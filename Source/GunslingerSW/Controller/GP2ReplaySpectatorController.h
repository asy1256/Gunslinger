// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GP2ReplaySpectatorController.generated.h"

/**
 * 
 */
UCLASS()
class GUNSLINGERSW_API AGP2ReplaySpectatorController : public APlayerController
{
	GENERATED_BODY()

public:

	AGP2ReplaySpectatorController();

protected:

	int32 PreviousAASetting;
	int32 PreviousMBSetting;
public:

	/** ���� ��������� ���÷����� Play �� Pause ���� */
	UFUNCTION(BlueprintCallable, Category = "CurrentReplay")
	bool SetCurrentReplayPausedState(bool bDoPause);

	/** ���÷��������� �ѽð��� ���� */
	UFUNCTION(BlueprintCallable, Category = "CurrentReplay")
		int32 GetCurrentReplayTotalTimeInSeconds() const;

	/** ���� ���÷����� ��� �ð� ���� */
	UFUNCTION(BlueprintCallable, Category = "CurrentReplay")
		int32 GetCurrentReplayCurrentTimeInSeconds() const;

	/** Ư���� ���÷����� �������� �̵��Ѵ� */
	UFUNCTION(BlueprintCallable, Category = "CurrentReplay")
		void SetCurrentReplayTimeToSeconds(int32 Seconds);

	/** �÷��� �ӵ� ������ �����Ѵ� */
	UFUNCTION(BlueprintCallable, Category = "CurrentReplay")
		void SetCurrentReplayPlayRate(float PlayRate = 1.f);
	
};
