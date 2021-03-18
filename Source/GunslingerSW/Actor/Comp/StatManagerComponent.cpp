// Fill out your copyright notice in the Description page of Project Settings.


#include "StatManagerComponent.h"
#include "Actor/Comp/GWStatComponent.h"
#include "Actor/Comp/CharacterMasteryComponent.h"


// Sets default values for this component's properties
UStatManagerComponent::UStatManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	CharacterStat = nullptr;
	WeaponStats.Add( nullptr );
	WeaponStats.Add( nullptr );
	WeaponStats.Add( nullptr );



	// ...
}

// Called when the game starts
void UStatManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UStatManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
bool UStatManagerComponent::IsAllocatedAllComponent()
{
	bool AllAllocated = true;

	AllAllocated = CharacterStat != nullptr && AllAllocated;

	for ( auto stat : WeaponStats )
	{
		AllAllocated = stat != nullptr && AllAllocated;
	};

	return AllAllocated;
}
void UStatManagerComponent::AddStat( FAddStatParam Stat , EGWStatCompType ApplyComponent )
{

	switch ( ApplyComponent )
	{
	case EGWStatCompType::Character:
		if ( CharacterStat == nullptr ) return;
		CharacterStat->AddStat( Stat );
		break;
	case EGWStatCompType::WeaponFirstSlot:
		if ( WeaponStats[ 0 ] == nullptr ) return;
		WeaponStats[ 0 ]->AddStat( Stat );
		break;
	case EGWStatCompType::WeaponSecondSlot:
		if ( WeaponStats[ 1 ] == nullptr ) return;
		WeaponStats[ 1 ]->AddStat( Stat );
		break;
	case EGWStatCompType::WeaponThirdSlot:
		if ( WeaponStats[ 2 ] == nullptr ) return;
		WeaponStats[ 2 ]->AddStat( Stat );
		break;
	case EGWStatCompType::WeaponAll:

		for( UGWStatComponent* StatComp : WeaponStats)
		{
			if ( StatComp == nullptr ) return;
			StatComp->AddStat( Stat );
		}
		break;
	default:
		break;
	}

}

void UStatManagerComponent::AddOptionDatas( int32 SlotIndex , const TArray<int32>& OptionIds ,  EGWAdjustment AdjumentType )
{
	if ( OptionInfoTable == nullptr ) return ;

	EGWStatCompType StatCompType(EGWStatCompType::Character);

	for ( uint16 Row : OptionIds )
	{
		if ( OptionInfoTable->FindRow<FGWItemOptionInfo>( (*FString::FromInt( Row ) ) , FString( "" ) ) == nullptr ) return;

		const FGWItemOptionInfo* const Info = OptionInfoTable->FindRow<FGWItemOptionInfo>( ( *FString::FromInt( Row ) ) , FString( "" ) );

		if ( Info == nullptr ) continue;

		if ( Info->OptionApplyTarget == EGWOptionTarget::Weapon )
		{
			StatCompType = ( EGWStatCompType ) ( SlotIndex + 1 );

		}
		else if ( Info->OptionApplyTarget == EGWOptionTarget::Character )
		{
			StatCompType = EGWStatCompType::Character;
		}

		FAddStatParam NewStat;

		NewStat.CalculateType = Info->CalculateType;
		NewStat.StatType = Info->OptionType;
		NewStat.Value = AdjumentType == EGWAdjustment::Positive ? Info->Value_1 : ( Info->Value_1*-1 );

		AddStat( NewStat , StatCompType );
	}
}

void UStatManagerComponent::AddMasteryDatas( const TArray<int32>& MasteryIds )
{

	if ( MasteryTable == nullptr ) return;

	for ( int32 id : MasteryIds )
	{

		if ( MasteryTable->FindRow<FGWMasteryDataParam>( FName( *FString::FromInt( id ) ) , FString( "" ) ) == nullptr ) return;

		const FGWMasteryDataParam* const Info = MasteryTable->FindRow<FGWMasteryDataParam>( ( *FString::FromInt( id ) ) , FString( "" ) );

		if ( Info == nullptr ) continue;

		EGWStatCompType Type = Info->ApplyTarget == EGWMasteryTarget::Character ? EGWStatCompType::Character : EGWStatCompType::WeaponAll;

		AddStat( Info->StatParam , Type );
	}

}

void UStatManagerComponent::RemoveMasteryDatas( const TArray<int32>& MasteryIds )
{
	if ( MasteryTable == nullptr ) return;

	for ( int32 id : MasteryIds )
	{
		if ( MasteryTable->FindRow<FGWMasteryDataParam>( FName( *FString::FromInt(id) ) , FString( "" ) ) == nullptr ) return;

		const FGWMasteryDataParam* const Info = MasteryTable->FindRow<FGWMasteryDataParam>( ( *FString::FromInt( id ) ) , FString( "" ) );

		if ( Info == nullptr ) continue;

		FAddStatParam RemoveStatParm = Info->StatParam;

		RemoveStatParm.Value = RemoveStatParm.Value*-1;

		EGWStatCompType Type = Info->ApplyTarget == EGWMasteryTarget::Character ? EGWStatCompType::Character : EGWStatCompType::WeaponAll;

		AddStat( RemoveStatParm , Type );
	}
}

void UStatManagerComponent::SetStatComponent( EGWStatCompType StatCompType , UGWStatComponent * StatComp )
{

	switch ( StatCompType )
	{
	case EGWStatCompType::Character:
		CharacterStat = StatComp;
		break;
	case EGWStatCompType::WeaponFirstSlot:
		WeaponStats[ 0 ] = StatComp;
		break;
	case EGWStatCompType::WeaponSecondSlot:
		WeaponStats[ 1 ] = StatComp;
		break;
	case EGWStatCompType::WeaponThirdSlot:
		WeaponStats[ 2 ] = StatComp;
		break;
	default:
		break;
	}

	if( IsAllocatedAllComponent() == true )
	{
		AllStatCompAllocated.Broadcast();
		
		UE_LOG( LogTemp , Warning , TEXT( "StatManagerComponent : AllStatComponentAllocated Complete" ) );
	}
}

