// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponBase.h"
#include "Net/UnrealNetwork.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"


//#include "CharacterBase.h"
#include "Projectile/ProjectileBase.h"

#include "Actor/Skill/SkillComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

//#include "StaticFunctionLibrary.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;


	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Root
	RootComponent = WeaponMesh;



	SkillComp = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));
	if (SkillComp)
	{
		// ...
	}




	// 테스트
	WeaponInfo.TriggerType = EGWWeaponTriggerType::Auto;
	WeaponInfo.FireInterval = 0.5f;
	WeaponInfo.TraceType = EGWTraceType::Visible;
	WeaponInfo.MagazineCapacity = 25;
	WeaponInfo.WeaponRange = 500.0f;

	WeaponInfo.MinDamage = 10.0f;
	WeaponInfo.MaxDamage = 30.0f;


	CurrentAmmoInClip = WeaponInfo.MagazineCapacity;

	fSphereTraceRadius = 10.0f;

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();


	if (Role == ROLE_Authority)
	{
		if (SkillComp)
		{
			SkillComp->InitSKillData(SkillInfo);
		}
	}
}


void AWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeaponBase, CurrentAmmoInClip);
}

bool AWeaponBase::InitWeaponInfo()
{
	return true;
}

FVector AWeaponBase::GetTraceStartLocation() const
{
	FVector StartLocation = FVector::ZeroVector;

	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (PlayerCameraManager)
	{
		const FVector CamLoc = PlayerCameraManager->GetCameraLocation();
		const FRotator CamRot = PlayerCameraManager->GetCameraRotation();

		APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		/*
		ACharacterBase* Character = Cast<ACharacterBase>(Pawn);
		if (Character)
		{
			USpringArmComponent* CameraBoom = Character->GetCameraBoom();
			UCameraComponent* FollowCamera = Character->GetFollowCamera();

			FVector CameraBoomLocation = CameraBoom->GetComponentTransform().GetLocation();
			FVector FollowCameraLocation = FollowCamera->GetComponentTransform().GetLocation();

			const float Distance = FVector::Distance(CameraBoomLocation, FollowCameraLocation);

			StartLocation = CamLoc + (CamRot.Vector() * Distance);
		}
		else
		{
			StartLocation = CamLoc;
		}

		*/
	}
	
	return StartLocation;
}


float AWeaponBase::CalcDamage() const
{
	const float fMInDamage = WeaponInfo.MinDamage;
	const float fMaxDamage = WeaponInfo.MaxDamage;

	return FMath::RandRange(fMInDamage, fMaxDamage) * (1.0f + fAddSkillDamageRate);
}

bool AWeaponBase::CalcDamageByDefence(float& Damage, const FHitResult HitResult) const
{
	// Todo : 
	return true;
}

bool AWeaponBase::CalcDamageByPhysical(float& Damage, const FHitResult HitResult) const
{
	// Todo : 
	return true;
}

bool AWeaponBase::CalcDamageByDistance(float& Damage, const FHitResult HitResult) const
{
	// Todo : 
	return true;
}




void AWeaponBase::OnFire(bool bIsFire)
{
	if (bIsFire)
	{
		// 인터발 체크
		if (!CheckFireInterval()) return;

		switch (WeaponInfo.TriggerType)
		{
		case EGWWeaponTriggerType::SemiAuto :
			OnFireBase();
			break;

		case EGWWeaponTriggerType::Auto :
			AutoMode();
			break;

		case EGWWeaponTriggerType::Burst :
			BurstMode();
			break;

		case EGWWeaponTriggerType::AutoSpool :
			AutoSpoolMode();
			break;

		case EGWWeaponTriggerType::Charge :
			ChargeMode();
			break;

		case EGWWeaponTriggerType::BurstCharge :
			BurstChargeMode();
			break;

		case EGWWeaponTriggerType::Hold :
			HoldMode();
			break;

		case EGWWeaponTriggerType::Buckshot :
			BuckshotLogic();
			break;
		}
	}
	else
	{
		OnStopFire();
	}
}

void AWeaponBase::OnStopFire()
{
	GLog->Log("Todo : Force Stop Fire Logic");

	//GetWorldTimerManager().ClearTimer(FireTimerHandle);
	GetWorldTimerManager().ClearAllTimersForObject(this);

	HoldFireDelegate.Broadcast(false);

	// 홀드 파이어 바인딩해줘야함.
	HoldFireDelegate.Broadcast(false);
	//HoldFireDelegate.ExecuteIfBound(false);
}

void AWeaponBase::FireTimer()
{

}

bool AWeaponBase::CheckFireInterval()
{
	float TimeSeconds = UGameplayStatics::GetTimeSeconds(GetWorld());
	if (TimeSeconds >= WeaponInfo.FireInterval + LastFireTime)
	{
		LastFireTime = TimeSeconds;
		return true;
	}

	return false;
}

