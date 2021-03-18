// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPC.h"
#include "GunslingerSW.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Components/SkeletalMeshComponent.h>
#include "TimerManager.h"
#include "IEasyAntiCheatServer.h"
#include "Net/UnrealNetwork.h"

// Sets default values

// ACharacterPC::ACharacterPC() : ACharacterBase()
ACharacterPC::ACharacterPC()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize( 42.f , 96.0f );

	// set our turn rates for input

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator( 0.0f , 540.0f , 0.0f ); // ...at this rotation rate
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>( TEXT( "CameraBoom" ) );
	CameraBoom->SetupAttachment( RootComponent );
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>( TEXT( "FollowCamera" ) );
	FollowCamera->SetupAttachment( CameraBoom , USpringArmComponent::SocketName ); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}


//void ACharacterPC::BeginDestroy()
//{
//	Super::BeginDestroy();
//}
//
//void ACharacterPC::BeginPlay()
//{
//	Super::BeginPlay();
//}
//
//void ACharacterPC::Tick( float DeltaTime )
//{
//	QUICK_SCOPE_CYCLE_COUNTER( STAT_ACharacterPC )
//
//	Super::Tick( DeltaTime );
//}
//
//void ACharacterPC::Destroyed()
//{
//	Super::Destroyed();
//}

void ACharacterPC::GetActorEyesViewPoint( FVector& Location , FRotator& Rotation ) const
{
	Location = FollowCamera->GetComponentLocation();
	Rotation = FollowCamera->GetComponentRotation();
}

void ACharacterPC::eacLogEventPlayerSpawn_Implementation( AController * Player , const int32 TeamType , const int32 CharID )
{
	// Log spawn event to EAC.
	if ( IEasyAntiCheatServer::IsAvailable() && IEasyAntiCheatServer::Get().IsActive() )
	{
		if ( Player )
		{
			IEasyAntiCheatServer::Get().LogEventPlayerSpawn( Player , ( uint32 ) TeamType , ( uint32 ) CharID );
		}
	}
}

void ACharacterPC::eacLogEventPlayerTakeDamage_Implementation( APlayerController * VictimPlayer , APlayerController * AttackerPlayer , const int32 Weaponindex , const EPhysicalSurface HitID , const float Damagevalue )
{
	// Provide EAC server anti-cheat information about this damage event.
	if ( IEasyAntiCheatServer::IsAvailable() && IEasyAntiCheatServer::Get().IsActive() &&
		 VictimPlayer && AttackerPlayer )
	{
		if ( AttackerPlayer )
		{
			uint32 HitBoneID = ( uint32 ) ( HitID );

			easyanticheat::cerberus::PlayerTakeDamageFlags TakeDamageFlags = easyanticheat::cerberus::PlayerTakeDamageFlags::PlayerTakeDamageNormalHit;

			if ( HitID == EPhysicalSurface::SurfaceType17 )
			{
				TakeDamageFlags = easyanticheat::cerberus::PlayerTakeDamageFlags::PlayerTakeDamageCriticalHit;
			}

			IEasyAntiCheatServer::Get().LogEventPlayerTakeDamage( VictimPlayer , AttackerPlayer , ( uint32 ) Weaponindex , HitBoneID , static_cast< uint32 >( Damagevalue ) , TakeDamageFlags );
		}
	}
}

void ACharacterPC::eacLogEventPlayerDespawn_Implementation( AController * Player , AController * Killer )
{
	// Log the despawn event to EAC.
	if ( IEasyAntiCheatServer::IsAvailable() && IEasyAntiCheatServer::Get().IsActive() )
	{
		IEasyAntiCheatServer::Get().LogEventPlayerDespawn( Player , true , Killer );
	}
}

void ACharacterPC::eacLogEventPlayerTick_Implementation( const int32 CurHP )
{
	// Provide tick information to EAC.
	if ( IEasyAntiCheatServer::IsAvailable() && IEasyAntiCheatServer::Get().IsActive() )
	{
		APlayerController* PC = Cast<APlayerController>( this->Controller );
		if ( PC && !PC->IsPendingKillPending() )
		{
			APawn* PlayerPawn = PC->GetPawn();
			uint32 TickFlags = easyanticheat::cerberus::PlayerTickFlags::PlayerTickNone;

			// Determine the player's movement state for EAC's flags.
			if ( PlayerPawn && !PlayerPawn->IsPendingKillPending() && PlayerPawn->GetMovementComponent() )
			{
				if ( PlayerPawn->GetMovementComponent()->IsMovingOnGround() )
				{
					TickFlags |= easyanticheat::cerberus::PlayerTickFlags::PlayerTickAirborne;
				}
				if ( PlayerPawn->GetMovementComponent()->IsSwimming() )
				{
					TickFlags |= easyanticheat::cerberus::PlayerTickFlags::PlayerTickSwimming;
				}
				if ( PlayerPawn->GetMovementComponent()->IsCrouching() )
				{
					TickFlags |= easyanticheat::cerberus::PlayerTickFlags::PlayerTickCrouched;
				}
			}

			IEasyAntiCheatServer::Get().LogEventPlayerTick( Cast<APlayerController>( this->Controller ) ,
				( uint32 ) CurHP ,
															static_cast< easyanticheat::cerberus::PlayerTickFlags >( TickFlags ) );
		}
	}
}

