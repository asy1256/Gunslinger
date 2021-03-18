#include "CharacterMonster.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "./Controller/MonCtrlBase.h"
// ���� MaterialInstance ������ ���� �ʿ��� ���
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
// ĸ�� �ݸ��� ������ ���� �ʿ��� ���
#include "Components/CapsuleComponent.h"
// ��Ÿ�� ����� ���� �ʿ��� ���
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
	
	// Dissolve ������ ���� DynamicMaterialInstance ����
	int32 size = mats.Num();
	DynamicMats.SetNum(size);
	for (int32 i = 0; i < size; i++)
	{
		DynamicMats[i] = mesh->CreateDynamicMaterialInstance(i, mats[i]);
		// NOTE : �ϵ��ڵ� �Ǿ������� �ش��� ���濡 ���� R&D �ʿ� Index�� Ȱ���ϴ� �Լ��� �����ϴ°ɷ� ���� ��ü�������� ������ ������
		// BP������ ���� ������ �����Ű�� �ش纯�� �ʱ�ȭ�Ǿ��ִ� ���� 2.0f�� �״�ξ��� �߰��� �����ϴ°� ���� ������ ����
		DynamicMats[i]->SetScalarParameterValue(FName("FresnelShrink"), 2.0f);
		// BP���� RimLightColor��� ������ ����ϳ� ���ó� ���������� ���� �����ϴ°� ������ ����
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
	// ����� ���� �浹 ��ȿȭ ó��
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	auto skeletal = GetMesh();
	skeletal->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	skeletal->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);

	// ����� ���� �ִϸ��̼� ���
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
