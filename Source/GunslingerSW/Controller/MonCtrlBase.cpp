#include "MonCtrlBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Actor/CharacterPC.h"

void AMonCtrlBase::Activate()
{
	ActivateProcess();
}

void AMonCtrlBase::ActivateProcess_Implementation()
{
	if (BrainComponent != nullptr)
	{
		BrainComponent->RestartLogic();
	}
	else
	{
		if (BTAsset != nullptr)
			RunBehaviorTree(BTAsset);

		auto ctrlpawn = GetPawn();
		if (ctrlpawn != nullptr)
			GetBlackboardComponent()->SetValueAsVector(FName("HomeLocation"), ctrlpawn->GetActorLocation());
	}
}

void AMonCtrlBase::Deactivate()
{
	DeactivateProcess();
}

void AMonCtrlBase::DeactivateProcess_Implementation()
{
	BrainComponent->StopLogic("Deactivate monster");
}

void AMonCtrlBase::SetSightData(const FGWSightData& data)
{
	if (SightConfig == nullptr)
	{
		this->AddSightConfig();
	}

	SightConfig->SightRadius = data.SightRadius;
	SightConfig->LoseSightRadius = data.LoseRadius;
	SightConfig->PeripheralVisionAngleDegrees = data.SightAngle;
	SightConfig->SetMaxAge(data.MaxAge);
}

void AMonCtrlBase::PerceptionTargetUpdated(AActor* actor, FAIStimulus stimulus)
{
	if (stimulus.Type == SightConfig->GetSenseID())
	{
		ACharacterPC* pl = Cast<ACharacterPC>(actor);
		if (pl == nullptr)
		{
			return;
		}

		int32 id = 0;
		bool result = EnemyList.Find(pl, id);
		if (result == true)
		{
			EnemyList.RemoveAt(id);
		}
		else
		{
			EnemyList.AddUnique(pl);
		}
	}
}

void AMonCtrlBase::AddSightConfig()
{
	if (PerceptionComponent == nullptr)
	{
		this->ActivatePerceptionSystem();
	}

	SightConfig = NewObject<UAISenseConfig_Sight>(this, FName("SightConfig"));
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMonCtrlBase::PerceptionTargetUpdated);
}

void AMonCtrlBase::ActivatePerceptionSystem()
{
	PerceptionComponent = NewObject<UAIPerceptionComponent>(this, FName("PerceptionComp"));
}