bool AWeaponBase::CanFire()
{
	return (CurrentAmmoInClip > 0);
}

bool AWeaponBase::CanReload()
{
	return true;
}

void AWeaponBase::OnReload()
{
	if (!CanReload()) return;

	AddAmmo(WeaponInfo.MagazineCapacity);

	Server_Reload();
}

void AWeaponBase::AddAmmo(const int Ammo)
{
	CurrentAmmoInClip = FMath::Clamp(CurrentAmmoInClip + Ammo, 0, WeaponInfo.MagazineCapacity);
}

void AWeaponBase::Server_Reload_Implementation()
{
	if (Role == ROLE_Authority)
	{
		GLog->Log("Todo : DecrementAmmo");
		AddAmmo(WeaponInfo.MagazineCapacity);
	}
}

bool AWeaponBase::Server_Reload_Validate()
{
	return true;
}

void AWeaponBase::DecrementAmmo()
{
	GLog->Log("Todo : DecrementAmmo");

	CurrentAmmoInClip = (CurrentAmmoInClip - 1 == 0 ? 0 : CurrentAmmoInClip - 1);
}

void AWeaponBase::Server_DecrementAmmo_Implementation()
{
	if (Role == ROLE_Authority)
		DecrementAmmo();
}

bool AWeaponBase::Server_DecrementAmmo_Validate()
{
	return true;
}

void AWeaponBase::OnFireBase()
{
	FireBaseLogic();

	// 홀드 파이어 바인딩해줘야함.
	HoldFireDelegate.Broadcast(true);
	//HoldFireDelegate.ExecuteIfBound(true);
}

void AWeaponBase::FireBaseLogic()
{
	DecrementAmmo();

	Server_DecrementAmmo();


	TArray<FHitResult> HitResults;
	bool bIsHit = false;
	
	const FVector FireLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);
	FVector EndTrace;

	WeaponSphereTrace(HitResults, bIsHit, EndTrace);

	for (FHitResult HitResult : HitResults)
	{
		// Todo : Single Fire Weapon FX

		//HitResult.bBlockingHit
	}


	FireBulletTrailFX(HitResults, EndTrace);


	if (!bIsHit)
	{
		HitResults.Add(FHitResult());
	}

	Server_SetFire(HitResults, bIsHit, FireLocation, EndTrace);
	Server_FireBullerTrailFX(HitResults, EndTrace);
}


void AWeaponBase::BuckshotLogic()
{
	DecrementAmmo();

	Server_DecrementAmmo();

	float AngleDeg = 0.0f;

	for (int i = 1; i < WeaponInfo.BuckshotCount; ++i)
	{
		AngleDeg += 360.0f / WeaponInfo.BuckshotCount;

		TArray<FHitResult> OutHits;
		
		FVector TraceStartLocation = GetTraceStartLocation();
		
		FVector CamLoc;
		FRotator CamRot;

		APlayerController* PlayerController = Cast<APlayerController>(GetInstigatorController());
		if (PlayerController)
			PlayerController->GetPlayerViewPoint(CamLoc, CamRot);


		const FVector ForwardVec = UKismetMathLibrary::GetForwardVector(CamRot);
		const FVector UpVec = UKismetMathLibrary::GetUpVector(CamRot);

		float RandomSpread = FMath::RandRange(0.f, WeaponInfo.MaxSpread);

		FVector RotateVector = UKismetMathLibrary::RotateAngleAxis(ForwardVec + (UpVec * RandomSpread), AngleDeg, ForwardVec);


		const FVector Direction = CamRot.Vector();
		const FVector TraceEnd = TraceStartLocation + (RotateVector * WeaponInfo.WeaponRange);

		TraceEndLocation = TraceEnd;


		TArray<AActor*> IgnoreActors;
		IgnoreActors.Add(this);
		IgnoreActors.Add(GetInstigator());
		/*bool  IsHit = UStaticFunctionLibrary::MultiSphereTraceByChannel(
			GetWorld(), 
			OutHits, 
			TraceStartLocation, 
			TraceEnd, 
			fSphereTraceRadius, 
			ECC_Visibility, 
			true, 
			IgnoreActors);
			

		if (IsHit == true)
		{
			for (auto Hit : OutHits)
			{
				if (Hit.bBlockingHit)
				{
					// Todo : Single Fire FX
				}
			}

			Server_SetFire(OutHits, IsHit, TraceStartLocation, TraceEnd);

			FireBulletTrailFX(OutHits, TraceEnd);

			Server_FireBullerTrailFX(OutHits, TraceEnd);
		}
		else
		{
			TArray<FHitResult> EmptyArray;

			EmptyArray.Add(FHitResult());

			Server_SetFire(EmptyArray, IsHit, TraceStartLocation, TraceEnd);

			FireBulletTrailFX(EmptyArray, TraceEnd);

			Server_FireBullerTrailFX(EmptyArray, TraceEnd);
		}

		*/


	}
}




