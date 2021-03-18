#pragma once
#include "CoreMinimal.h"
#include "CharacterMonster.h"
#include "Animation/AnimInstance.h"
#include "GP2MonsterAnimInstance.generated.h"

class UAnimMontage;
class ACharacterMonster;

UCLASS()
class GUNSLINGERSW_API UGP2MonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void PlayDieAnimation(float hitdirection);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	ACharacterMonster* MonsterRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	float MoveDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	float AimOffsetX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	float AimOffsetY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	bool BattleStance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	bool IsSkill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	bool IsDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	bool GetHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	bool IsCriticalHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	bool IsJumping;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	bool IsJumpUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	float HitAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	int IdleAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	EGWDamageTypes DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	bool IsBattleHowling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	int BossPhaseType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobAnimInstance")
	bool IsSkillMontagePlaying;//공격동작중인가?

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MobAnimInstance")
	UAnimMontage* FrontDieAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MobAnimInstance")
	UAnimMontage* BackDieAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MobAnimInstance")
	UAnimMontage* RightDieAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MobAnimInstance")
	UAnimMontage* LeftDieAnim;
};
