// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "UnrealNetwork.h"

#include <list>
#include "CharacterPC.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UMaterialInstanceDynamic;

UENUM( BlueprintType )
enum class FlagOnOff : uint8
{
	OFF ,
	ON
};


UCLASS()
class GUNSLINGERSW_API ACharacterPC
	:
	public ACharacterBase
{
	GENERATED_BODY()

private:
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = ( AllowPrivateAccess = "true" ) )
	class USpringArmComponent* CameraBoom; /// Camera boom positioning the camera behind the character

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = ( AllowPrivateAccess = "true" ) )
	class UCameraComponent* FollowCamera; /// Follow camera

	UPROPERTY( Replicated , VisibleAnywhere , BlueprintReadWrite , meta = ( AllowPrivateAccess = "true", Bitmask , BitmaskEnum ="EGWPlayerStateFlag" ) )
	int32 CurrentPlayerStateFlag = 0; /// 

public:	
	// Sets default values for this character's properties
	ACharacterPC();

	/// Called before destroying the object.  
	/// virtual void BeginDestroy() override;

	/// Called when the game starts or when spawned
	/// virtual void BeginPlay() override;

	/// Overridable function called whenever this actor is being removed from a level
	/// virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

	/// Called every frame
	/// virtual void Tick( float DeltaSeconds ) override;

	/// Called once this actor has been deleted
	/// virtual void Destroyed() override;

	/// 
	virtual void GetActorEyesViewPoint( FVector& OutLocation , FRotator& OutRotation ) const override;

public:
	/** Returns CameraBoom subobject **/
	virtual USpringArmComponent* GetCameraBoom() const override { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	virtual UCameraComponent* GetFollowCamera() const override { return FollowCamera; }

	/// 
	void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const override;

public:
	/// 
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "EAC SERVER")
	void eacLogEventPlayerSpawn(AController *Player, const int32 TeamType, const int32 CharID);

	/// 
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "EAC SERVER")
	void eacLogEventPlayerTakeDamage(APlayerController *VictimPlayer, APlayerController *AttackerPlayer, const int32 Weaponindex, const EPhysicalSurface HitID, const float Damagevalue);

	/// 
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "EAC SERVER")
	void eacLogEventPlayerDespawn(AController *Player, AController *Killer);

	/// 
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "EAC SERVER")
	void eacLogEventPlayerTick(const int32 CurHP );

	/// 
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "EAC SERVER")
	void eacLogEventPlayerUseWeapon(const int32 Weaponindex, const bool IsMeleeAttack);


public :
	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool NativeCanFire();

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool IsFireFlagOn();

	UFUNCTION( BlueprintCallable , Category = "CharacterState" )
	void SetFireFlag( FlagOnOff Flag );

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool NativeCanWeaponChange();

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool IsWeaponChangeFlagOn();

	UFUNCTION( BlueprintCallable , Category = "CharacterState" )
	void SetWeaponChangeFlag( FlagOnOff Flag );

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool NativeCanReload();

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool IsReloadFlagOn();

	UFUNCTION( BlueprintCallable , Category = "CharacterState" )
	void SetReloadFlag( FlagOnOff Flag );

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool NativeCanZoom();

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool IsZoomFlagOn();

	UFUNCTION( BlueprintCallable , Category = "CharacterState" )
	void SetZoomFlag( FlagOnOff Flag );

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool NativeCanWeaponSkill();

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool IsWeaponSkillFlagOn();

	UFUNCTION( BlueprintCallable , Category = "CharacterState" )
	void SetWeaponSkillFloa( FlagOnOff Flag );

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool NativeCanUltraSkill();

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool IsUltrasSkillFlagOn();

	UFUNCTION( BlueprintCallable , Category = "CharacterState" )
	void SetUltraSkillFlag( FlagOnOff Flag );

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool NativeCanDashForce();

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool IsDashForceFlagOn();

	UFUNCTION( BlueprintCallable , Category = "CharacterState" )
	void SetDashForceFlag( FlagOnOff Flag );

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool NativeCanDashLoop();

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool IsDashLoopFlagOn();

	UFUNCTION( BlueprintCallable , Category = "CharacterState" )
	void SetDashLoop( FlagOnOff Flag );

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool NativeCanForceAirJump();

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool IsForceAirJumpFlagOn();

	UFUNCTION( BlueprintCallable , Category = "CharacterState" )
	void SetForceAirJump( FlagOnOff Flag );

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool NativeCanLoopAirJump();

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool IsJumpLoopFlagOn();

	UFUNCTION( BlueprintCallable , Category = "CharacterState" )
	void SetLoopAirJump( FlagOnOff Flag );

	UFUNCTION( BlueprintCallable , Category = "CharacterState" )
	void SetPlayerState( EGWPlayerState NewState , EGWPlayerState& PrevState );

	UFUNCTION( BlueprintPure , Category = "CharacterState" )
	bool CanChangePlayerState( EGWPlayerState NewState );

};
