// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/CharacterBase.h"
#include "Data/GP2EnumTypes.h"
#include "./Data/MonsterDataType.h"
#include "CharacterMonster.generated.h"

class UMaterialInstanceDynamic;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeactivate, ACharacterMonster*)

UCLASS()
class GUNSLINGERSW_API ACharacterMonster
	:
	public ACharacterBase
{
	GENERATED_BODY()
	friend class UAnimNotify_MonsterDissolve;
	friend class UAnimNotify_MonsterRagdoll;

public:
	ACharacterMonster();
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;

	void SetData(const FGWMonData& data) { Data = data; }

	UFUNCTION(NetMulticast, Reliable)
	void ReDeployMTC(const FTransform& transform);
	void ReDeployMTC_Implementation(const FTransform& transform);

	UFUNCTION(BlueprintCallable)
	const bool& IsAwake() { return Awake; }

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Activate();
	virtual void Activate_Implementation();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Deactivate();
	virtual void Deactivate_Implementation();

	UFUNCTION(Server, Reliable)
	void SimulateRagdoll(const bool active);
	void SimulateRagdoll_Implementation(const bool active);

	UFUNCTION(BlueprintCallable, Category = "CoreState")
	AAIController*						GetAiControll();

	FOnDeactivate& GetDeactivateDelegate() { return OnDeactivate; }

protected:
	UFUNCTION(NetMulticast, Reliable)
	void ActivateMTC();
	virtual void ActivateMTC_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void ActivateProcess();
	virtual void ActivateProcess_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void DeactivateMTC();
	virtual void DeactivateMTC_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void SimulateRagdollMTC(const bool active);
	void SimulateRagdollMTC_Implementation(const bool active);

	UFUNCTION(BlueprintNativeEvent)
	void DeactivateProcess();
	virtual void DeactivateProcess_Implementation();

	// NOTE : Dissolve ������ ������ ȣ���Ͽ� ���͸� ��Ȱ��ȭ �ϴ� �뵵�� �Լ��Դϴ�. ������ ������ ���������� ȣ���ϴ°� ���� �� �����ϴ�.
	UFUNCTION(BlueprintCallable)
	void SetInactivity() { Awake = false; }

	// NOTE : Ÿ�Ӷ��� Ȱ���� ���ؼ� �� �����δ� BP�� �ֽ��ϴ�. / By.�ȼ���
	UFUNCTION(BlueprintNativeEvent)
	void ActivateDissolve(const bool reverse);
	void ActivateDissolve_Implementation(const bool reverse) {}

private:
	void MakeMonsterDisappear();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	bool								AnimUseSkill = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	float								AnimAimOffSetX = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	float								AnimAimOffSetY = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	bool								AnimIsBattleStance = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	bool								AnimIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	bool								AnimGetHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	bool								AnimIsCriticalHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	bool								AnimIsJumping = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	bool								AnimIsJumpUp = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	float								AnimHitAngle = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	int									AnimIdleAction = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	EGWDamageTypes						AnimDamageType = EGWDamageTypes::Type_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	FName								AnimHitBone = "None";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	float								AnimHitBoneWeight = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	float								AnimMaxSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoreState_Animation", Replicated)
	bool								AnimBattleHowling = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BaseState")
	AAIController*						ControllerRef;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	FGWMonData							Data;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector								DefaultMeshPosition;
	
	UPROPERTY(VisibleAnywhere)
	bool								Awake = false;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float								DissolveDelay = 2.5f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInstanceDynamic*>	DynamicMats;

	FOnDeactivate OnDeactivate;
	
	FTimerHandle DissolveTimer;
};
