// Fill out your copyright notice in the Description page of Project Settings.

#include "StatusEffectBase.h"
#include "SkillInterface.h"

#include "StatusEffectManager.h"

//#include "GameBlueprintFunctionLibrary.h"

#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Net
#include "Net/UnrealNetwork.h"

/* Define a log category for error messages */
DEFINE_LOG_CATEGORY_STATIC(StatusEffectBase, Log, All);

// Sets default values for this component's properties
UStatusEffectBase::UStatusEffectBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bReplicates = true;
	MaxSkillDuration = 99.0f;

	PrimaryComponentTick.bAllowTickOnDedicatedServer = true;


	UE_LOG(StatusEffectBase, Warning, TEXT("UStatusEffectBase()"));

}


// Called every frame
void UStatusEffectBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (GetOwnerRole() == ROLE_Authority)
	{
		UpdateTime(DeltaTime);
	}
}


void UStatusEffectBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStatusEffectBase, StackCount);

	DOREPLIFETIME(UStatusEffectBase, DamageInstigator);

	DOREPLIFETIME(UStatusEffectBase, SkillDuration);
}


bool UStatusEffectBase::HasAuthority()
{
	
	AActor* OwnerActor = GetOwner();

	if (OwnerActor)
	{
		return OwnerActor->HasAuthority();
	}
	return false;
}


void UStatusEffectBase::UpdateTime(float delta)
{

	if (HasAuthority())
	{
		if (GetOwner()->IsValidLowLevel())
		{
			AActor* OwnerActor = GetOwner();
			APawn* InstigatorPawn = OwnerActor->GetInstigator();
			if (OwnerActor && InstigatorPawn->GetClass()->ImplementsInterface(USkillInterface::StaticClass()))
			{
				const bool IsDead = ISkillInterface::Execute_GetIsDead(InstigatorPawn);
				if (!IsDead)
				{
					if (!StatusEffectInfo.Infinite)
					{
						SkillDuration = UKismetMathLibrary::FClamp(SkillDuration + delta, 0.0f, MaxSkillDuration);
						//UE_LOG(StatusEffectBase, Warning, TEXT("duration : %f"), SkillDuration);
					}
					else
					{
						UE_LOG(StatusEffectBase, Warning, TEXT("Infinite"));
					}
				}
				else
				{
					SkillDuration = MaxSkillDuration;
				}
			}
		}
		else
		{
			SkillDuration = MaxSkillDuration;
		}

		OnRep_SkillDuration();
	}

	//UE_LOG(StatusEffectBase, Warning, TEXT("UpdateTime(%f/%f)"), SkillDuration, MaxSkillDuration);

}

void UStatusEffectBase::InitStatusEffect(const FString& SkillEffectId)
{
	StatusEffectId = SkillEffectId;

	UE_LOG(StatusEffectBase, Warning, TEXT("Init Status Effect : %s"), *SkillEffectId);

	/*
	UDataManager* DataManager = UGameBlueprintFunctionLibrary::GetDataManager();
	if (DataManager)
	{
		FST_StatusEffectInfo OutInfo;
		if (DataManager->GetStatusEffectInfo(OutInfo, SkillEffectId))
		{
			StatusEffectInfo = OutInfo;

			InitData();

			StackCount = 1;

			ResetTimer();
		}
		else
		{
			UE_LOG(StatusEffectBase, Warning, TEXT("Not Table Info"));
		}
	}

	*/
}

void UStatusEffectBase::SetInstigator(AController* Instigator)
{
	if (HasAuthority())
	{
		DamageInstigator = Instigator;
	}
}

// Add
void UStatusEffectBase::AddEffect(const FString& SkillEffectId)
{
	if (HasAuthority())
	{
		Multi_SetStatusEffectData(SkillEffectId);

		StackCount = UKismetMathLibrary::Clamp(StackCount + 1, 0, MaxStackCount);

		Multi_ResetTimer();

		// Call override Function
		StackEffect(StackCount);

		UE_LOG(StatusEffectBase, Warning, TEXT("Add Status Effect : %d"), StackCount);
	}
}

// Overwrite
void UStatusEffectBase::OverwriteEffect(const FString& SkillEffectId)
{
	if (HasAuthority())
	{
		Multi_SetStatusEffectData(SkillEffectId);

		UE_LOG(StatusEffectBase, Warning, TEXT("Overwrite Status Effect"));

		Multi_ResetTimer();
	}
}

