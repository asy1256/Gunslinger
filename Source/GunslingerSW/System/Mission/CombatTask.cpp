#include "CombatTask.h"
#include "./System/Monster/SectorManager.h"
#include "./System/Gimmick/DetectorBase.h"
#include "./Actor/CharacterPC.h"

void ACombatTask::BeginPlay()
{
	Super::BeginPlay();

	SpawnManager->GetWaveCompleteDelegate().AddUObject(this, &ACombatTask::CompleteTask);

	if (TriggerActor != nullptr)
	{ TriggerActor->OnEnter.BindUObject(this, &ACombatTask::EnterActorCheck); }
}

void ACombatTask::ActivateTask()
{
	Super::ActivateTask();

	SpawnManager->StartSpawning();
}

void ACombatTask::EnterActorCheck(AActor* EnterActor)
{
	auto pl = Cast<ACharacterPC>(EnterActor);
	if (pl != nullptr)
	{ StartSequencePlay(); }
}