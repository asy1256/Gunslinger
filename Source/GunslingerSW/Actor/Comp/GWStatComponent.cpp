// Fill out your copyright notice in the Description page of Project Settings.


#include "GWStatComponent.h"

DEFINE_LOG_CATEGORY_STATIC( StatComponent , Log , All );

// Sets default values for this component's properties
UGWStatComponent::UGWStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicated( true );

	SetStatMapping();
	// ...
}

// Called when the game starts
void UGWStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UGWStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGWStatComponent::SetStatMapping() 
{
	StatDataMap = TMap<EGWStatType , FGWStat*>();
}

void UGWStatComponent::SetDefaultStat( double Value , EGWStatType Type )
{
	if ( StatDataMap.Find( Type ) == nullptr )
	{
		UE_LOG( StatComponent , Warning , TEXT( "Stat Type Not Found" ) );
		return;
	}

	FGWStat* Stat = *(StatDataMap.Find( Type ));

	Stat->DefualtValue = Value;
}

void UGWStatComponent::SetStatRangeDatas()
{
	if ( StatRangeTable == nullptr ) 
	{
		UE_LOG( StatComponent , Warning , TEXT( "Table is Empty" ) );
		return;
	}
	for ( const FName& RowName : StatRangeTable->GetRowNames() )
	{
		const FGWStatRangeParam* const RowData = StatRangeTable->FindRow<FGWStatRangeParam>( RowName , FString( "" ) );

		if ( RowData == nullptr ) continue;

        SetStatRange( *RowData );
	}
}

void UGWStatComponent::AddStat( const FAddStatParam& StatParam )
{
	if( StatDataMap.Find( StatParam.StatType ) == nullptr )
	{
		UE_LOG( StatComponent , Warning , TEXT( "Stat Type Not Found" ) );
		return;
	}

	FGWStat* Stat = *( StatDataMap.Find( StatParam.StatType ) );

	FGWStatAdjustment* Adj = nullptr;

	Adj = StatParam.CalculateType == EGWStatCalculateType::Add ? &Stat->Add : &Stat->Multiply;

	Adj->AddValue( StatParam.Value );
}

void UGWStatComponent::SetStatRange( const FGWStatRangeParam& RangeParam )
{
	if ( StatDataMap.Find( RangeParam.OriginType ) == nullptr ) return;

	FGWStat* Stat = *StatDataMap.Find( RangeParam.OriginType );

	Stat->Add.MaxRange = RangeParam.AddMaxRange;
	Stat->Add.MinRange = RangeParam.AddMinRange;
	Stat->Add.SetAdjustmentType( RangeParam.Adjustment );

	Stat->Multiply.MaxRange = RangeParam.MultiplyMaxRange;
	Stat->Multiply.MinRange = RangeParam.MultiplyMinRange;
	Stat->Multiply.SetAdjustmentType( RangeParam.Adjustment );

	Stat->TotalMin = RangeParam.TotalMinRange;
	Stat->TotalMax = RangeParam.ToTalMaxRange;

}

float UGWStatComponent::GetStat( EGWStatType StatType )
{
	if ( StatDataMap.Contains( StatType ) == false ) return 0.0f;

	return ( *StatDataMap.Find( StatType ) )->GetTotalStatValue();
}

float UGWStatComponent::GetAdditionalStat( EGWStatType StatType )
{
	if ( StatDataMap.Contains( StatType ) == false ) return 0.0f;

	return (( *StatDataMap.Find( StatType ) )->Add.AdjValue + ( *StatDataMap.Find( StatType ) )->Multiply.AdjValue ) ;

}

float UGWStatComponent::GetDefaultStat( EGWStatType StatType )
{
	if ( StatDataMap.Contains( StatType ) == false ) return 0.0f;

	return ( *StatDataMap.Find( StatType ) )->DefualtValue;
}

void UGWStatComponent::GetAllStatInfo( TArray<FString>& StatName , TArray<float>& StatValue )
{

	const UEnum* EnumPtr = FindObject<UEnum>( ANY_PACKAGE , TEXT("EGWStatType") , true );

	if ( EnumPtr == nullptr ) return;

	for(auto Stat : StatDataMap)
	{
		StatName.Add( EnumPtr->GetNameStringByIndex( ( int32 ) Stat.Key ) );
		StatValue.Add( GetStat( Stat.Key ) );
	}

}