void AWeaponBase::ShootInfo(FHitResult& OutResult, bool& OutHit, float& OutDamage, FHitResult HitResult, bool bHit, FVector FireLocation, FVector EndTrace)
{
	
	if (WeaponInfo.FireType == EGWWeaponAttackType::HitScan)
	{
		OutResult = HitResult;
		OutHit = bHit;

		// Todo : Hit Check

		float BaseDamage = CalcDamage();
		CalcDamageByDefence(BaseDamage, HitResult);
		CalcDamageByPhysical(BaseDamage, HitResult);
		CalcDamageByDistance(BaseDamage, HitResult);

		GLog->Log("Damage : " + FString::SanitizeFloat(BaseDamage));


		if (HitResult.GetActor() && bHit)
		{
			FDamageEvent DamageEvent;
			OutDamage = HitResult.Actor->TakeDamage(BaseDamage, DamageEvent, Instigator->GetController(), this);
		}
	}
	else if (WeaponInfo.FireType == EGWWeaponAttackType::Projectile)
	{
		// Todo : Spawn Projectile
		OutDamage = 0.f;
		OutResult = FHitResult();
		OutHit = false;


		SpawnProjectile(HitResult, bHit, FireLocation, EndTrace);

	}

}

void AWeaponBase::SubAttack(float Damage, FHitResult HitResult, bool bIsHit)
{
	// Todo : SubAttack Logic
}

void AWeaponBase::BindAttack(FHitResult HitResult, bool bIsHit)
{
	// Todo : BindAttack Logic
}



void AWeaponBase::OnCameraShake()
{
	GLog->Log("Todo : Camera Shake");
}



void AWeaponBase::Server_MuzzleFXAndSound_Implementation()
{

}

bool AWeaponBase::Server_MuzzleFXAndSound_Validate()
{
	return true;
}

void AWeaponBase::SpawnMuzzleFXAndSound()
{
	GLog->Log("Todo : Spawn Muzzle Effect and Sound");
}


void AWeaponBase::IncreseSpread(float IncreseSpreadAmound)
{
	GLog->Log("Todo : Increase Weapon Spread");
}

void AWeaponBase::WeaponSphereTrace(TArray<FHitResult>& HitResults, bool& bIsHit, FVector& EndTrace)
{
	GLog->Log("Todo : Weapon Trace Return HitResult array");

	TArray<FHitResult> OutHits;

	FVector TraceStartLocation = GetTraceStartLocation();


	FVector CamLoc;
	FRotator CamRot;

	APlayerController* PlayerController = Cast<APlayerController>(GetInstigatorController());
	if(PlayerController)
		PlayerController->GetPlayerViewPoint(CamLoc, CamRot);


	const FVector Direction = CamRot.Vector();
	const FVector TraceEnd = TraceStartLocation + (Direction * WeaponInfo.WeaponRange);

	TraceEndLocation = TraceEnd;


	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	IgnoreActors.Add(GetInstigator());
	/*
	bool  IsHit = UStaticFunctionLibrary::MultiSphereTraceByChannel(
		GetWorld(),
		OutHits,
		TraceStartLocation,
		TraceEndLocation,
		fSphereTraceRadius,
		ECC_Visibility,
		true,
		IgnoreActors);
	
	*/
	bIsHit = (OutHits.Num() > 0 ? true : false);

	// 중복된 Actor 제외
	TArray<AActor*> CheckActors;
	TArray<FHitResult> Results;

	for (FHitResult Hit : OutHits)
	{
		AActor* actor = Hit.GetActor();
		if (actor)
		{
			if (!CheckActors.Contains(actor))
			{
				CheckActors.Add(actor);
				Results.Add(Hit);
			}
		}
	}

	// HitResult가 1보다 크고 트레이스타입이 Visible이면 맨 앞에꺼 한개만 
	if (Results.Num() > 1 && WeaponInfo.TraceType == EGWTraceType::Visible)
	{
		HitResults.Add(Results[0]);
	}
	else
	{
		HitResults = Results;
	}

	EndTrace = TraceEndLocation;

}