// Weapon Firing
void ACharacterPC::eacLogEventPlayerUseWeapon_Implementation( const int32 Weaponindex , const bool IsMeleeAttack )
{
	// Provide EAC server anti-cheat information about this weapon fire event.
	if ( Role == ROLE_Authority && IEasyAntiCheatServer::IsAvailable() && IEasyAntiCheatServer::Get().IsActive() )
	{
		APlayerController* PlayerController = Cast<APlayerController>( this->Controller );
		if ( PlayerController )
		{
			IEasyAntiCheatServer::Get().LogEventPlayerUseWeapon( PlayerController , ( uint32 ) Weaponindex , IsMeleeAttack );
		}
	}
}

bool ACharacterPC::NativeCanFire()
{
	return !( CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_CanFireCondition );
}

bool ACharacterPC::IsFireFlagOn()
{
	return CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_Fire;
}

void ACharacterPC::SetFireFlag( FlagOnOff Flag )
{
	Flag == FlagOnOff::ON ? CurrentPlayerStateFlag |= ( int32 ) EGWPlayerStateFlag::ECB_Fire : CurrentPlayerStateFlag &= ~( int32 ) EGWPlayerStateFlag::ECB_Fire;
}

bool ACharacterPC::NativeCanWeaponChange()
{
	return !( CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_CanWeaponChangeCondition );
}

bool ACharacterPC::IsWeaponChangeFlagOn()
{
	return  CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_WeaponChange;
}

void ACharacterPC::SetWeaponChangeFlag( FlagOnOff Flag )
{
	Flag == FlagOnOff::ON ? CurrentPlayerStateFlag |= ( int32 ) EGWPlayerStateFlag::ECB_WeaponChange : CurrentPlayerStateFlag &= ~( int32 ) EGWPlayerStateFlag::ECB_WeaponChange;
}

bool ACharacterPC::NativeCanReload()
{
	return !( CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_CanReloadCondition );
}

bool ACharacterPC::IsReloadFlagOn()
{
	return CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_Reload;
}

void ACharacterPC::SetReloadFlag( FlagOnOff Flag )
{
	Flag == FlagOnOff::ON ? CurrentPlayerStateFlag |= ( int32 ) EGWPlayerStateFlag::ECB_Reload : CurrentPlayerStateFlag &= ~( int32 ) EGWPlayerStateFlag::ECB_Reload;
}

bool ACharacterPC::NativeCanZoom()
{
	return !( CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_CanZoomCondition );;
}

bool ACharacterPC::IsZoomFlagOn()
{
	return CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_Zoom;
}

void ACharacterPC::SetZoomFlag( FlagOnOff Flag )
{
	Flag == FlagOnOff::ON ? CurrentPlayerStateFlag |= ( int32 ) EGWPlayerStateFlag::ECB_Zoom : CurrentPlayerStateFlag &= ~( int32 ) EGWPlayerStateFlag::ECB_Zoom;
}

bool ACharacterPC::NativeCanWeaponSkill()
{
	return !( CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_CanWeaponSkillCondition );
}

bool ACharacterPC::IsWeaponSkillFlagOn()
{
	return CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_WeaponSkill;
}

void ACharacterPC::SetWeaponSkillFloa( FlagOnOff Flag )
{
	Flag == FlagOnOff::ON ? CurrentPlayerStateFlag |= ( int32 ) EGWPlayerStateFlag::ECB_WeaponSkill : CurrentPlayerStateFlag &= ~( int32 ) EGWPlayerStateFlag::ECB_WeaponSkill;
}

bool ACharacterPC::NativeCanUltraSkill()
{
	return !( CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_CanUltraSkilCondition );
}

bool ACharacterPC::IsUltrasSkillFlagOn()
{
	return CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_UltraSkill;
}

