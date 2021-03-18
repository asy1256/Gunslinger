// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Data
#include "../../Data/GP2DataStructTypes.h"
#include "WeaponBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHoldFireDelegate, bool, IsHold);

UCLASS(config = Game, BlueprintType)
class GUNSLINGERSW_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true" ) )
		class USkeletalMeshComponent* WeaponMesh;

	/** Status Manager **/
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true" ) )
		class USkillComponent*	SkillComp;

	//UPROPERTY( VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true" ) )
	//	class USoundComponent* FireSoundComponent; 

protected:
	int ObjId; /// 고유 식별자

public:
	


	UPROPERTY(BlueprintReadWrite, Category = "Init")
	FName					TableId;

	UPROPERTY(BlueprintReadWrite, Category = "Init")
	int32					InfoId;


	// Weapon Struct Info
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FGWWeaponInfo			WeaponInfo;

	// Skill Info
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FGWSkillInfo			SkillInfo;


	// Muzzle Socket
	UPROPERTY(BlueprintReadWrite, Category = "Socket Name")
	FName					MuzzleSocketName;

	// Attach Socket Right
	UPROPERTY(BlueprintReadWrite, Category = "Socket Name")
	FName					AttachRSocketName;

	// Attach Socket Left
	UPROPERTY(BlueprintReadWrite, Category = "Socket Name")
	FName					AttachLSocketName;



	UPROPERTY(Transient, Replicated, VisibleAnywhere)
	int32					CurrentAmmoInClip;
	
	UPROPERTY(Transient, Replicated, VisibleAnywhere)
	int32					MaxAmmoClipSize;

	UPROPERTY(Transient, Replicated, VisibleAnywhere)
	int32					MaxReloadSize;

	UPROPERTY(Transient, Replicated, VisibleAnywhere)
	int32					CurrentMaxAmmo;

	int32					AmmoNeededForReload;
	int32					MaxAmmo;

	float					ZoomFOV;
	FVector					ZoomOffset;

	bool					bIsTwoHand;
	bool					bInfinityMaxAmmo;
	bool					bInfinityWeapon;
	bool					bHaveWeaponSkill;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool					bIsBeamType;

	//Bullet Trace Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Effect")
	class UParticleSystem*		PS_TraceFX;

	// Weapon Muzzle FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Effect")
	class UParticleSystem*		PS_MuzzleFX;

	// Bullet Impact FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Effect")
	class UParticleSystem*		PS_ImpactFX;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Sound")
	class USoundCue*			SingleFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Sound")
	class USoundCue*			ShotEndSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Sound")
	class USoundCue*			BulletImpactSound;


	// Camera Shake Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Class")
	TSubclassOf<class UCameraShake>		WeaponShakeClass;

	// Force Feedback


	// Bind Attack
	bool					bIsBindAttack;
	TArray<FString>			BindSkillEffectId;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector					TraceEndLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float					fSphereTraceRadius;


	// Reload
	bool bIsReload;


	/* 발사 타이머 핸들 */
	FTimerHandle			FireTimerHandle;


	/* Skill */
	UPROPERTY(Transient, Replicated)
	float					fAddSkillDamageRate;


	float					LastFireTime;


	// 홀드 파이어
	FHoldFireDelegate		HoldFireDelegate;

