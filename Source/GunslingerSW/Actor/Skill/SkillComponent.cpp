// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "SkillInterface.h"
//#include "ProjectileBase.h"
//#include "SkillActorBase.h"

//#include "CharacterBase.h"
//#include "WeaponBase.h"
//#include "BattleGM.h"

#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Custum Static Library
//#include "StaticFunctionLibrary.h"


// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bReplicates = true;
	
}


// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (HasSkillData)
	{
		UpdateTime(DeltaTime);
	}
}

void USkillComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USkillComponent, SkillData);

	DOREPLIFETIME(USkillComponent, HasSkillData);

	DOREPLIFETIME(USkillComponent, SkillTime);

	DOREPLIFETIME(USkillComponent, CastTime);

	DOREPLIFETIME(USkillComponent, HoldFireTime);

	DOREPLIFETIME(USkillComponent, SkillDurationTime);

	DOREPLIFETIME(USkillComponent, IsRunSkill);

	DOREPLIFETIME(USkillComponent, IsCasting);

}

bool USkillComponent::HasAuthority() const
{
	AActor* OwnerActor = GetOwner();
	
	if (OwnerActor)
	{
		if (OwnerActor->HasAuthority())
		{
			return true;
		}
	}

	return false;
}

// ############# [ Update Time ] ###############
void USkillComponent::UpdateTime(float delta)
{
	if (HasAuthority())
	{
		// Cool Time
		UpdateCoolTime(delta);

		// Cast Time
		UpdateCastTime(delta);

		// Hold Time
		UpdateHoldTime(delta);

		// Skill Duration Time
		UpdateDurationTime(delta);
	}
}

// Cool Time
void USkillComponent::UpdateCoolTime(float delta)
{
	if (!IsCasting && !IsRunSkill)
	{
		SkillTime = UKismetMathLibrary::FClamp(SkillTime + delta, 0.0f, SkillData.CoolTime);
	}
}

// Cast Time
void USkillComponent::UpdateCastTime(float delta)
{
	if (IsCasting)
	{
		CastTime = UKismetMathLibrary::FClamp(CastTime + delta, 0.0f, SkillData.CastTime);
		

		/*FString str = " Cast Time : " + FString::SanitizeFloat(delta);
		GLog->Log(str);*/

		if (CastTime >= SkillData.CastTime)
		{
			Server_OnActiveSkill();
		}
	}
	
}

// Hold Time
void USkillComponent::UpdateHoldTime(float delta)
{
	if (IsHoldFire)
	{
		HoldFireTime = UKismetMathLibrary::FClamp(HoldFireTime + delta, 0.0f, SkillData.PassiveConditionParam);
	}
}

// Skill Duration Time
void USkillComponent::UpdateDurationTime(float delta)
{
	if (IsRunSkill)
	{
		SkillDurationTime = UKismetMathLibrary::FClamp(SkillDurationTime + delta, 0.0f, SkillData.SkillDuration);

		if (SkillDurationTime >= SkillData.SkillDuration)
		{
			IsRunSkill = false;
			IsCasting = false;
			SkillTime = 0.0f;
		}
	}
}

// Can Skill?
bool USkillComponent::CanSkill() const
{
	if (!HasSkillData) return false;

	if (IsCasting) return false;

	return (SkillTime >= SkillData.CoolTime && !IsRunSkill);
}


void USkillComponent::InitSKillData_Implementation(struct FGWSkillInfo SkillInfo)
{
	if (!HasAuthority()) return;

	SkillData = SkillInfo;

	HasSkillData = true;

	CastTime = 0.0f;

	SkillTime = SkillData.CoolTime;

	// Todo : Load Skill Actor Data Table




	// Initialize Passive Skill
	if (SkillData.SkillType == EGWSkillType::Passive)
	{
		GLog->Log("Init Passive Skill");


		switch (SkillData.PassiveConditionType)
		{
		case EGWPassiveConditionType::Always :
			Server_RunSkill();
			break;
		case EGWPassiveConditionType::BelowHP:
			break;
		case EGWPassiveConditionType::Killed:
			break;
		case EGWPassiveConditionType::KeepAttack:
			break;
		}
	}
}

bool USkillComponent::InitSKillData_Validate(struct FGWSkillInfo SkillInfo)
{
	return true;
}


