// Fill out your copyright notice in the Description page of Project Settings.


#include "SvUpdateTarget.h"
#include "Actor/CharacterPC.h"
#include "Actor/GP2AiController.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"

USvUpdateTarget::USvUpdateTarget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(USvUpdateTarget, TargetKey), ACharacterPC::StaticClass());
}

void USvUpdateTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (BBAsset)
	{ TargetKey.ResolveSelectedKey(*BBAsset); }
	else
	{ UE_LOG(LogBehaviorTree, Warning, TEXT("Can't initialize service: %s, make sure that behavior tree specifies blackboard asset!"), *GetName()); }
}

void USvUpdateTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AGP2AiController* con = Cast<AGP2AiController>(OwnerComp.GetAIOwner());
	if (con)
	{
		UBlackboardComponent* bb = OwnerComp.GetBlackboardComponent();
		ACharacterPC* pl = nullptr;

		//if (con->EnemyList.Num() > 0)
		//{
		//	float dist = INFINITY;
		//	float caldist = 0;
		//
		//	int32 size = con->EnemyList.Num();
		//	for (int32 i = 0; i < size; i++)
		//	{
		//		if (con->EnemyList.IsValidIndex(i))
		//		{
		//			if (con->EnemyList[i]->IsPendingKill())
		//			{
		//				con->EnemyList.RemoveAt(i, 1, false);
		//				continue;
		//			}
		//
		//			caldist = con->EnemyList[i]->GetDistanceTo(con->GetPawn());
		//			if (caldist < dist)
		//			{
		//				dist = caldist;
		//				pl = con->EnemyList[i];
		//			}
		//		}
		//	}
		//}

		//if (pl != nullptr)
		//{ UE_LOG(LogBehaviorTree, Warning, TEXT("[%s] Suscessfully set new target"), *con->GetName()); }

		bb->SetValueAsObject(TargetKey.SelectedKeyName, pl);
	}
	//else
	//{ UE_LOG(LogBehaviorTree, Warning, TEXT("Monster don't have GP2AiController")); }
}