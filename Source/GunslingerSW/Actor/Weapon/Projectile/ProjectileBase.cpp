// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "Engine/World.h"
//#include "StaticFunctionLibrary.h"

// Interface
#include "Actor/Skill/SkillInterface.h"

// Debug header
#include "DrawDebugHelpers.h"

// Sets default values
AProjectileBase::AProjectileBase() :
	fTotalTime(0.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bReplicateMovement = true;


	// Projectile Collision
	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	RootComponent = ProjectileCollision;
	RootComponent->Rename(TEXT("ProjectileCollision"));
	ProjectileCollision->SetSphereRadius(10.0f);


	// ProjectilePS
	ProjectilePS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectilePS"));
	ProjectilePS->SetupAttachment(ProjectileCollision);

	// IgnoreCheckCollision
	IgnoreCheckCollision = CreateDefaultSubobject<USphereComponent>(TEXT("IgnoreCheckCollision"));
	IgnoreCheckCollision->SetupAttachment(ProjectileCollision);

}

void AProjectileBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Value is already updated locally, skip in replication step
	//DOREPLIFETIME_CONDITION(AProjectileBase, bIsJumping, COND_SkipOwner);

	//// Replicate to every client, no special condition required
	DOREPLIFETIME(AProjectileBase, fGravity);

	DOREPLIFETIME(AProjectileBase, SearchTargetActor);

	DOREPLIFETIME(AProjectileBase, HomingTarget);

	DOREPLIFETIME(AProjectileBase, IgnoreActors);

	DOREPLIFETIME_CONDITION(AProjectileBase, bIsTargetParbolic, COND_SkipOwner);
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	InitLocation = GetActorLocation();

	PrevLocation = InitLocation;

	// Projectile Ignore Move
	ProjectileCollision->IgnoreActorWhenMoving(GetOwner(), true);

	InitProjectile();

}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovement(DeltaTime);

	UpdatePivot(DeltaTime);

	if (bIsHoming)
	{
		/*
		if (UStaticFunctionLibrary::IsValid(SearchTargetActor))
		{
			if (SearchTargetActor->GetClass()->ImplementsInterface(USkillInterface::StaticClass()))
			{
				if (!ISkillInterface::Execute_GetIsDead(SearchTargetActor))
				{
					UpdateTargetRotate(DeltaTime);
				}
				else
				{
					bIsHoming = false;
				}
			}
		}
		*/
	}
}

void AProjectileBase::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	//GLog->Log("Projectile Hit");

	// Todo : Projectil Hit Process

	switch (ProjectileInfo.HitAction)
	{
	case EGWProjectileHitAction::Explosion :
		ExplosionAction(Hit);
		break;

	case EGWProjectileHitAction::Bounce :
		BounceAction(HitNormal);
		break;

	case EGWProjectileHitAction::Attach :
		AttachAction();
		break;
	}


}

bool AProjectileBase::CanExplosion() const
{
	return !IsExplosioned;
}

bool AProjectileBase::CanMove() const
{
	return !IsMoveStop;
}


float AProjectileBase::GetProjectileDamage() const
{
	return fDamage * fDamageRate;
}

FVector AProjectileBase::CalculatorReflect(const FVector& VelocityVector, const FVector& NormalVector) const
{
	const float Length = UKismetMathLibrary::VSize(VelocityVector);

	const FVector normal = UKismetMathLibrary::Normal(VelocityVector);

	

	FVector NewVelocity = (normal - (UKismetMathLibrary::Dot_VectorVector(normal, NormalVector) * 2.0f * NormalVector)) * Length;

	return UKismetMathLibrary::SelectVector(NewVelocity, FVector::ZeroVector, Length > 1000.f);
}

// 나중에 스태틱 라이브러리로 이동
float AProjectileBase::CalculateRadiusDamage(float BaseDamage, FVector Zero, float Radius)
{
	return (1.0f - (UKismetMathLibrary::VSize(Zero - GetActorLocation()) / Radius)) * BaseDamage;
}


/* Explosion Action */
void AProjectileBase::ExplosionAction(const FHitResult& HitResult)
{
	if (CanExplosion())
	{
		ApplySkill();
		ApplyDamage(HitResult);
	}

}