void AWeaponBase::Server_SetFire_Implementation(const TArray<FHitResult>& HitResults, const bool bIsHit, const FVector FireLocation, const FVector EndTrace)
{
	if (Role == ROLE_Authority)
	{
		//TMap<FHitResult, bool> HitResultMap;


		for (FHitResult Hit : HitResults)
		{
			FHitResult OutResult;
			bool OutHit;
			float OutDamage;


			// Default Attack
			ShootInfo(OutResult, OutHit, OutDamage, Hit, bIsHit, FireLocation, EndTrace);

			//HitResultMap.Add(OutResult, OutHit);


			// Sub Attack
			SubAttack(OutDamage, OutResult, OutHit);

			// Bind Attack
			BindAttack(OutResult, OutHit);

		}

		// Spawn Impact Particle
		if (WeaponInfo.FireType == EGWWeaponAttackType::HitScan)
		{
			Multi_FireImpactFX(HitResults);
		}

		/*
		if (ACharacterBase* Character = Cast<ACharacterBase>(GetInstigator()))
		{
			Character->OnPlayAttackAnim();
		}
		*/
	}

}

bool AWeaponBase::Server_SetFire_Validate(const TArray<FHitResult>& HitResults, const bool bIsHit, const FVector FireLocation, const FVector EndTrace)
{
	return true;
}



void AWeaponBase::Server_FireBullerTrailFX_Implementation(const TArray<FHitResult>& HitResults, FVector TargetLocation)
{

}

bool AWeaponBase::Server_FireBullerTrailFX_Validate(const TArray<FHitResult>& HitResults, FVector TargetLocation)
{
	return true;
}


void AWeaponBase::FireBulletTrailFX(const TArray<FHitResult> HitResults, FVector TargetLocation)
{
	GLog->Log("Todo : Spawn Bullet Trail Effect");
}



void AWeaponBase::Multi_FireImpactFX_Implementation(const TArray<FHitResult>& HitResults)
{
	GLog->Log("Todo : Spawn Bullet Impact Effect");
	//if (Role != ROLE_Authority)
	{
		for (FHitResult Hit : HitResults)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(), 
				PS_ImpactFX,
				Hit.ImpactPoint, 
				Hit.ImpactNormal.Rotation(), 
				true);
		}
	}
	
}

bool AWeaponBase::Multi_FireImpactFX_Validate(const TArray<FHitResult>& HitResults)
{
	return true;
}



void AWeaponBase::SpawnProjectile(const FHitResult& HitResult, const bool& bHit, const FVector& StartLocation, const FVector& EndTrace)
{
	// Server 
	if (Role == ROLE_Authority)
	{
		GLog->Log("SpawnProjectile");
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Instigator = GetInstigator();
		SpawnInfo.Owner = GetInstigator();

		const FVector End = bHit ? HitResult.ImpactPoint : EndTrace;

		const FRotator Rot = UKismetMathLibrary::FindLookAtRotation(StartLocation, End);

		//AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(WeaponInfo.ProjectileBaseClass, StartLocation, Rot, SpawnInfo);
		//Projectile->SetDamage(CalcDamage());
	}

}



void AWeaponBase::OnWeaponSkill()
{
	if (SkillComp)
	{
		SkillComp->Server_OnStartSkill();
	}
}


// ##############################################
// ############### [ Fire Mode ] ################
// ##############################################
void AWeaponBase::AutoMode()
{
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AWeaponBase::OnFireBase, WeaponInfo.FireInterval, true, 0.0f);
}


void AWeaponBase::BurstMode()
{
	for (int i = 0; i < WeaponInfo.TriggerCount; ++ i)
	{
		FTimerHandle FireTimer;
		const float interval = WeaponInfo.TriggerInterval * i;
		GetWorldTimerManager().SetTimer(FireTimer, this, &AWeaponBase::OnFireBase, interval, false);
	}
	
}


void AWeaponBase::AutoSpoolMode()
{
	FLatentActionInfo ActionInfo;
	ActionInfo.CallbackTarget = this;
	ActionInfo.ExecutionFunction = "AutoMode"; // Call function must be BlueprintCallable!
	ActionInfo.UUID = 123;
	ActionInfo.Linkage = 0;
	
	UKismetSystemLibrary::RetriggerableDelay(this, WeaponInfo.SpoolUpTime, ActionInfo);

}



void AWeaponBase::ChargeMode()
{
	// 한발?
	FLatentActionInfo ActionInfo;
	ActionInfo.CallbackTarget = this;
	ActionInfo.ExecutionFunction = "AutoMode"; // Call function must be BlueprintCallable!
	ActionInfo.UUID = 123;
	ActionInfo.Linkage = 0;

	UKismetSystemLibrary::RetriggerableDelay(this, WeaponInfo.ChargeTime, ActionInfo);
}


void AWeaponBase::BurstChargeMode()
{
	FLatentActionInfo ActionInfo;
	ActionInfo.CallbackTarget = this;
	ActionInfo.ExecutionFunction = "BurstMode"; // Call function must be BlueprintCallable!
	ActionInfo.UUID = 123;
	ActionInfo.Linkage = 0;

	UKismetSystemLibrary::RetriggerableDelay(this, WeaponInfo.ChargeTime, ActionInfo);
}


void AWeaponBase::HoldMode()
{
	AutoMode();
}








