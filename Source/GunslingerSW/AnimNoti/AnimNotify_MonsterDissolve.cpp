#include "AnimNotify_MonsterDissolve.h"
#include "Components/SkeletalMeshComponent.h"
#include "./Actor/CharacterMonster.h"

void UAnimNotify_MonsterDissolve::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	auto mon = Cast<ACharacterMonster>(MeshComp->GetOwner());
	mon->ActivateDissolve(DoReverse);
}