/* Bounce Action */
void AProjectileBase::BounceAction(const FVector& Normal)
{
	InitLocation = GetActorLocation();

	//fCurrentSpeed = fCurrentSpeed * ProjectileInfo.fBouncines;

	fTotalTime = 0.0f;

	Velocity = CalculatorReflect(Velocity, Normal) * ProjectileInfo.Bouncines;

	bIsTargetParbolic = false;
}

/* Attach Action */
void AProjectileBase::AttachAction()
{
	fGravity = 0.0f;
	IsMoveStop = true;
}

float AProjectileBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	// Todo : Damage Logic

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);;
}



bool AProjectileBase::InitProjectile()
{
	// Todo : Init Projectile Info

	Velocity = GetActorRotation().Vector() * ProjectileInfo.InitialSpeed;
	fGravity = ProjectileInfo.GravityValue;
	fDamageRate = ProjectileInfo.DamageRate;

	//fCurrentSpeed = ProjectileInfo.fInitialSpeed;

	if (ProjectileInfo.ArroundSearch)
	{
		if (Role == ROLE_Authority)
		{
			SearchStart();
		}
	}

	if (ProjectileInfo.SelfExplosion)
	{
		FTimerHandle SelfExplosionTimerHandle;
		GetWorldTimerManager().SetTimer(SelfExplosionTimerHandle, this, &AProjectileBase::SelfExplosion, ProjectileInfo.Duration, false);
	}
	else
	{
		SetLifeSpan(ProjectileInfo.Duration);
	}

	return true;
}

bool AProjectileBase::InitParabolicMove(const FVector& TargetLocation, const float& MaxTime, const float& MaxHeight)
{
	const float EndHeight = TargetLocation.Z - InitLocation.Z;
	const float Height = MaxHeight - InitLocation.Z;

	fGravity = (Height * 2.0f) / FMath::Square(MaxTime);

	const float SpeedZ = FMath::Sqrt(2.0f * fGravity * Height);
	const float EndTime = (SpeedZ * 2.0f) + FMath::Sqrt((FMath::Square(SpeedZ * -2.0f) - (4.0f * fGravity * (EndHeight * 2.0f))) / (fGravity * 2.0f));

	const float SpeedX = InitLocation.X - TargetLocation.X * -1.f / EndTime;
	const float SpeedY = InitLocation.Y - TargetLocation.Y * -1.f / EndTime;

	Velocity = FVector(SpeedX, SpeedY, SpeedZ);

	bIsTargetParbolic = true;


	if (Role == ROLE_Authority)
	{
		Multi_SetIsTargetParabolic(true);
	}


	return true;
}


bool AProjectileBase::SetSkillData(struct FGWSkillInfo SkillInfo)
{
	SkillData = SkillInfo;

	bHasSkill = true;

	// Todo : Load Skill Actor Data

	if (bHasSkillActor)
	{
		//SkillData = 
	}


	return true;
}

bool AProjectileBase::SetDamage(float Damage)
{
	fDamage = Damage;
	return true;
}




void AProjectileBase::Multi_SetIsTargetParabolic_Implementation(bool IsTargetParabolic)
{
	bIsTargetParbolic = IsTargetParabolic;
}



void AProjectileBase::UpdateMovement(float delta)
{
	if (!CanMove()) return;

	fTotalTime += delta;

	if (bIsTargetParbolic)
	{
		ProjectileMovement(delta);
	}
	else
	{
		ProjectileMovement2(delta);
	}
}



void AProjectileBase::ProjectileMovement(float delta)
{
	FVector Location;
	Location.X = Velocity.X * fTotalTime + InitLocation.X;
	Location.Y = Velocity.Y * fTotalTime + InitLocation.Y;
	Location.Z = Velocity.Z * fTotalTime + InitLocation.Z - (0.5f * fGravity * (fTotalTime * fTotalTime));	// Apply Gravity 

	const FVector NewLocation = FMath::VInterpTo(PrevLocation, Location, delta, 0.0f);

	const FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);

	SetActorLocationAndRotation(NewLocation, NewRotator, true);

	PrevLocation = GetActorLocation();
}


