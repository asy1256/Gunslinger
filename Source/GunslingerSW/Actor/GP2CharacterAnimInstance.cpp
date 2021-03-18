// Fill out your copyright notice in the Description page of Project Settings.


#include "GP2CharacterAnimInstance.h"

//void UGP2CharacterAnimInstance::SetReferences()
//{
//}
//
//void UGP2CharacterAnimInstance::SetDefaultValues()
//{
//}
//
//void UGP2CharacterAnimInstance::CalculateAimOffset()
//{
//}
//
//void UGP2CharacterAnimInstance::GetVariablesFromBaseCharacterBP()
//{
//}
//
//void UGP2CharacterAnimInstance::CalculateMovementDirection( float DirectionThresholdMin , float DirectionThresholdMax , float Buffer )
//{
//}
//
//void UGP2CharacterAnimInstance::CalculateGroundedLeaningValues()
//{
//}
//
//void UGP2CharacterAnimInstance::CalculateStartPosition()
//{
//}
//
//void UGP2CharacterAnimInstance::CalculateGaitValue()
//{
//}
//
//void UGP2CharacterAnimInstance::CalculatePlayRates()
//{
//}
//
//void UGP2CharacterAnimInstance::CalculateInAirLeaningValues()
//{
//}
//
//void UGP2CharacterAnimInstance::CalculateLandPredictionAlpha()
//{
//}
//
//// TurnInPlace( Delay )
//// TurnInPlace( Responsive )
//// OnMovementModeChanged
//


///----------------------------------------------------------------------------
///	Name	:	
///----------------------------------------------------------------------------
UBlendSpace* UGP2CharacterAnimInstance::NGetBlendSpace( EGWBlendSpaceAnim BlendSpace )
{
	switch( BlendSpace )
	{
	case EGWBlendSpaceAnim::LFMove:
		return Animations.LFMove;
	case EGWBlendSpaceAnim::NMoveF:
		return Animations.NMoveF;
	case EGWBlendSpaceAnim::NMove:
		return Animations.NMove;
	case EGWBlendSpaceAnim::LFMoveAim:
		return Animations.LFMoveAim;
	case EGWBlendSpaceAnim::NLeanGrounded:
		return Animations.NLeanGrounded;
	case EGWBlendSpaceAnim::NLeanDash:
		return Animations.NLeanDash;
	case EGWBlendSpaceAnim::AirMoveAim:
		return Animations.AirMoveAim;
	case EGWBlendSpaceAnim::NStopLF:
		return Animations.NStopLF;
	case EGWBlendSpaceAnim::NStopRF:
		return Animations.NStopRF;
	case EGWBlendSpaceAnim::LFStop:
		return Animations.LFStop;
	case EGWBlendSpaceAnim::HitInAir:
		return Animations.HitInAir;
	}

	return nullptr;
}


///----------------------------------------------------------------------------
///	Name	:	
///----------------------------------------------------------------------------
UAimOffsetBlendSpace* UGP2CharacterAnimInstance::NGetAimOffset()
{
	return Animations.AimOffset;
}


///----------------------------------------------------------------------------
///	Name	:	
///----------------------------------------------------------------------------
UAnimSequence* UGP2CharacterAnimInstance::NGetAnimSequence( EGWAnimSequence AnimSequence )
{
	switch ( AnimSequence )
	{
	case EGWAnimSequence::NAdd:
		return Animations.NAdd;
	case EGWAnimSequence::LFAdd:
		return Animations.LFAdd;
	case EGWAnimSequence::NPose:
		return Animations.NPose;
	case EGWAnimSequence::LFPose:
		return Animations.LFPose;
	case EGWAnimSequence::LFToN:
		return Animations.LFToN;
	case EGWAnimSequence::NToLF:
		return Animations.NToLF;
	case EGWAnimSequence::PivotF:
		return Animations.PivotF;
	case EGWAnimSequence::SprintBegin:
		return Animations.SprintBegin;
	case EGWAnimSequence::SprintLoop:
		return Animations.SprintLoop;
	case EGWAnimSequence::SprintStop:
		return Animations.SprintStop;
	case EGWAnimSequence::Land:
		return Animations.Land;
	case EGWAnimSequence::LandHigh:
		return Animations.LandHigh;
//	case EGWAnimSequence::JumpBeginIdle:
//		return Animations.JumpBeginIdle;
	case EGWAnimSequence::JumpBeginRun:
		return Animations.JumpBeginRun;
	case EGWAnimSequence::FallLoop:
		return Animations.FallLoop;
	case EGWAnimSequence::FallLoopHigh:
		return Animations.FallLoopHigh;
//	case EGWAnimSequence::AirSprintBegin:
//		return Animations.AirSprintBegin;
	case EGWAnimSequence::AirSprintLoop:
		return Animations.AirSprintLoop;
	case EGWAnimSequence::AirJumpBegin:
		return Animations.AirJumpBegin;
	case EGWAnimSequence::AirJumpLoop:
		return Animations.AirJumpLoop;
	case EGWAnimSequence::LandAdditive:
		return Animations.LandAdditive;
	case EGWAnimSequence::RespawnLoop:
		return Animations.RespawnLoop;
	case EGWAnimSequence::RespawnEnd:
		return Animations.RespawnEnd;
	case EGWAnimSequence::FirstSpawn:
		return Animations.FirstSpawn;
	case EGWAnimSequence::FirstSpawnLoop:
		return Animations.FirstSpawnLoop;
	case EGWAnimSequence::FirstSpawnRecovery:
		return Animations.FirstSpawnRecovery;
	case EGWAnimSequence::Win:
		return Animations.Win;
	case EGWAnimSequence::WinLoop:
		return Animations.WinLoop;
	case EGWAnimSequence::Defeat:
		return Animations.Defeat;
	case EGWAnimSequence::DefeatLoop:
		return Animations.DefeatLoop;
	case EGWAnimSequence::Die:
		return Animations.Die;
	case EGWAnimSequence::Knockback:
		return Animations.Knockback;
	case EGWAnimSequence::CommonIdle:
		return Animations.CommonIdle;
	case EGWAnimSequence::Stun:
		return Animations.Stun;
	case EGWAnimSequence::Shock:
		return Animations.Shock;
	case EGWAnimSequence::LFLand:
		return Animations.LFLand;
	case EGWAnimSequence::LFLandHigh:
		return Animations.LFLandHigh;
	}

	return nullptr;
}

///----------------------------------------------------------------------------
///	Name	:	
///----------------------------------------------------------------------------
UAnimMontage* UGP2CharacterAnimInstance::NGetMontage( EGWMontage Montage )
{
	switch( Montage )
	{
	case EGWMontage::LFTurnL90:
		return Animations.LFTurnL90;
	case EGWMontage::LFTurnR90:
		return Animations.LFTurnR90;
	case EGWMontage::Fire:
		return Animations.Fire;
	case EGWMontage::Reload:
		return Animations.Reload;
	case EGWMontage::WeaponChange:
		return Animations.WeaponChange;
	}

	return nullptr;
}

///----------------------------------------------------------------------------
///	Name	:	
///----------------------------------------------------------------------------
//void UGP2CharacterAnimInstance::SetAnimationsForWeapon()
//{
//}
//
//float UGP2CharacterAnimInstance::GetDeltaTick()
//{
//	return 0.0f;
//}