void UStatusEffectBase::ShowEffect()
{
	if (CurrentPS && CurrentPS->IsValidLowLevel())
	{
		CurrentPS->Activate(true);
	}
	else
	{
		AActor* OwnerActor = GetOwner();
		APawn* InstigatorPawn = OwnerActor->GetInstigator();
		if (OwnerActor && InstigatorPawn->GetClass()->ImplementsInterface(USkillInterface::StaticClass()))
		{
			USkeletalMeshComponent* Mesh = ISkillInterface::Execute_GetOwnerMesh(InstigatorPawn);

			if (Mesh && Mesh->IsValidLowLevel())
			{
				CurrentPS = UGameplayStatics::SpawnEmitterAttached(
					StatusEffectInfo.ParticleEmitter,
					Mesh,
					StatusEffectInfo.EmitterSocketName,
					StatusEffectInfo.EmitterLocOffset,
					FRotator::ZeroRotator,
					FVector(1, 1, 1),
					EAttachLocation::Type::SnapToTarget,
					true);

			}

		}
	}
}

void UStatusEffectBase::EffectDestroy()
{
	if (CurrentPS && CurrentPS->IsValidLowLevel())
	{
		CurrentPS->Deactivate();
	}
}


void UStatusEffectBase::SetStatusEffectData(const FString& SkillEffectId)
{	
	/*
	UDataManager* DataManager = UGameBlueprintFunctionLibrary::GetDataManager();
	if (DataManager)
	{
		FST_StatusEffectInfo OutInfo;
		if (DataManager->GetStatusEffectInfo(OutInfo, SkillEffectId))
		{
			StatusEffectInfo = OutInfo;

			InitData();
		}
	}
	*/
}

void UStatusEffectBase::ResetTimer()
{
	UE_LOG(StatusEffectBase, Warning, TEXT("ResetTimer()"));

	ApplyStatusEffect();

	const float Interval = StatusEffectInfo.TickInterval;
	if (bool IsLooping = Interval > 0)
	{
		if (!GetOwner()->GetWorldTimerManager().IsTimerActive(EffectTimerHandle))
		{
			GetOwner()->GetWorldTimerManager().SetTimer(EffectTimerHandle, this, &UStatusEffectBase::ApplyStatusEffect, Interval, IsLooping, 0.0f);
		}
	}

	SkillDuration = 0.0f;
}


void UStatusEffectBase::InitData()
{
	UE_LOG(StatusEffectBase, Warning, TEXT("InitData()"));

	MaxSkillDuration = StatusEffectInfo.Duration;
	AffectType = StatusEffectInfo.AffectType;
	MaxStackCount = StatusEffectInfo.StackCount;

}

void UStatusEffectBase::ApplyStatusEffect()
{
	ShowEffect();

	if (HasAuthority())
	{
		ApplyEffect();
	}
}

void UStatusEffectBase::EndStatusEffect()
{
	if (!IsEffectEnd)
	{
		IsEffectEnd = true;
		GetOwner()->GetWorldTimerManager().ClearTimer(EffectTimerHandle);
		UE_LOG(StatusEffectBase, Warning, TEXT("Status Effect End"));

		if (HasAuthority())
		{
			Multi_EffectDestroy();

			UStatusEffectManager* Manager = Cast<UStatusEffectManager>(GetOwner()->GetComponentByClass(UStatusEffectManager::StaticClass()));
			if (Manager && Manager->IsValidLowLevel())
			{
				Manager->RemoveStatusEffect(AffectType);
			}

			CancelEffect();

			StackCount = 0;

			DestroyComponent();
		}
	}
}




void UStatusEffectBase::OnRep_SkillDuration()
{
	if (HasAuthority())
	{
		//UE_LOG(StatusEffectBase, Warning, TEXT("Skill Duration : %f"), SkillDuration);

		if (SkillDuration >= MaxSkillDuration)
		{
			EndStatusEffect();
		}
	}
}





// ########  Server Logic ###############
void UStatusEffectBase::Server_SetInstigator_Implementation(AController* Instigator)
{
	SetInstigator(Instigator);
}

bool UStatusEffectBase::Server_SetInstigator_Validate(AController* Instigator)
{
	return true;
}

void UStatusEffectBase::Server_AddEffect_Implementation(const FString& SkillEffectId)
{
	AddEffect(SkillEffectId);
}

bool UStatusEffectBase::Server_AddEffect_Validate(const FString& SkillEffectId)
{
	return true;
}

void UStatusEffectBase::Server_OverwriteEffect_Implementation(const FString& SkillEffectId)
{
	OverwriteEffect(SkillEffectId);
}

bool UStatusEffectBase::Server_OverwriteEffect_Validate(const FString& SkillEffectId)
{
	return true;
}



// ########  Multicast Logic ###############
void UStatusEffectBase::Multi_EffectDestroy_Implementation()
{
	EffectDestroy();
}


void UStatusEffectBase::Multi_ResetTimer_Implementation()
{
	ResetTimer();
}


void UStatusEffectBase::Multi_SetStatusEffectData_Implementation(const FString& SkillEffectId)
{
	SetStatusEffectData(SkillEffectId);
}


void UStatusEffectBase::Multi_InitStatusEffect_Implementation(const FString& SkillEffectId)
{
	InitStatusEffect(SkillEffectId);
}