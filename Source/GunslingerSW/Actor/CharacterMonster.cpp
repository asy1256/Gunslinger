#include "CharacterMonster.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "./Controller/MonCtrlBase.h"
// 동적 MaterialInstance 생성을 위해 필요한 헤더
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
// 캡슐 콜리전 설정을 위해 필요한 헤더
#include "Components/CapsuleComponent.h"
// 몽타쥬 재생을 위해 필요한 헤더
#include "Actor/GP2MonsterAnimInstance.h"
#include "TimerManager.h"

ACharacterMonster::ACharacterMonster()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
}

void ACharacterMonster::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACharacterMonster, AnimUseSkill);
	DOREPLIFETIME(ACharacterMonster, AnimAimOffSetX);
	DOREPLIFETIME(ACharacterMonster, AnimAimOffSetY);
	DOREPLIFETIME(ACharacterMonster, AnimIsBattleStance);
	DOREPLIFETIME(ACharacterMonster, AnimIsDead);
	DOREPLIFETIME(ACharacterMonster, AnimGetHit);
	DOREPLIFETIME(ACharacterMonster, AnimIsCriticalHit);
	DOREPLIFETIME(ACharacterMonster, AnimIsJumping);
	DOREPLIFETIME(ACharacterMonster, AnimIsJumpUp);
	DOREPLIFETIME(ACharacterMonster, AnimHitAngle);
	DOREPLIFETIME(ACharacterMonster, AnimIdleAction);
	DOREPLIFETIME(ACharacterMonster, AnimDamageType);
	DOREPLIFETIME(ACharacterMonster, AnimHitBone);
	DOREPLIFETIME(ACharacterMonster, AnimHitBoneWeight);
	DOREPLIFETIME(ACharacterMonster, AnimMaxSpeed);
	DOREPLIFETIME(ACharacterMonster, AnimBattleHowling);
	DOREPLIFETIME(ACharacterMonster, Data);
}

void ACharacterMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	DefaultMeshPosition = this->GetMesh()->RelativeLocation;

	auto skeletal = GetMesh();
	auto anim = Cast<UGP2MonsterAnimInstance>(skeletal->GetAnimInstance());
	anim->MonsterRef = this;

	if (HasAuthority())
	{ return; }

	auto mesh = this->GetMesh();
	auto mats = mesh->GetMaterials();
	
	// Dissolve 적용을 위한 DynamicMaterialInstance 제작
	int32 size = mats.Num();
	DynamicMats.SetNum(size);
	for (int32 i = 0; i < size; i++)
	{
		DynamicMats[i] = mesh->CreateDynamicMaterialInstance(i, mats[i]);
		// NOTE : 하드코딩 되어있으나 해당방법 변경에 대해 R&D 필요 Index를 활용하는 함수가 존재하는걸로 보아 대체가능하지 않을까 생각중
		// BP에서는 현재 변수를 적용시키나 해당변수 초기화되어있는 값인 2.0f를 그대로쓰고 중간에 변경하는건 딱히 보이지 않음
		DynamicMats[i]->SetScalarParameterValue(FName("FresnelShrink"), 2.0f);
		// BP에서 RimLightColor라는 변수를 사용하나 역시나 마찬가지로 따로 변경하는건 보이지 않음
		DynamicMats[i]->SetVectorParameterValue(FName("RimLightColor"), FLinearColor::Blue);
		DynamicMats[i]->SetScalarParameterValue(FName("DissolveControl"), 0.0f);
	}
}

void ACharacterMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	QUICK_SCOPE_CYCLE_COUNTER(STAT_ACharacterMonster)
}

void ACharacterMonster::ReDeployMTC_Implementation(const FTransform& transform)
{
	AnimIsDead = false;
	Data.CurHealth = Data.MaxHealth;
	SetActorTransform(transform);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	if (HasAuthority() == true)
	{
		SimulateRagdollMTC(false);
	}
}

AAIController* ACharacterMonster::GetAiControll()
{
	if (!IsValid(ControllerRef))
	{ ControllerRef = Cast<AAIController>(GetController()); }
	return ControllerRef;
}

void ACharacterMonster::Activate_Implementation()
{
	if (HasAuthority() == false)
		return;

	ActivateMTC();
}

void ACharacterMonster::ActivateMTC_Implementation()
{
	ActivateProcess();
}

void ACharacterMonster::ActivateProcess_Implementation()
{
	Awake = true;

	if (HasAuthority() == true)
	{
		auto aicon = Cast<AMonCtrlBase>(Controller);
		if (aicon != nullptr)
			aicon->Activate();
	}
	else
	{
		ActivateDissolve(false);
		if (Data.SpawnAnim != nullptr)
		{ this->GetMesh()->GetAnimInstance()->Montage_Play(Data.SpawnAnim); }
	}
}

void ACharacterMonster::Deactivate_Implementation()
{
	if (HasAuthority() == false)
		return;

	DeactivateMTC();
}

void ACharacterMonster::DeactivateMTC_Implementation()
{
	DeactivateProcess();
}

void ACharacterMonster::DeactivateProcess_Implementation()
{
	// 사망에 따른 충돌 무효화 처리
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	auto skeletal = GetMesh();
	skeletal->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	skeletal->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);

	// 사망에 따른 애니메이션 재생
	auto anim = Cast<UGP2MonsterAnimInstance>(skeletal->GetAnimInstance());
	if (anim != nullptr)
	{ anim->PlayDieAnimation(AnimHitAngle); }

	if (HasAuthority() == true)
	{
		auto aicon = Cast<AMonCtrlBase>(Controller);
		if (aicon != nullptr)
			aicon->Deactivate();
		GetMovementComponent()->StopMovementImmediately();
		OnDeactivate.Broadcast(this);
	}
}

void ACharacterMonster::SimulateRagdoll_Implementation(const bool active)
{
	if (HasAuthority() == true)
	{ SimulateRagdollMTC(active); }
}

void ACharacterMonster::SimulateRagdollMTC_Implementation(const bool active)
{
	auto skeletal = GetMesh();
	skeletal->SetAllBodiesSimulatePhysics(active);
	
	if (active == true)
	{
		if (DissolveDelay > 0)
		{
			if (GetWorldTimerManager().IsTimerActive(DissolveTimer) == false)
			{ GetWorldTimerManager().SetTimer(DissolveTimer, this, &ACharacterMonster::MakeMonsterDisappear, DissolveDelay); }
		}
	}
	else
	{
		skeletal->ResetAllBodiesSimulatePhysics();
		skeletal->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		skeletal->SetRelativeLocationAndRotation(DefaultMeshPosition, FRotator(0, 0, -90.f), false, nullptr, ETeleportType::ResetPhysics);
		skeletal->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		skeletal->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
	}
}

void ACharacterMonster::MakeMonsterDisappear()
{
	DissolveTimer.Invalidate();
	ActivateDissolve(true);
}
