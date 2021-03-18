// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleManagerBaseComponent.h"

// Sets default values for this component's properties
UModuleManagerBaseComponent::UModuleManagerBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UModuleManagerBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

FGWModuleData UModuleManagerBaseComponent::RemoveModule(int32 SocketNumber )
{
	if( ModuleSlots.Find( SocketNumber )!= nullptr ){

	FGWModuleData RemoveData = *(ModuleSlots.Find( SocketNumber )->ModuleData);

	ModuleSlots.Find( SocketNumber )->ModuleData = nullptr;

	return RemoveData;

	}

	return FGWModuleData();
}

void UModuleManagerBaseComponent::EquipInitModules( TMap<int32 , FGWModuleData> InitModuleDatas )
{
	 for(auto MouduleData : InitModuleDatas )
	 {
		 FGWModuleData Data = FGWModuleData();

		 EquipModule( Data , MouduleData.Key , MouduleData.Value );
	 }
}

void UModuleManagerBaseComponent::CreateModuleSocket( int32 SockeIndex , FModuleSlotData ModuleSlotData )
{

	ModuleSlots.Add( SockeIndex , ModuleSlotData );

}

EModuleEquipState UModuleManagerBaseComponent::EquipModule( FGWModuleData& OldModule , int32 SocketIndex , FGWModuleData ModuleData )
{


	FModuleSlotData SlotData = *ModuleSlots.Find( SocketIndex );

	if ( SlotData.SlotType != ModuleData.ModuleSlotType ) return EModuleEquipState::NotMatch;

	if ( TotalModuleCost - ModuleData.ModuleCost < 0 ) return EModuleEquipState::LackCost;

	if ( SlotData.ModuleData == nullptr )
	{
		*SlotData.ModuleData = ModuleData;

	}
	else
	{
		OldModule = *SlotData.ModuleData;

		*SlotData.ModuleData = ModuleData;
	}

	TotalModuleCost -= ModuleData.ModuleCost;

	return EModuleEquipState::Sueccess;

}

void UModuleManagerBaseComponent::InitModule( FMouleInitParam InitData )
{
	TotalModuleCost = InitData.TotalMouduleCost;

	MaxSockeNumber = InitData.SocketNumber;

	for ( auto& ModuleSlot : InitData.InitModuleSlotInfos )
	{
		CreateModuleSocket( ModuleSlot.Key, ModuleSlot.Value );
	}

}

// Called every frame
void UModuleManagerBaseComponent::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );

	// ...
}
