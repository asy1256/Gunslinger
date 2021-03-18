// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Data/GP2DataStructTypes.h"
#include "../Data/GP2EnumTypes.h"
#include "GP2CharacterAnimInstance.generated.h"


class UAnimMontage;
class ACharacterPC;

/**
 * 
 */
UCLASS()
class GUNSLINGERSW_API UGP2CharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	class ACharacterPC* Owner; /// ¼ÒÀ¯ÀÚ

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	FVector               Velocity;                        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	FVector2D             AimOffset;                       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	FVector2D             LeanGrounded;                    ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	FVector2D             FeetPosition;                    ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	EGWMovementDirection    MovementDirection;               ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	EGWGaitType             Gait;                            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	EGWRotationMode         RotationMode;                    ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	EGWViewMode             ViewMode;                        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 Direction;                       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 Speed;                           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 GaitValue;                       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 N_PlayRate;                      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 StartPosition;                   ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 LeanInAir;                       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 LeanInAirPitch;                  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 FlailRate;                       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 FlailBelndAlpha;                 ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 LandPredictionAlpha;             ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 TargetCharacterRotationDiffence; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 MovementInputVelocityDifference; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  Aiming;                          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsMoving;                        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  HasMovementInput;                ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  ShouldTurnInPlace;               ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  Zooming;                         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsJump;                          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsAirJump;                       ///

	/// Turn In Place System
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  TurningInPlace;                  ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  TurningRight;                    ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 TurnInPlaceDelayCount;           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	class UAnimMontage*   ActiveTurnInPlaceMongtage;       ///


	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	struct FGWPivotParams   PivotParam;                      


	/// Leaning Calculations
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	FRotator              PreviousVelocityRotation;        

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 VelocityDifference;              

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 PreviousSpeed;                   

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 AccelerationDifference;          

	   
	/// Rotator
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	FRotator              CharacterRotation;               

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	FRotator              LastVelocityRotation;            

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	FRotator              LastMovementInputRotation;       

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	FRotator              LookingRotation;                 


	/// Floats
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 AimYawDelta;                     

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 AimYawRate;                      

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 WalkingSpeed;                    

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 RunningSpeed;                    

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 SprintingSpeed;                  

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	EGWLocomotionState      ActiveLocomotionState;           


	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	float                 StopCompareDifferenceValue;      


	/// mission
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  MissionCompleted;                

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	EGWResult               MissionResult;                   

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  MissionFinished;                 


	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsSprintBraking;                 

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  ShouldSprint;                    

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  ForceSprint;                     

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsReloading;       
	

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance" )
	struct FGWAnimationListInfo Animations;


	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsWeaponChange;                  

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsFirstSpawn;                    

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsRespawn;                       

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	EGWMachineState         MachineState;                    

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsHit;                           

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsMeleeWeapon;                   

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  MontagePose;                     

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsUltraSkillActivate;            

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  ForceAirJump;                    

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	EGWWeaponSlot           CurrentWeaponSlot;               

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  AimPose;                         

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	FRotator              InterpRotation;                  

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsShock;                         

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  IsStun;                          

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	bool                  FoundAnim;                       

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	FString               AnimKey;                         

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2 AnimInstance|Base" )
	EGWFallLoopMethod       FallloopMethod;


public:
	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//void SetReferences();

	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//void SetDefaultValues();

	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//void CalculateAimOffset();

	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//void GetVariablesFromBaseCharacterBP();

	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//void CalculateMovementDirection( float DirectionThresholdMin , float DirectionThresholdMax , float Buffer );

	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//void CalculateGroundedLeaningValues();

	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//void CalculateStartPosition();

	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//void CalculateGaitValue();

	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//void CalculatePlayRates();

	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//void CalculateInAirLeaningValues();

	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//void CalculateLandPredictionAlpha();

	//// TurnInPlace( Delay )
	//// TurnInPlace( Responsive )
	//// OnMovementModeChanged

	/// 
	UFUNCTION( BlueprintPure , Category = "GP2 AnimInstance" )
	class UBlendSpace* NGetBlendSpace( EGWBlendSpaceAnim BlendSpace );

	/// 
	UFUNCTION( BlueprintPure , Category = "GP2 AnimInstance" )
	class UAimOffsetBlendSpace* NGetAimOffset();

	/// 
	UFUNCTION( BlueprintPure , Category = "GP2 AnimInstance" )
	class UAnimSequence* NGetAnimSequence( EGWAnimSequence AnimSequence );

	/// 
	UFUNCTION( BlueprintPure , Category = "GP2 AnimInstance" )
	class UAnimMontage* NGetMontage( EGWMontage Montage );

	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//void SetAnimationsForWeapon();

	//UFUNCTION( BlueprintCallable , Category = "GP2 AnimInstance" )
	//float GetDeltaTick();


	public:

};
