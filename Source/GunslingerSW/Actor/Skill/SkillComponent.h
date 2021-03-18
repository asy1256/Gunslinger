// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

//#include "SkillDataType.h"
#include "Data/SkillDataType.h"
#include "Data/GP2DataStructTypes.h"
#include "SkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUNSLINGERSW_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

protected:

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		

public:

	UPROPERTY(Transient, Replicated)
	struct FGWSkillInfo		SkillData;

	UPROPERTY(Transient, Replicated)
	bool				HasSkillData;

	UPROPERTY(Transient, Replicated)
	float		SkillTime;

	UPROPERTY(Transient, Replicated)
	float		CastTime;

	UPROPERTY(Transient, Replicated)
	bool		IsCasting;

	bool		HasSkillActor;

	FGWSkillActorInfo	SkillActorData;

	UPROPERTY(Transient, Replicated)
	float		HoldFireTime;

	bool		IsHoldFire;

	UPROPERTY(Transient, Replicated)
	bool		IsRunSkill;

	UPROPERTY(Transient, Replicated)
	float		SkillDurationTime;

public:

	bool HasAuthority() const;

	// ###########  Update Time  ###########
	void UpdateTime(float delta);
	void UpdateCoolTime(float delta);
	void UpdateCastTime(float delta);
	void UpdateHoldTime(float delta);
	void UpdateDurationTime(float delta);

	// Can Skill?
	bool CanSkill() const;


	UFUNCTION(Reliable, Server, WithValidation)
	void InitSKillData(struct FGWSkillInfo SkillInfo);
	void InitSKillData_Implementation(struct FGWSkillInfo SkillInfo);
	bool InitSKillData_Validate(struct FGWSkillInfo SkillInfo);


	float GetSkillDamage() const;

	FTransform GetCastTransform() const;

	// Run Skill (4)
	UFUNCTION(Reliable, Server, WithValidation)
	void Server_RunSkill();
	void Server_RunSkill_Implementation();
	bool Server_RunSkill_Validate();


	// Skill Start (1)
	UFUNCTION(Reliable, Server, WithValidation)
	void Server_OnStartSkill();
	void Server_OnStartSkill_Implementation();
	bool Server_OnStartSkill_Validate();

	// Casting Skill (2)
	void OnCastSkill();

	// Active Skill (3)
	UFUNCTION(Reliable, Server, WithValidation)
	void Server_OnActiveSkill();
	void Server_OnActiveSkill_Implementation();
	bool Server_OnActiveSkill_Validate();

	// Active Skill (3)
	UFUNCTION(Reliable, NetMulticast)
	void Multi_RunSkillAnimation();
	void Multi_RunSkillAnimation_Implementation();



	UFUNCTION(Reliable, NetMulticast)
	void Multi_CharacterEffect();
	void Multi_CharacterEffect_Implementation();

	UFUNCTION(Reliable, NetMulticast)
	void Multi_MuzzleEffect();
	void Multi_MuzzleEffect_Implementation();


	UFUNCTION(Unreliable, Client)
	void Client_CameraShake();
	void Client_CameraShake_Implementation();

	UFUNCTION(Unreliable, Client)
	void Client_SpawnSkillActor();
	void Client_SpawnSkillActor_Implementation();


	void ApplyBuffEffect();

	// Init Skill Time & Duration & RunSkill Flag = true
	void OnSkillDuration();


	UFUNCTION(Unreliable, Client)
	void Client_WeaponTrace(int32 index);
	void Client_WeaponTrace_Implementation(int32 index);

	// Spawn Projectile (Server)
//	UFUNCTION(Reliable, Server, WithValidation)
	//void Server_Spawnprojectile(TSubclassOf<class AProjectileBase> ProjectileClass, const FTransform& SpawnTransform, AActor* Owner, APawn* Instigator);
	//void Server_Spawnprojectile_Implementation(TSubclassOf<class AProjectileBase> ProjectileClass, const FTransform& SpawnTransform, AActor* Owner, APawn* Instigator);
	//bool Server_Spawnprojectile_Validate(TSubclassOf<class AProjectileBase> ProjectileClass, const FTransform& SpawnTransform, AActor* Owner, APawn* Instigator);
	
};
