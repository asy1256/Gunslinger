// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GameFramework/Controller.h"
#include "Data/SkillDataType.h"

#include "StatusEffectBase.generated.h"





//class AController;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GUNSLINGERSW_API UStatusEffectBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusEffectBase();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:
	FString                         StatusEffectId;     ///

	struct FGWStatusEffectInfo               StatusEffectInfo;   ///

	FTimerHandle                    EffectTimerHandle;  ///


	UPROPERTY(Transient, Replicated)
	int32                           StackCount;         ///

	int32                           MaxStackCount;      ///

	UPROPERTY(Transient, Replicated)
	AController*                    DamageInstigator;   ///

	float                           MaxSkillDuration;   ///

	UPROPERTY(Transient, ReplicatedUsing=OnRep_SkillDuration)
	float                           SkillDuration;      ///

	bool                            IsEffectEnd;        ///

	EGWAffectType                     AffectType;         ///

	FName                           ActorParameterName; ///

	class UParticleSystemComponent* CurrentPS;          ///

public:
	bool HasAuthority();

	void UpdateTime(float delta);

	void InitStatusEffect(const FString& SkillEffectId);

	void SetInstigator(AController* Instigator);

	/**
	* Add Effect
	*/
	void AddEffect(const FString& SkillEffectId);

	/**
	* overwrite Effect
	*/
	void OverwriteEffect(const FString& SkillEffectId);

	/**
	* Spawn Particle
	*/
	void ShowEffect();

	/**
	* Current Particle Destroy
	*/
	void EffectDestroy();

	void SetStatusEffectData(const FString& SkillEffectId);

	/**
	* Reset Timer
	*/
	void ResetTimer();


	void InitData();

	void ApplyStatusEffect();

	void EndStatusEffect();

public:
	/**
	* Override Function
	* Cancel Effect
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CancelEffect();

	/**
	* Override Function
	* Apply Effect
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ApplyEffect();

	/**
	* Override Function
	* Stack Effect
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StackEffect(int32 Count);


	UFUNCTION()
	virtual void OnRep_SkillDuration();




	UFUNCTION(Reliable, NetMulticast)
	void Multi_EffectDestroy();
	void Multi_EffectDestroy_Implementation();


	UFUNCTION(Reliable, NetMulticast)
	void Multi_ResetTimer();
	void Multi_ResetTimer_Implementation();

	UFUNCTION(Reliable, NetMulticast)
	void Multi_SetStatusEffectData(const FString& SkillEffectId);
	void Multi_SetStatusEffectData_Implementation(const FString& SkillEffectId);


	UFUNCTION(Reliable, NetMulticast)
	void Multi_InitStatusEffect(const FString& SkillEffectId);
	void Multi_InitStatusEffect_Implementation(const FString& SkillEffectId);


	UFUNCTION(Reliable, Server, WithValidation)
	void Server_SetInstigator(AController* Instigator);
	void Server_SetInstigator_Implementation(AController* Instigator);
	bool Server_SetInstigator_Validate(AController* Instigator);

	UFUNCTION(Reliable, Server, WithValidation)
	void Server_AddEffect(const FString& SkillEffectId);
	void Server_AddEffect_Implementation(const FString& SkillEffectId);
	bool Server_AddEffect_Validate(const FString& SkillEffectId);

	UFUNCTION(Reliable, Server, WithValidation)
	void Server_OverwriteEffect(const FString& SkillEffectId);
	void Server_OverwriteEffect_Implementation(const FString& SkillEffectId);
	bool Server_OverwriteEffect_Validate(const FString& SkillEffectId);
};