void AProjectileBase::ProjectileMovement2(float delta)
{
	Velocity = Velocity + (FVector(0, 0, -fGravity) * delta);

	FVector Location = GetActorLocation() + (Velocity * delta);

	const FVector NewLocation = FMath::VInterpTo(PrevLocation, Location, delta, 0.0f);

	const FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);

	SetActorLocationAndRotation(NewLocation, NewRotator, true);

	PrevLocation = GetActorLocation();
}


void AProjectileBase::UpdatePivot(float delta)
{
	if (ProjectilePS)
	{
		const FRotator OldRot = ProjectilePS->RelativeRotation;
		const FRotator DeltaRot = ProjectileInfo.RotateMovement.RotateRate * delta;

		const FRotator NewRot = UKismetMathLibrary::ComposeRotators(OldRot, DeltaRot);


		
		if (UKismetMathLibrary::VSize(ProjectileInfo.RotateMovement.Pivot) > 0)
		{
			const FVector OldPivot = UKismetMathLibrary::GreaterGreater_VectorRotator(ProjectileInfo.RotateMovement.Pivot, OldRot);
			const FVector NewPivot = UKismetMathLibrary::GreaterGreater_VectorRotator(ProjectileInfo.RotateMovement.Pivot, NewRot);

			ProjectilePS->AddLocalOffset(OldPivot - NewPivot, true);
		}

		ProjectilePS->SetRelativeRotation(NewRot);

	}
}

void AProjectileBase::UpdateTargetRotate(float delta)
{
	if (HomingTarget)
	{
		const float Lenght = UKismetMathLibrary::VSize(Velocity);
		
		const FRotator FindLookRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HomingTarget->GetComponentLocation());

		const FRotator InterpRot = UKismetMathLibrary::RInterpTo(GetActorRotation(), FindLookRot, delta, ProjectileInfo.HomingTime);

		Velocity = UKismetMathLibrary::GetForwardVector(InterpRot) * Lenght;		
	}
}


void AProjectileBase::ApplyDamage(const FHitResult& HitResult)
{
	if (ProjectileType == EGWProjectileType::Normal)
	{
		const float Damage = GetProjectileDamage();
		UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), GetProjectileDamage(), HitResult.ImpactNormal, HitResult, GetInstigatorController(), this, NULL);
	}
	else if (ProjectileType == EGWProjectileType::Explosion)
	{
		ApplyRadialDamage();
	}

	Multi_ExplosionFX();
	IsExplosioned = true;
	Destroy();
}

void AProjectileBase::ApplyRadialDamage()
{
	// Todo : Radial Damage Process

	TArray<FHitResult> OutHits;

	/*
	UStaticFunctionLibrary::MultiSphereTraceByChannel(
		GetWorld(),
		OutHits,
		GetActorLocation(),
		GetActorLocation(),
		ProjectileInfo.ExplosionRadius,
		ECC_Visibility,
		false,
		IgnoreActors,
		true);

	TArray<FHitResult> CheckResult = CheckTargetHits(OutHits);

	const float BaseDamage = GetProjectileDamage();
	const float ExplosionRadius = ProjectileInfo.ExplosionRadius;

	for (FHitResult hit : CheckResult)
	{
		// Todo : Check Target Enemy ? Ally?
		AActor* TargetActor = NULL;
		if (!UStaticFunctionLibrary::CheckTargetBySkillTargetType(TargetActor, ProjectileInfo.SearchTarget, hit, GetInstigatorController()))
		{
			TargetActor = hit.GetActor();
		}

		float Damage = ProjectileInfo.DoFullDamage ? BaseDamage : CalculateRadiusDamage(BaseDamage, hit.ImpactPoint, ExplosionRadius);
		if (TargetActor)
		{
			GLog->Log(TargetActor->GetName());
			UGameplayStatics::ApplyPointDamage(TargetActor, Damage, hit.ImpactNormal, hit, GetInstigatorController(), this, NULL);
		}
	}
			*/
}

