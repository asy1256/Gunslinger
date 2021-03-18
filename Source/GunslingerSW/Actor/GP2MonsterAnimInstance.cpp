// Fill out your copyright notice in the Description page of Project Settings.

#include "GP2MonsterAnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Actor/CharacterMonster.h"
#include "Engine.h"

void UGP2MonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MonsterRef != nullptr)
	{
		FVector velocity = MonsterRef->GetVelocity();

		//MoveSpeed
		MoveSpeed = velocity.Size();
		MoveSpeed = FMath::Clamp(0.0f, (MoveSpeed / MonsterRef->AnimMaxSpeed) * 100.0f, 100.0f);		

		//MoveDirection
		FRotator Delta = velocity.Rotation() - MonsterRef->GetActorRotation();
		Delta.Normalize();
		MoveDirection = Delta.Yaw;

		//MonsterRef.
		AimOffsetX = MonsterRef->AnimAimOffSetX;
		AimOffsetY = MonsterRef->AnimAimOffSetY;
		BattleStance = MonsterRef->AnimIsBattleStance;
		IsSkill =	MonsterRef->AnimUseSkill;
		IsDead = MonsterRef->AnimIsDead;
		GetHit = MonsterRef->AnimGetHit;
		IsCriticalHit = MonsterRef->AnimIsCriticalHit;
		IsJumping = MonsterRef->AnimIsJumping;
		IsJumpUp = MonsterRef->AnimIsJumpUp;
		HitAngle = MonsterRef->AnimHitAngle;
		IdleAction = MonsterRef->AnimIdleAction;
		DamageType = MonsterRef->AnimDamageType;
		IsBattleHowling = MonsterRef->AnimBattleHowling;
	}
}

void UGP2MonsterAnimInstance::PlayDieAnimation(float hitdirection)
{
	// NOTE : Montage_Play 함수 인자중 현재 재생중인 Montage를 멈추는 bool 값이 있는데 기본값이 true 입니다.
	if (hitdirection <= -135)
	{ Montage_Play(BackDieAnim); }
	else if (hitdirection <= -45)
	{ Montage_Play(LeftDieAnim); }
	else if (hitdirection <= 45)
	{ Montage_Play(FrontDieAnim); }
	else if (hitdirection <= 135)
	{ Montage_Play(RightDieAnim); }
	else
	{ Montage_Play(BackDieAnim); }
}