float USkillComponent::GetSkillDamage() const
{
	if (HasSkillData)
	{
		AActor* OwnerActor = GetOwner();
		APawn* InstigatorPawn = OwnerActor->GetInstigator();
		if (OwnerActor && InstigatorPawn->GetClass()->ImplementsInterface(USkillInterface::StaticClass()))
		{
			const float BaseDamage = ISkillInterface::Execute_GetDamage(InstigatorPawn);
			return SkillData.SkillDamageRate * BaseDamage;
		}
	}

	return 0.0f;
}

// Cast Transform
FTransform USkillComponent::GetCastTransform() const
{
	FTransform CastTransform;

	/*
	// Todo : Make Cast Transform
	CastTransform = GetOwner()->GetTransform();
	

	AActor* OwnerActor = GetOwner();
	APawn* InstigatorPawn = OwnerActor->GetInstigator();
	if (OwnerActor && InstigatorPawn->GetClass()->ImplementsInterface(USkillInterface::StaticClass()))
	{
		USkeletalMeshComponent* CharacterMesh = ISkillInterface::Execute_GetOwnerMesh(InstigatorPawn);
		USkeletalMeshComponent * WeaponMesh = ISkillInterface::Execute_GetCurWeaponMesh(InstigatorPawn);


		if (SkillData.CastLocationType == EGWCastLocationType::Character)
		{
			if (SkillData.SkillCategory == EGWSkillCategoty::WeaponSkill)
			{
				if (CharacterMesh)
				{
					FVector SocketLocation = CharacterMesh->GetSocketLocation(SkillData.SkillSocketName);
					FRotator SocketRotation = CharacterMesh->GetSocketRotation(SkillData.SkillSocketName);

					FVector Offset = UKismetMathLibrary::GreaterGreater_VectorRotator(SkillData.CastLocOffset, CharacterMesh->GetComponentRotation());

					FRotator CalculRot = (SocketRotation - CharacterMesh->RelativeRotation) + SkillData.CastRotOffset;



					// return value
					CastTransform.SetLocation(SocketLocation + Offset);
					CastTransform.SetRotation(FQuat(CalculRot));

				}
			}
			else if (SkillData.SkillCategory == EGWSkillCategoty::UltimateSkill)
			{
				// Todo : Ultimate Skill Cast Location & Rotation


			}
		}
		else if (SkillData.CastLocationType == EGWCastLocationType::Weapon)
		{
			ACharacterBase* Character = Cast<ACharacterBase>(InstigatorPawn);
			if (Character)
			{

				FVector CamLoc;
				FRotator CamRot;

				APlayerController* PlayerController = Cast<APlayerController>(InstigatorPawn->GetController());
				if (PlayerController)
					PlayerController->GetPlayerViewPoint(CamLoc, CamRot);


				const FVector Direction = CamRot.Vector();

				FVector Start = Character->CurrentWeapon->GetTraceStartLocation();
				FVector End = Start + (Direction * 5000.0f);

				FHitResult OutHit;
				TArray<AActor*> IgnoreActors;
				IgnoreActors.Add(OwnerActor);
				IgnoreActors.Add(InstigatorPawn);


				bool IsHit = UStaticFunctionLibrary::SphereTraceByChannel(
					GetWorld(),
					OutHit,
					Start,
					End,
					20.0f,
					ECC_Visibility,
					false,
					IgnoreActors);

				FVector TargetLocation = IsHit ? OutHit.ImpactPoint : End;

				FRotator CalculRot = UKismetMathLibrary::FindLookAtRotation(Start, TargetLocation);

				// return value
				CastTransform.SetLocation(Start);
				CastTransform.SetRotation(FQuat(CalculRot));

			}
		}

	}
	*/
	return CastTransform;
}


void USkillComponent::OnCastSkill()
{
	if (HasAuthority())
	{
		if (SkillData.CastTime > 0)
		{
			IsCasting = true;
			CastTime = 0.0f;
			SkillTime = 0.0f;
		}
		else
		{
			Server_OnActiveSkill();
		}
	}
}


