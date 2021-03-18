// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMasteryComponent.h"
#include "Actor/Comp/StatManagerComponent.h"


// Sets default values for this component's properties
UCharacterMasteryComponent::UCharacterMasteryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


	// ...

	ActiveSkillIds = TArray<int32>();


}

void UCharacterMasteryComponent::InitComponent( UStatManagerComponent * NewStatManager )
{
	this->StatManager = NewStatManager;
}

TArray<int32> UCharacterMasteryComponent::GetActiveSkillIds() const
{
	return ActiveSkillIds;
}

int32 UCharacterMasteryComponent::GetCurrentSkillPoint() const
{
	return SkillPoint;
}

void UCharacterMasteryComponent::SetSkillPoint( const int32& NewSkillPoint )
{
	SkillPoint = FMath::Clamp( NewSkillPoint , 0 , (int32)MaxSkillPoint );

	if(GetOwnerRole() == ROLE_Authority)
	{
		Client_SetSkillPoint( SkillPoint );
	}
}

void UCharacterMasteryComponent::Client_SetSkillPoint_Implementation( const int32 & NewSkillPoint )
{
	SetSkillPoint( NewSkillPoint );
}

bool UCharacterMasteryComponent::Client_SetSkillPoint_Validate( const int32 & NewSkillPoint )
{
	return true;
}

void UCharacterMasteryComponent::Client_SetActiveMastery_Implementation( const TArray<int32>& MasteryArray )
{
	SetActiveMastery( MasteryArray );
}

bool UCharacterMasteryComponent::Client_SetActiveMastery_Validate( const TArray<int32>& MasteryArray )
{
	return true;
}

void UCharacterMasteryComponent::AddActiveMastery( const uint16& MasteryId )
{
	ActiveSkillIds.Add( MasteryId );
}


// Called when the game starts
void UCharacterMasteryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UCharacterMasteryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterMasteryComponent::SetActiveMastery( const TArray<int32>& MasteryArray )
{

	if ( StatManager == nullptr ) return;

	if( ActiveSkillIds.Num() > 0)
	{
		StatManager->RemoveMasteryDatas( ActiveSkillIds );
	}

	ActiveSkillIds = TArray<int32>();

	for(const int32& Id : MasteryArray)
	{
		ActiveSkillIds.Add( Id );

		//SkillPoint -= (Id % 100);
	}

	if ( GetOwner()->Role == ROLE_Authority )
	{
		StatManager->AddMasteryDatas( ActiveSkillIds );

		Client_SetActiveMastery( MasteryArray );
	}

}
