// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


// Data
#include "Data/GP2DataStructTypes.h"
#include "Data/SkillDataType.h"
#include "Data/ProjectileDataType.h"


#include "ProjectileBase.generated.h"




UCLASS()
class GUNSLINGERSW_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	// Take Damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent*	ProjectileCollision;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ProjectilePS;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent*	IgnoreCheckCollision;


	// Projectile Struct Info
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FGWProjectileInfo			ProjectileInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGWProjectileType				ProjectileType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName						ProjectileTableId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Effect")
	class UParticleSystem*		PS_ExplosionFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Sound")
	class USoundCue*			ExplosionSound;


	// Projectile Struct Info
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FGWSkillInfo			SkillData;

	bool					bHasSkill;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FGWSkillActorInfo		SkillActorData;

	bool					bHasSkillActor;


	float			fDamage;

	float			fDamageRate;


	float			fTotalTime;

	bool			IsMoveStop;

	bool			IsExplosioned;

	FVector			InitLocation;

	FVector			PrevLocation;

	FVector			Velocity;

	//float			fCurrentSpeed;

	UPROPERTY(Transient, Replicated)
	float			fGravity;

	// Target Parabolic Move?
	UPROPERTY(Transient, Replicated)
	bool			bIsTargetParbolic;

	// IsHoming?
	UPROPERTY(Transient, Replicated)
	bool			bIsHoming;

	UPROPERTY(Transient, Replicated)
	AActor*					SearchTargetActor;

	UPROPERTY(Transient, Replicated)
	USceneComponent*		HomingTarget;


	UPROPERTY(Transient, Replicated)
	TArray<AActor*>			IgnoreActors;


	FTimerHandle	SearchTimerHandle;

public:

	bool InitProjectile();

	bool InitParabolicMove(const FVector& TargetLocation, const float& MaxTime, const float& MaxHeight);

	bool SetSkillData(struct FGWSkillInfo SkillInfo);

	bool SetDamage(float Damage);


	void UpdateMovement(float delta);

	void ProjectileMovement(float delta);

	void ProjectileMovement2(float delta);


	void UpdatePivot(float delta);

	void UpdateTargetRotate(float delta);


	// Can?
	bool CanExplosion() const;

	bool CanMove() const;


	/* Get projectile Damage */
	float GetProjectileDamage() const;


	FVector CalculatorReflect(const FVector& VelocityVector, const FVector& NormalVector) const;

	float CalculateRadiusDamage(float BaseDamage, FVector Zero, float Radius);


	void ApplySkill() {};

	void ApplyDamage(const FHitResult& HitResult);

	void ApplyRadialDamage();


	TArray<FHitResult> CheckTargetHits(const TArray<FHitResult>& HitResults);


	void SearchTarget();

	void SearchStart();

	void SearchEnd(const FHitResult& HitResult);

	void OnSearch();

	void SelfExplosion();

	void SetHoming(USceneComponent* Target);

	/* Explosion Action */
	void ExplosionAction(const FHitResult& HitResult);


	/* Bounce Action */
	void BounceAction(const FVector& Normal);

	/* Attach Action */
	void AttachAction();



	void OnExplosionFX();

	UFUNCTION(Reliable, NetMulticast, BlueprintCallable)
	void Multi_ExplosionFX();
	void Multi_ExplosionFX_Implementation();


	UFUNCTION(Reliable, NetMulticast, BlueprintCallable)
	void Multi_SetIsTargetParabolic(bool IsTargetParabolic);
	void Multi_SetIsTargetParabolic_Implementation(bool IsTargetParabolic);
	
};