void USkillComponent::ApplyBuffEffect()
{
	/*
	if (HasSkillActor)
	{
		Client_SpawnSkillActor();
	}
	else
	{
		ABattleGM* BattleGM = GetWorld()->GetAuthGameMode<ABattleGM>();
		// GameMode Check
		if (!BattleGM && !BattleGM->IsValidLowLevel()) return;

		AActor* OwnerActor = GetOwner();
		APawn* InstigatorPawn = OwnerActor->GetInstigator();
		if (OwnerActor && InstigatorPawn->GetClass()->ImplementsInterface(USkillInterface::StaticClass()))
		{
			USkeletalMeshComponent* CharacterMesh = ISkillInterface::Execute_GetOwnerMesh(InstigatorPawn);


			// Todo : Apply Buff
			if (SkillData.SkillTargetType == EGWSearchTarget::Self)
			{
				const TArray<FString> SkillEffectIdArray = SkillData.SkillEffectIds;

				for (FString EffectId : SkillEffectIdArray)
				{
					BattleGM->AddStatusEffect(EffectId, GetOwner()->GetInstigator()->GetController(), GetOwner()->GetInstigator()->GetController());
				}

				OnSkillDuration();
			}
			else
			{
				if (CharacterMesh == NULL)
				{
					UE_LOG(LogTemp, Warning, TEXT("CharacterMesh is NULL"));
					return;
				}


				FVector SocketLocation = CharacterMesh->GetSocketLocation(SkillData.SkillSocketName);

				FVector Start = SocketLocation + UKismetMathLibrary::GreaterGreater_VectorRotator(SkillData.CastLocOffset, CharacterMesh->GetComponentRotation());

				TArray<AActor*> IgnoreActors;

				TArray<ECollisionChannel> ObjectTypes;
				ObjectTypes.Add(ECC_Pawn);

				TArray<FHitResult> OutHits;
				UStaticFunctionLibrary::MultiCollisionTraceForObject(
					GetWorld(),
					OutHits,
					SkillData.SkillCollisionType,
					Start,
					FVector::ZeroVector,
					ObjectTypes,
					IgnoreActors,
					SkillData.CollisionParam);

				

				for (FHitResult hit : OutHits)
				{
					AActor* TargetActor;
					if (UStaticFunctionLibrary::CheckTargetBySkillTargetType(TargetActor, SkillData.SkillTargetType, hit, InstigatorPawn->GetController()))
					{
						GLog->Log("Target Check");

						for (FString EffectId : SkillData.SkillEffectIds)
						{
							// Todo : GameMode :: Add Status Effect
							BattleGM->AddStatusEffect(EffectId, TargetActor->GetInstigator()->GetController(), GetOwner()->GetInstigator()->GetController());
						}
					}
				}



				OnSkillDuration();
			}
		}

	}
	*/
}

void USkillComponent::OnSkillDuration()
{
	if (HasAuthority())
	{
		SkillTime = 0.0f;
		SkillDurationTime = 0.0f;
		IsRunSkill = true;
	}
}



// ######  Server Logic  #####

void USkillComponent::Server_RunSkill_Implementation()
{
	if (HasAuthority())
	{
		GLog->Log("Run Skill");

		IsRunSkill = true;
		IsCasting = false;

		// Character Effect
		Multi_CharacterEffect();

		// Muzzle Effect
		Multi_MuzzleEffect();

		// Camera Shake
		Client_CameraShake();

		switch (SkillData.SkillDetailType)
		{
		case EGWSkillDetailType::Buff:
			ApplyBuffEffect();
			break;

		case EGWSkillDetailType::Projectile:
			// Todo : Spawn Projectile
			//GetWorld()->GetTimerManager().
			
			for (int i = 0; i < SkillData.FireCount; ++i)
			{
				FTimerHandle FireTimer;

				FTimerDelegate FuctionDelegate = FTimerDelegate::CreateUObject(this, &USkillComponent::Client_WeaponTrace, i);

				const float interval = SkillData.FireInterval * (i + 1);
				GetOwner()->GetWorldTimerManager().SetTimer(FireTimer, FuctionDelegate, interval, false);
			}

			OnSkillDuration();

			break;
		}
	}
}
bool USkillComponent::Server_RunSkill_Validate()
{
	return true;
}


void USkillComponent::Server_OnStartSkill_Implementation()
{
	if (HasAuthority())
	{
		if (CanSkill())
		{
			OnCastSkill();
		}
	}
}