void ACharacterPC::SetUltraSkillFlag( FlagOnOff Flag )
{
	Flag == FlagOnOff::ON ? CurrentPlayerStateFlag |= ( int32 ) EGWPlayerStateFlag::ECB_UltraSkill : CurrentPlayerStateFlag &= ~( int32 ) EGWPlayerStateFlag::ECB_UltraSkill;
}

bool ACharacterPC::NativeCanDashForce()
{
	return !( CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_CanForceDashCondition );
}

bool ACharacterPC::IsDashForceFlagOn()
{
	return CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_ForceDash;
}

void ACharacterPC::SetDashForceFlag( FlagOnOff Flag )
{
	Flag == FlagOnOff::ON ? CurrentPlayerStateFlag |= ( int32 ) EGWPlayerStateFlag::ECB_ForceDash : CurrentPlayerStateFlag &= ~( int32 ) EGWPlayerStateFlag::ECB_ForceDash;
}

bool ACharacterPC::NativeCanDashLoop()
{
	return !( CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_CanLoopDashCondition );
}

bool ACharacterPC::IsDashLoopFlagOn()
{
	return CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_LoopDash;
}

void ACharacterPC::SetDashLoop( FlagOnOff Flag )
{
	Flag == FlagOnOff::ON ? CurrentPlayerStateFlag |= ( int32 ) EGWPlayerStateFlag::ECB_LoopDash : CurrentPlayerStateFlag &= ~( int32 ) EGWPlayerStateFlag::ECB_LoopDash;
}

bool ACharacterPC::NativeCanForceAirJump()
{
	return !( CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_CanForceAirJumpCondition );
}

bool ACharacterPC::IsForceAirJumpFlagOn()
{
	return CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_ForceAirJump;
}

void ACharacterPC::SetForceAirJump( FlagOnOff Flag )
{
	Flag == FlagOnOff::ON ? CurrentPlayerStateFlag |= ( int32 ) EGWPlayerStateFlag::ECB_ForceAirJump : CurrentPlayerStateFlag &= ~( int32 ) EGWPlayerStateFlag::ECB_ForceAirJump;
}

bool ACharacterPC::NativeCanLoopAirJump()
{
	return !( CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_LoopAirJump );
}

bool ACharacterPC::IsJumpLoopFlagOn()
{
	return CurrentPlayerStateFlag & ( int32 ) EGWPlayerStateFlag::ECB_LoopAirJump;
}

void ACharacterPC::SetLoopAirJump( FlagOnOff Flag )
{
	Flag == FlagOnOff::ON ? CurrentPlayerStateFlag |= ( int32 ) EGWPlayerStateFlag::ECB_LoopAirJump : CurrentPlayerStateFlag &= ~( int32 ) EGWPlayerStateFlag::ECB_LoopAirJump;
}

void ACharacterPC::SetPlayerState( EGWPlayerState NewState , EGWPlayerState& PrevState )
{
	uint8 Count = 0;
	uint32 CompareBit = CurrentPlayerStateFlag ;

	while ( CompareBit )
	{
		CompareBit >>= 1;

		Count++;
	}

	PrevState = ( EGWPlayerState ) Count;

	if ( NewState == PrevState ) return;

	if ( NewState == EGWPlayerState::None ) { CurrentPlayerStateFlag = 0; }
	else
	{
		CurrentPlayerStateFlag = 1 << ( ( ( int32 ) NewState ) - 1 );
	}
}

bool ACharacterPC::CanChangePlayerState( EGWPlayerState NewState )
{
	switch ( NewState )
	{
	case EGWPlayerState::None:
		return true;
	case EGWPlayerState::Fire:
		return NativeCanFire();
	case EGWPlayerState::WeaponChange:
		return NativeCanWeaponChange();
	case EGWPlayerState::Reload:
		return NativeCanReload();
	case EGWPlayerState::Zoom:
		return NativeCanZoom();
	case EGWPlayerState::WeaponSkill:
		return NativeCanWeaponSkill();
	case EGWPlayerState::UltraSkill:
		return NativeCanUltraSkill();
	case EGWPlayerState::ForceDash:
		return NativeCanDashForce();
	case EGWPlayerState::LoopDash:
		return NativeCanDashLoop();
	case EGWPlayerState::ForceAirJump:
		return NativeCanForceAirJump();
	case EGWPlayerState::LoopAirJump:
		return NativeCanLoopAirJump();
	default:
		return false;
	}

	return false;
}

void ACharacterPC::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( ACharacterPC , CurrentPlayerStateFlag );
}