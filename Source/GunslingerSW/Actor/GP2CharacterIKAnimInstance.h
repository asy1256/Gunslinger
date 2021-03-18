// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Data/GP2EnumTypes.h"
#include "GP2CharacterIKAnimInstance.generated.h"


class ACharacterPC;

/**
 * 
 */
UCLASS()
class GUNSLINGERSW_API UGP2CharacterIKAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	float               PelvisOffset;       ///
	FVector             RightFootOffsets;   ///
	FVector             LeftFootOffsets;    ///
	FTransform          LeftFootTransform;  ///
	FTransform          RightFootTransform; ///
	bool                EnableFootIK;       ///
	EGWMovementMode MovementMode;       ///
	float               FootIK_Alpha;       ///



public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|IK" )
	ACharacterPC*       Owner;                     /// 소유자

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|IK" )
	FName               LeftFootBoneName;          /// 왼발 본이름

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|IK" )
	FName               RightFootBoneName;         /// 오른발 본이름

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|IK" )
	float               TraceLengthAboveFoot;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|IK" )
	float               TraceLengthBelowFoot;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|IK" )
	float               RotationOffsetInterpSpeed; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|IK" )
	float               ZOffsetInterpSpeed;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|IK" )
	FVector             MinLimits_Standing;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|IK" )
	FVector             MaxLimits_Standing;        ///


	
public:
	///을 설정한다.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetPelvisOffset( float _PelvisOffset ) { PelvisOffset = _PelvisOffset; }

	///을 설정한다.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetRightFootOffsets( const FVector& _RightFootOffsets ) { RightFootOffsets = _RightFootOffsets; }

	///을 설정한다.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetLeftFootOffsets( const FVector& _LeftFootOffsets ) { LeftFootOffsets = _LeftFootOffsets; }

	///을 설정한다.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetLeftFootTransform( const FTransform& _LeftFootTransform ) { LeftFootTransform = _LeftFootTransform; }

	///을 설정한다.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetRightFootTransform( const FTransform& _RightFootTransform ) { RightFootTransform = _RightFootTransform; }

	///을 설정한다.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetEnableFootIK( bool _EnableFootIK ) { EnableFootIK = _EnableFootIK; }

	///을 설정한다.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetMovementMode( const EGWMovementMode& _MovementMode ) { MovementMode = _MovementMode; }

	///을 설정한다.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetAlpha( float _Alpha ) { FootIK_Alpha = _Alpha; }

	///을 반환한다.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	float GetPelvisOffset() const { return PelvisOffset; }

	///을 반환한다.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	const FVector& GetRightFootOffsets() const { return RightFootOffsets; }

	///을 반환한다.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	const FVector& GetLeftFootOffsets() const { return LeftFootOffsets; }

	///을 반환한다.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	const FTransform& GetLeftFootTransform() const { return LeftFootTransform; }

	///을 반환한다.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	const FTransform& GetRightFootTransform() const { return RightFootTransform; }

	///을 반환한다.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	bool GetEnableFootIK() const { return EnableFootIK; }

	///을 반환한다.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	const EGWMovementMode& GetMovementMode() const { return MovementMode; }

	///을 반환한다.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	float GetAlpha() const { return FootIK_Alpha; }




public:
	//UFUNCTION( BlueprintCallable , Category = "Sub Anim-IK" )
	//void FootIK();
	//UFUNCTION( BlueprintCallable , Category = "Sub Anim-IK" )
	//void RagdollIK();
	//UFUNCTION( BlueprintCallable , Category = "Sub Anim-IK" )
	//void SetDefaultValues();
};
