// Fill out your copyright notice in the Description page of Project Settings.

#include "GP2ReplaySpectatorController.h"
#include "Engine/DemoNetDriver.h"
#include "GP2GameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"


AGP2ReplaySpectatorController::AGP2ReplaySpectatorController()
{
	bShowMouseCursor                     = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;
	bShouldPerformFullTickWhenPaused     = true;

}

bool AGP2ReplaySpectatorController::SetCurrentReplayPausedState(bool bDoPause)
{
	AWorldSettings* WorldSettings = GetWorldSettings();

	// MotionBlur를 끄고 앤티 앨리어싱을 FXAA로 설정하여 두 가지 모두의 일시 중지 버그를 우회합니다
	static const auto CVarAA = IConsoleManager::Get().FindConsoleVariable(TEXT("r.DefaultFeature.AntiAliasing"));

	static const auto CVarMB = IConsoleManager::Get().FindConsoleVariable(TEXT("r.DefaultFeature.MotionBlur"));

	if (bDoPause)
	{
		PreviousAASetting = CVarAA->GetInt();
		PreviousMBSetting = CVarMB->GetInt();

		// Set MotionBlur to OFF, Anti-Aliasing to FXAA
		CVarAA->Set(1);
		CVarMB->Set(0);

		WorldSettings->SetPauserPlayerState(PlayerState);
		return true;
	}
	// Rest MotionBlur and AA
	CVarAA->Set(PreviousAASetting);
	CVarMB->Set(PreviousMBSetting);

	WorldSettings->SetPauserPlayerState(nullptr);
	return false;
}

int32 AGP2ReplaySpectatorController::GetCurrentReplayTotalTimeInSeconds() const
{
	if (GetWorld())
	{
		if (GetWorld()->DemoNetDriver)
		{
			return GetWorld()->DemoNetDriver->DemoTotalTime;
		}
	}

	return 0.f;
}

int32 AGP2ReplaySpectatorController::GetCurrentReplayCurrentTimeInSeconds() const
{
	if (GetWorld())
	{
		if (GetWorld()->DemoNetDriver)
		{
			return GetWorld()->DemoNetDriver->DemoCurrentTime;
		}
	}

	return 0.f;
}

void AGP2ReplaySpectatorController::SetCurrentReplayTimeToSeconds(int32 Seconds)
{

	if (GetWorld())
	{

		UGP2GameInstance* GameInstance = Cast<UGP2GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (GetWorld()->DemoNetDriver)
		{
			GetWorld()->DemoNetDriver->GotoTimeInSeconds(Seconds, GameInstance->GoToTimeCompleteDelegate);
		}
	}
}


void AGP2ReplaySpectatorController::SetCurrentReplayPlayRate(float PlayRate)
{
	if (GetWorld())
	{
		if (GetWorld()->DemoNetDriver)
		{
			GetWorld()->GetWorldSettings()->DemoPlayTimeDilation = PlayRate;
		}
	}
}