public:
	bool InitWeaponInfo();


	/* Util Func */
	FVector GetTraceStartLocation() const;

	float CalcDamage() const;
	bool CalcDamageByDefence(float& Damage, const FHitResult HitResult) const;
	bool CalcDamageByPhysical(float& Damage, const FHitResult HitResult) const;
	bool CalcDamageByDistance(float& Damage, const FHitResult HitResult) const;


	/* 발사 */
	void OnFire(bool bIsFire);
	/* 발사 중지 */
	void OnStopFire();


	void FireTimer();

	/* 발사 가능한 Interval인지 체크 */
	bool CheckFireInterval();

	/* 발사 가능한지? */
	bool CanFire();

	/* 재정전 여부 */
	bool CanReload();

	void OnReload();

	void AddAmmo(const int Ammo);

	UFUNCTION(Reliable, Server, WithValidation)
	void Server_Reload();
	void Server_Reload_Implementation();
	bool Server_Reload_Validate();


	/* 총알 감소 */
	void DecrementAmmo();

	UFUNCTION(Reliable, Server, WithValidation)
	void Server_DecrementAmmo();
	void Server_DecrementAmmo_Implementation();
	bool Server_DecrementAmmo_Validate();


	// 웨폰 발사 기본 로직
	UFUNCTION(BlueprintCallable)
	void OnFireBase();

	/* 발사 로직 */
	UFUNCTION(BlueprintCallable)
	virtual void FireBaseLogic();

	/* 벅샷 로직 */
	void BuckshotLogic();


	/* Shoot Info */
	UFUNCTION(BlueprintCallable)
	void ShootInfo(FHitResult& OutResult, bool& OutHit, float& OutDamage, FHitResult HitResult, bool bHit, FVector FireLocation, FVector EndTrace);



	void SubAttack(float Damage, FHitResult HitResult, bool bIsHit);

	void BindAttack(FHitResult HitResult, bool bIsHit);



	/* 카메라 쉐이크 */
	void OnCameraShake();

	/* 머즐 이팩트와 사운드 */
	UFUNCTION(Reliable, Server, WithValidation)
	void Server_MuzzleFXAndSound();
	void Server_MuzzleFXAndSound_Implementation();
	bool Server_MuzzleFXAndSound_Validate();

	void SpawnMuzzleFXAndSound();

	void IncreseSpread(float IncreaseSpreadAmount);


	/* Weapon Trace */
	UFUNCTION(BlueprintCallable)
	void WeaponSphereTrace(TArray<FHitResult>& HitResults, bool& bIsHit, FVector& EndTrace);

	/* Server Fire */
	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable)
	void Server_SetFire(const TArray<FHitResult>& HitResults, const bool bIsHit, const FVector FireLocation, const FVector EndTrace);
	void Server_SetFire_Implementation(const TArray<FHitResult>& HitResults, const bool bIsHit, const FVector FireLocation, const FVector EndTrace);
	bool Server_SetFire_Validate(const TArray<FHitResult>& HitResults, const bool bIsHit, const FVector FireLocation, const FVector EndTrace);


	/* Bullet Trail FX */
	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable)
	void Server_FireBullerTrailFX(const TArray<FHitResult>& HitResults, FVector TargetLocation);
	void Server_FireBullerTrailFX_Implementation(const TArray<FHitResult>& HitResults, FVector TargetLocation);
	bool Server_FireBullerTrailFX_Validate(const TArray<FHitResult>& HitResults, FVector TargetLocation);

	void FireBulletTrailFX(const TArray<FHitResult> HitResults, FVector TargetLocation);

	/* Bullet Impact FX */
	UFUNCTION(Reliable, NetMulticast, WithValidation, BlueprintCallable)
	void Multi_FireImpactFX(const TArray<FHitResult>& HitResults);
	void Multi_FireImpactFX_Implementation(const TArray<FHitResult>& HitResults);
	bool Multi_FireImpactFX_Validate(const TArray<FHitResult>& HitResults);



	/* Spawn Projecilt */
	void SpawnProjectile(const FHitResult& HitResult, const bool& bHit, const FVector& StartLocation, const FVector& EndTrace);



	// Weapon Skill
	void OnWeaponSkill();

public:
	UFUNCTION( BlueprintCallable )
	int GetObjId() const { return ObjId; }

	UFUNCTION(BlueprintCallable)
	void SetObjId( int InObjId ) { ObjId = InObjId; }

public:

	/* Fire Mode */
	UFUNCTION(BlueprintCallable)
	void AutoMode();

	UFUNCTION(BlueprintCallable)
	void BurstMode();
	
	UFUNCTION(BlueprintCallable)
	void AutoSpoolMode();

	UFUNCTION(BlueprintCallable)
	void ChargeMode();

	UFUNCTION(BlueprintCallable)
	void BurstChargeMode();

	UFUNCTION(BlueprintCallable)
	void HoldMode();


};
