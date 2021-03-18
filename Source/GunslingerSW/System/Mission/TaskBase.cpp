#include "TaskBase.h"
#include "LevelSequence.h"
#include "./System/Gimmick/DetectorBase.h"
#include "./System/Gimmick/LocationMarker.h"

ATaskBase::ATaskBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATaskBase::BeginPlay()
{
	Super::BeginPlay();

	if (AutoPrepare)
	{ PrepareTask(); }
}

void ATaskBase::PrepareTask()
{
	GEngine->AddOnScreenDebugMessage(4, 5.0f, FColor::Red, FString("Prepare Task"));
	TriggerActor->CollisionToggle();
	Marker->ToggleVisible();
}

void ATaskBase::StartSequencePlay()
{
	GEngine->AddOnScreenDebugMessage(5, 5.0f, FColor::Yellow, FString("Task Triggered"));
	Marker->ToggleVisible();
	TriggerActor->CollisionToggle();

	if (BegineSequence)
	{
		// TODO : Request sequence play to GameMode then sequence is ended call ActivateTask Function
		auto gmode = GetWorld()->GetAuthGameMode();
		if (gmode != nullptr)
		{
			//gmode->PlayTaskSequence(BegineSequence);
		}
	}
	else { ActivateTask(); }
}

void ATaskBase::CompleteTask()
{
	if (EndSequence)
	{
		// TODO : Request sequence play to GameMode then sequence is ended call Deactivate Function
		auto gmode = GetWorld()->GetAuthGameMode();
		if (gmode != nullptr)
		{
			//gmode->PlayTaskSequence(BegineSequence);
		}
	}
	else { DeactivateTask(); }
}

void ATaskBase::DeactivateTask()
{
	GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Yellow, FString("Task completed!"));
	if (NextTask)
	{
		NextTask->PrepareTask();
		GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Yellow, FString("Prepare next task"));
	}
}