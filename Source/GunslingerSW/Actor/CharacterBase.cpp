// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "GunslingerSW.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GP2GameInstance.h"


// Sets default values
ACharacterBase::ACharacterBase() : Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TeamId = FGenericTeamId(0);
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterBase::BeginDestroy()
{
	Super::BeginDestroy();
}

void ACharacterBase::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
	Super::EndPlay( EndPlayReason );
}

void ACharacterBase::Tick( float DeltaSeconds )
{
	QUICK_SCOPE_CYCLE_COUNTER( STAT_ACharacterBase );

	Super::Tick( DeltaSeconds );

	// 기본적인 업데이트
}

void ACharacterBase::AsyncLoadCharacterMesh(int32 NewIndex)
{
	AsyncLoadIndex = NewIndex;
	UGP2GameInstance* GP2GameInstance = Cast<UGP2GameInstance>(GetGameInstance());

	if ( GP2GameInstance )
	{
		GP2GameInstance->AssetLoader.RequestAsyncLoad(GP2GameInstance->CharacterAssets[AsyncLoadIndex],
			FStreamableDelegate::CreateUObject(this, &ACharacterBase::AsyncLoadCompletedCharacterMesh));
	}

}

void ACharacterBase::AsyncLoadCompletedCharacterMesh_Implementation()
{
	GP2LOG("AsyncLoadCompletedCharacterMesh");

	UGP2GameInstance* GP2GameInstance = Cast<UGP2GameInstance>(GetGameInstance());

	if ( GP2GameInstance )
	{
		TAssetPtr<USkeletalMesh> NewCharacter(GP2GameInstance->CharacterAssets[AsyncLoadIndex]);

		if ( NewCharacter )
		{
			GetMesh()->SetSkeletalMesh(NewCharacter.Get());

			CharacterIndex = AsyncLoadIndex;

			CharacterLoadCompleted.Broadcast(AsyncLoadIndex);
		}
	}
}