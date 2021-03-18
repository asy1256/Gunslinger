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

	/** 현재 재생중인인 리플레이의 Play 와 Pause 설정 */
	UFUNCTION(BlueprintCallable, Category = "CurrentReplay")
	bool SetCurrentReplayPausedState(bool bDoPause);

	/** 리플레이파일의 총시간을 리턴 */
	UFUNCTION(BlueprintCallable, Category = "CurrentReplay")
		int32 GetCurrentReplayTotalTimeInSeconds() const;

	/** 현제 리플레이의 재생 시간 리턴 */
	UFUNCTION(BlueprintCallable, Category = "CurrentReplay")
		int32 GetCurrentReplayCurrentTimeInSeconds() const;

	/** 특정한 리플레이의 구간으로 이동한다 */
	UFUNCTION(BlueprintCallable, Category = "CurrentReplay")
		void SetCurrentReplayTimeToSeconds(int32 Seconds);

	/** 플레이 속도 비율을 설정한다 */
	UFUNCTION(BlueprintCallable, Category = "CurrentReplay")
		void SetCurrentReplayPlayRate(float PlayRate = 1.f);
	
};