TArray<FHitResult> AProjectileBase::CheckTargetHits(const TArray<FHitResult>& HitResults)
{
	TArray<FHitResult> NewHitResults;
	TArray<AActor*> CheckActors;

	for (FHitResult hit : HitResults)
	{
		if (hit.GetActor())
		{
			int32 FindResult = CheckActors.Find(hit.GetActor());
			if(FindResult == -1)
			{
				CheckActors.Add(hit.GetActor());
				NewHitResults.Add(hit);
			}
			else
			{
				const float v1 = UKismetMathLibrary::VSize(GetActorLocation() - hit.ImpactPoint);
				const float v2 = UKismetMathLibrary::VSize(GetActorLocation() - NewHitResults[FindResult].ImpactPoint);

				if (v1 < v2)
				{
					NewHitResults[FindResult] = hit;
				}
			}
		}
	}


	return NewHitResults;
}


void AProjectileBase::OnExplosionFX()
{
	// Todo : Spawn Explosion Effect
	if (PS_ExplosionFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			PS_ExplosionFX,
			GetActorLocation(),
			GetActorRotation(),
			true);
	}


	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			ExplosionSound,
			GetActorLocation());
	}
}


void AProjectileBase::Multi_ExplosionFX_Implementation()
{
	
	OnExplosionFX();

	GetWorldTimerManager().ClearTimer(SearchTimerHandle);

}


void AProjectileBase::SelfExplosion()
{
	if (Role == ROLE_Authority)
	{
		if (CanExplosion())
		{
			ApplySkill();
			FHitResult HitResult;
			ApplyDamage(HitResult);
		}
	}
}


void AProjectileBase::SearchStart()
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AProjectileBase::OnSearch, ProjectileInfo.HomingDelayTime, false);
}

void AProjectileBase::OnSearch()
{
	GetWorldTimerManager().SetTimer(SearchTimerHandle, this, &AProjectileBase::SearchTarget, ProjectileInfo.SearchInterval, true);
}

void AProjectileBase::SearchTarget()
{
	TArray<FHitResult> OutHits;


	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = false;
	QueryParams.AddIgnoredActor(this);

	FCollisionObjectQueryParams ObjectParam;
	ObjectParam.AddObjectTypesToQuery(ECC_Pawn);


	// Multi Sphere Trace
	bool bHit = GetWorld()->SweepMultiByObjectType(
		OutHits,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ObjectParam,
		FCollisionShape::MakeSphere(ProjectileInfo.SearchRadius),
		QueryParams);


	// Debug
	DrawDebugSphere(GetWorld(), GetActorLocation(), ProjectileInfo.SearchRadius, 10.f, FColor::Green, true, 1.0f);

	if (bHit)
	{
		for (auto hit : OutHits)
		{
			if (hit.bBlockingHit)
			{
				SearchTargetActor = hit.GetActor();
				SearchEnd(hit);
				break;
			}
		}
	}
}



void AProjectileBase::SearchEnd(const FHitResult& HitResult)
{
	if (SearchTargetActor)
	{
		GetWorldTimerManager().ClearTimer(SearchTimerHandle);

		if (Role == ROLE_Authority)
		{
			switch (ProjectileInfo.SearchAndAction)
			{
			case EGWSearchAndAction::Explosion :

				if (CanExplosion())
				{
					ApplySkill();
					ApplyDamage(HitResult);
				}
				break;

			case EGWSearchAndAction::Homing :

				if (HomingTarget == NULL)
				{
					USceneComponent* HomingComp = NewObject<USceneComponent>(SearchTargetActor, USceneComponent::StaticClass());
					//HomingComp->RegisterComponentWithWorld(GetWorld());
					//HomingComp->RegisterComponent();

					FTransform transform;

					//SearchTargetActor->AddComponent(TEXT("HomingTarget"), true, transform, HomingComp);

					FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
					//HomingComp->SetupAttachment(HitResult.GetComponent());
					HomingComp->AttachToComponent(HitResult.GetComponent(), AttachRule);

					HomingTarget = HomingComp;

					SetHoming(HomingTarget);
				}

				break;

			default:
				break;
			}
		}
	}
}


void AProjectileBase::SetHoming(USceneComponent* Target)
{
	GLog->Log("Set Homing");
	bIsHoming = true;

	Velocity = UKismetMathLibrary::Normal(Velocity) * ProjectileInfo.HomingAcceleration;

}