bool USkillComponent::Server_OnStartSkill_Validate()
{
	return true;
}

void USkillComponent::Server_OnActiveSkill_Implementation()
{
	if (HasAuthority())
	{
		// Only Active Skill
		if (SkillData.SkillType == EGWSkillType::Active)
		{
			Server_RunSkill();
		}
	}
}

bool USkillComponent::Server_OnActiveSkill_Validate()
{
	return true;
}

/*
// Spawn Projectile
void USkillComponent::Server_Spawnprojectile_Implementation(TSubclassOf<class AProjectileBase> ProjectileClass, const FTransform& SpawnTransform, AActor* Owner, APawn* Instigator)
{
	if (ProjectileClass)
	{
		FActorSpawnParameters SpawnParam;
		SpawnParam.Instigator = Instigator;
		SpawnParam.Owner = Owner;

		//AProjectileBase* SpawnProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnTransform, SpawnParam);
		// Todo : Set Damage & SkillData
	//	if (SpawnProjectile)
	//	{
			//SpawnProjectile->SetDamage(GetSkillDamage());
			//SpawnProjectile->SetSkillData(SkillData);
	//	}
	}
}
*/
//bool USkillComponent::Server_Spawnprojectile_Validate(TSubclassOf<class AProjectileBase> ProjectileClass, const FTransform& SpawnTransform, AActor* Owner, APawn* Instigator)
//{
//	return true;
//}




// ########  Multicast Logic ###############
void USkillComponent::Multi_RunSkillAnimation_Implementation()
{
	if (HasSkillData && SkillData.ActiveAnimation)
	{
		// Todo : Play Skill Animation (Call Interface)
	}
}


void USkillComponent::Multi_CharacterEffect_Implementation()
{

}


void USkillComponent::Multi_MuzzleEffect_Implementation()
{

}




// ########  Client Logic ###############

void USkillComponent::Client_CameraShake_Implementation()
{

}



void USkillComponent::Client_SpawnSkillActor_Implementation()
{

}


void USkillComponent::Client_WeaponTrace_Implementation(int32 index)
{
	AActor* OwnerActor = GetOwner();
	APawn* InstigatorPawn = GetOwner()->GetInstigator();

	if (OwnerActor && InstigatorPawn)
	{
		FTransform SpawnTransform;
		FTransform CastTransform = GetCastTransform();

		FRotator Rot = FRotator::ZeroRotator;
		
		const int32 FireCount = SkillData.FireCount;
		const float FireAngle = SkillData.FireAngle;
		const float AngleDeg = ((FireAngle / (FireCount - 1)) * index) - (FireAngle / 2.0f);;

		FRotator ComRot = SkillData.DirectionOffset + CastTransform.GetRotation().Rotator();

		FVector AroundVector = FVector::ZeroVector;


		// Circle
		if (FireAngle < 0.f)
		{
			float RandomValue = UKismetMathLibrary::RandomFloatInRange(0.f, 0.2f);

			FVector InVec = UKismetMathLibrary::GetForwardVector(ComRot) + (UKismetMathLibrary::GetUpVector(ComRot) * RandomValue);
			FVector Axis = UKismetMathLibrary::GetForwardVector(ComRot);

			AroundVector = UKismetMathLibrary::RotateAngleAxis(InVec, AngleDeg, Axis);
		}
		// Line
		else
		{
			FVector InVec = UKismetMathLibrary::GetForwardVector(ComRot);
			FVector Axis = UKismetMathLibrary::GetUpVector(ComRot);

			AroundVector = UKismetMathLibrary::RotateAngleAxis(InVec, AngleDeg, Axis);
		}

		//UKismetMathLibrary::MakeRotFromX(AroundVector);

		Rot = UKismetMathLibrary::MakeRotFromX(AroundVector); //UKismetMathLibrary::Conv_VectorToRotator(AroundVector);// .Rotation();


		SpawnTransform.SetLocation(CastTransform.GetLocation());
		SpawnTransform.SetRotation(FQuat(Rot));
		SpawnTransform.SetScale3D(FVector(1.f, 1.f, 1.f));
		

	//	Server_Spawnprojectile(SkillData.ProjectileClass, SpawnTransform, OwnerActor, InstigatorPawn);
	}

	
}









