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
	ACharacterPC*       Owner;                     /// ������

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|IK" )
	FName               LeftFootBoneName;          /// �޹� ���̸�

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|IK" )
	FName               RightFootBoneName;         /// ������ ���̸�

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
	///�� �����Ѵ�.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetPelvisOffset( float _PelvisOffset ) { PelvisOffset = _PelvisOffset; }

	///�� �����Ѵ�.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetRightFootOffsets( const FVector& _RightFootOffsets ) { RightFootOffsets = _RightFootOffsets; }

	///�� �����Ѵ�.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetLeftFootOffsets( const FVector& _LeftFootOffsets ) { LeftFootOffsets = _LeftFootOffsets; }

	///�� �����Ѵ�.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetLeftFootTransform( const FTransform& _LeftFootTransform ) { LeftFootTransform = _LeftFootTransform; }

	///�� �����Ѵ�.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetRightFootTransform( const FTransform& _RightFootTransform ) { RightFootTransform = _RightFootTransform; }

	///�� �����Ѵ�.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetEnableFootIK( bool _EnableFootIK ) { EnableFootIK = _EnableFootIK; }

	///�� �����Ѵ�.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetMovementMode( const EGWMovementMode& _MovementMode ) { MovementMode = _MovementMode; }

	///�� �����Ѵ�.
 	UFUNCTION( BlueprintCallable  , Category = "GP2 AnimInstance|IK" )
	void SetAlpha( float _Alpha ) { FootIK_Alpha = _Alpha; }

	///�� ��ȯ�Ѵ�.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	float GetPelvisOffset() const { return PelvisOffset; }

	///�� ��ȯ�Ѵ�.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	const FVector& GetRightFootOffsets() const { return RightFootOffsets; }

	///�� ��ȯ�Ѵ�.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	const FVector& GetLeftFootOffsets() const { return LeftFootOffsets; }

	///�� ��ȯ�Ѵ�.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	const FTransform& GetLeftFootTransform() const { return LeftFootTransform; }

	///�� ��ȯ�Ѵ�.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	const FTransform& GetRightFootTransform() const { return RightFootTransform; }

	///�� ��ȯ�Ѵ�.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	bool GetEnableFootIK() const { return EnableFootIK; }

	///�� ��ȯ�Ѵ�.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2 AnimInstance|IK" )
	const EGWMovementMode& GetMovementMode() const { return MovementMode; }

	///�� ��ȯ�Ѵ�.
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
