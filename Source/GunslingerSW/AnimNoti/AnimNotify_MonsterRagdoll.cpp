#include "AnimNotify_MonsterRagdoll.h"
#include "Components/SkeletalMeshComponent.h"
#include "Actor/CharacterMonster.h"

void UAnimNotify_MonsterRagdoll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	auto mon = Cast<ACharacterMonster>(MeshComp->GetOwner());
	if (mon != nullptr)
	{ mon->SimulateRagdoll(true); }
}