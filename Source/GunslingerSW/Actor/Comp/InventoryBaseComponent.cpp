// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryBaseComponent.h"
//net
#include "Net/UnrealNetwork.h"
#include "Actor/Comp/StatManagerComponent.h"

/* Define a log category for error messages */
DEFINE_LOG_CATEGORY_STATIC( InventoryBaseComponent , Log , All );

// Sets default values for this component's properties
UInventoryBaseComponent::UInventoryBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bReplicates = true;

	WeaponInven = FInventory();

	ArmorInven = FInventory();

	ModuleInven = FInventory();

	CraftMaterialInven = FInventory();

	MiscInven = FInventory();

	InventoryAll = TArray<FInventory*>();

	InventoryAll.Add( &WeaponInven );
	InventoryAll.Add( &ArmorInven );
	InventoryAll.Add( &ModuleInven );
	InventoryAll.Add( &CraftMaterialInven );
	InventoryAll.Add( &MiscInven );

	InventoryMap = TMap<EGWItemType , FInventory* >();

	InventoryMap.Add( EGWItemType::Weapon , &WeaponInven );
	InventoryMap.Add( EGWItemType::Armor , &ArmorInven );
	InventoryMap.Add( EGWItemType::WpModule , &ModuleInven );
	InventoryMap.Add( EGWItemType::Material , &CraftMaterialInven );

	Gold = 0;

	// ...
}
// Called when the game starts
void UInventoryBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}
// Called every frame
void UInventoryBaseComponent::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );

	// ...
}

void UInventoryBaseComponent::AllClearInventory()
{
	WeaponInven.InventoryItems.Empty();
	ArmorInven.InventoryItems.Empty();
	ModuleInven.InventoryItems.Empty();
	CraftMaterialInven.InventoryItems.Empty();
	MiscInven.InventoryItems.Empty();
}

void UInventoryBaseComponent::CreateWeaponEquipment( TArray<EGWItemSubType> WeaponEquipment )
{

	WearingWeapon = FWearingIventory( &WeaponInven , WeaponEquipment );
}

void UInventoryBaseComponent::CreateArmorEquipment( TArray<EGWItemSubType> ArmorEquipment )
{

	WearingArmor = FWearingIventory( &ArmorInven , ArmorEquipment );
}

bool UInventoryBaseComponent::GetItemInfo( FItemData ItemDtat , struct FGWItemInfo& ItemInfo )
{
	return true;
}

FInventory& UInventoryBaseComponent::GetIventoryByItemType( EGWItemType ItemType )
{
	if ( InventoryMap.Find( ItemType ) == nullptr ) return MiscInven;

	FInventory* Inven = *InventoryMap.Find( ItemType );

	return *Inven;

}

FWearingIventory& UInventoryBaseComponent::GetEquipInvenByItemType( EGWItemType ItemType )
{
	switch ( ItemType )
	{
	case EGWItemType::Weapon:
		return  WearingWeapon;
		break;
	case EGWItemType::Armor:
		return  WearingArmor;
		break;
	default:
		break;
	}

	return WearingWeapon;
}

bool UInventoryBaseComponent::AddItem( FItemData NewItem )
{
	if ( NewItem.ItemType == EGWItemType::None ) return false;

	FInventory& Inven = GetIventoryByItemType( NewItem.ItemType );

	if ( Inven.InventoryItems.Num() == InventoryMaxSize ) return false;

	Inven.InventoryItems.Add( NewItem.Uid , NewItem );

	return true;
}

bool UInventoryBaseComponent::RemoveItem( FItemData RemoveItem )
{
	if ( RemoveItem.ItemType == EGWItemType::None ) return false;

	FInventory& Inven = GetIventoryByItemType( RemoveItem.ItemType );

	FItemData* RemovedItem = Inven.InventoryItems.Find( RemoveItem.Uid );

	if ( RemovedItem == nullptr ) return false;

	Inven.InventoryItems.Remove( ( *RemovedItem ).Uid );

	Inven.InventoryItems.Compact();
	Inven.InventoryItems.Shrink();

	return true;
}

int32 UInventoryBaseComponent::EquipItem( FItemData Item , EGWItemSubType ItemSubType , int32& SlotIndex )
{

	FItemData* ItemData = GetIventoryByItemType( Item.ItemType ).InventoryItems.Find( Item.Uid );

	if ( ItemData == nullptr )
	{
		UE_LOG( InventoryBaseComponent , Warning , TEXT( "Item Not Find" ) );
		return -1;
	}

	FWearingIventory& WearingInven = GetEquipInvenByItemType( Item.ItemType );

	int32 OldItemUid = -1;

	int32* ItemUid = WearingInven.Slot.Find( ItemSubType );

	if ( ItemUid == nullptr )
	{
		UE_LOG( InventoryBaseComponent , Warning , TEXT( "ItemCan'tEquipt" ) );
		return -1;
	}

	OldItemUid = *ItemUid;

	if ( OldItemUid != -1 )
	{
		FItemData* OldItem = WearingInven.RefInven->InventoryItems.Find( OldItemUid );

		UnEquipItem( *OldItem , ItemSubType );

	}

	*ItemUid = ItemData->Uid;

	ItemData->bIsEquiped = true;

	/*
	int32 Index = 0;

	for ( auto& Pair : WearingInven.Slot )
	{
		Pair.Key == ItemSubType ? SlotIndex = Index : Index++;
	}

	if ( StatManager != nullptr )
	{
		StatManager->AddOptionDatas( ( uint8 ) SlotIndex , GetAllOptionInItem( *ItemData ) , EGWAdjustment::Positive );

		if(GetMoudulesInItem( Item ).Num() > 0)
		{
			for(auto& ItemData : GetMoudulesInItem( Item ))
			{
					StatManager->AddOptionDatas( ( uint8 ) SlotIndex , ItemData.OptionIds , EGWAdjustment::Positive );
			}
		}

	}
	*/
	return OldItemUid;
}


int32 UInventoryBaseComponent::UnEquipItem( FItemData Item , EGWItemSubType ItemSubType )
{

	FItemData* ItemData = GetIventoryByItemType( Item.ItemType ).InventoryItems.Find( Item.Uid );

	if ( ItemData == nullptr ) return -1;

	FWearingIventory& WearingInven = GetEquipInvenByItemType( Item.ItemType );

	int32* ItemUid = WearingInven.Slot.Find( ItemSubType );

	ItemData->bIsEquiped = false;

	uint8 Index = 0;

  /*
	for ( auto& Pair : WearingInven.Slot )
	{
		if ( Pair.Key != ItemSubType ) Index++;
	}
	if ( StatManager != nullptr )
	{
		StatManager->AddOptionDatas( Index , GetAllOptionInItem( *ItemData ) , EGWAdjustment::Negative );

		if ( GetMoudulesInItem( Item ).Num() > 0 )
		{
			for ( auto& ItemData : GetMoudulesInItem( Item ) )
			{
				StatManager->AddOptionDatas( Index , ItemData.OptionIds , EGWAdjustment::Negative );
			}
		}
	}

	*/
	*WearingInven.Slot.Find( ItemSubType ) = -1;

	return ItemData->Uid;
}


int32 UInventoryBaseComponent::EquipModule( FItemData ParentItem , int32 ParentModuleSlot , FItemData Module )
{

	FItemData* ParentData = GetIventoryByItemType( ParentItem.ItemType ).InventoryItems.Find( ParentItem.Uid );

	FItemData* ModuleData = GetIventoryByItemType( Module.ItemType ).InventoryItems.Find( Module.Uid );

	if ( ParentData == nullptr && ModuleData == nullptr ) return -1;

	if ( ParentData->ModuleUids.IsValidIndex( ParentModuleSlot ) == false ) return -1;

	/*
	if (CheckCost( *ParentData , *ModuleData ) == false)
	{
		UE_LOG( InventoryBaseComponent , Warning , TEXT( "CostIsFull" ) );
		return -1;
	}
	*/

	int32 OldModule = ParentData->ModuleUids[ ParentModuleSlot ];

	if ( OldModule != 0 )
	{
		FItemData* OloModuleData = ModuleInven.InventoryItems.Find( OldModule );
		if ( OloModuleData != nullptr )
		{
			UnEquipModule( *OloModuleData , ParentModuleSlot );
		}
	}

	ParentData->ModuleUids[ ParentModuleSlot ] = ModuleData->Uid;

	/*
	if ( StatManager != nullptr && ParentData->bIsEquiped == true )
	{
		FWearingIventory& WearingInven = GetEquipInvenByItemType( ParentData->ItemType );

		uint8 Index = 0;

		for ( auto& Pair : WearingInven.Slot )
		{
			if ( Pair.Value != ParentData->Uid ) Index++;
		}

		StatManager->AddOptionDatas( Index , GetAllOptionInItem( *ModuleData ) , EGWAdjustment::Positive );
	}
	*/
	ModuleData->bIsEquiped = true;

	return OldModule;

}

int32 UInventoryBaseComponent::UnEquipModule( FItemData ParentItem , int32 ParentModuleSlot )
{
	FItemData* ParentData = GetIventoryByItemType( ParentItem.ItemType ).InventoryItems.Find( ParentItem.Uid );

	if ( ParentData == nullptr ) return -1;

	if ( ParentData->ModuleUids.IsValidIndex( ParentModuleSlot ) == false ) return -1;

	int32 OldModule = ParentData->ModuleUids[ ParentModuleSlot ];

	if ( OldModule == 0 ) return -1;

	FItemData* ItemData = ModuleInven.InventoryItems.Find( OldModule );

	if ( ItemData == nullptr ) return -1;

	ItemData->bIsEquiped = false;

	ParentData->ModuleUids[ ParentModuleSlot ] = 0;

	/*
	if ( StatManager != nullptr && ParentData->bIsEquiped == true )
	{
		FWearingIventory& WearingInven = GetEquipInvenByItemType( ParentData->ItemType );

		uint8 Index = 0;

		for ( auto& Pair : WearingInven.Slot )
		{
			if ( Pair.Value != ParentData->Uid ) Index++;
		}

		StatManager->AddOptionDatas( Index , GetAllOptionInItem( *ItemData ) , EGWAdjustment::Negative );
	}
	*/
	return OldModule;
}

TArray<FItemData> UInventoryBaseComponent::GetInventoryItems( EInventoryType InvenType )
{
	FInventory* Inven = nullptr;
	TArray<FItemData> Items = TArray<FItemData>();

	switch ( InvenType )
	{
	case EInventoryType::Weapon:
		Inven = &WeaponInven;
		break;
	case EInventoryType::Armor:
		Inven = &ArmorInven;
		break;
	case EInventoryType::Module:
		Inven = &ModuleInven;
		break;
	case EInventoryType::CraftMaterial:
		Inven = &CraftMaterialInven;
		break;
	case EInventoryType::Misc:
		Inven = &MiscInven;
		break;
	default:
		Inven = &MiscInven;
		break;
	}

	for ( TPair<int32 , FItemData> Item : Inven->InventoryItems )
	{
		Items.Add( Item.Value );
	}

	return Items;
}

TArray<FItemData> UInventoryBaseComponent::GetWeraringInvenItems( EWearingInvenType InvenType )
{
	TArray<FItemData> WearingItems = TArray<FItemData>();
	FWearingIventory* WearingInven = nullptr;
	FInventory* ItemInven = nullptr;

	switch ( InvenType )
	{
	case EWearingInvenType::Weapon:
		WearingInven = &WearingWeapon;
		ItemInven = &WeaponInven;
		break;
	case EWearingInvenType::Armor:
		WearingInven = &WearingArmor;
		ItemInven = &ArmorInven;
		break;
	default:
		break;
	}

	if ( WearingInven == nullptr && ItemInven == nullptr ) return WearingItems;

	for ( TPair<EGWItemSubType , int32> Uid : WearingInven->Slot )
	{
		if ( Uid.Value != -1 )
		{
			FItemData* Item = ItemInven->InventoryItems.Find( Uid.Value );

			if ( Item != nullptr ) WearingItems.Add( *Item );
		}
		else
		{
			WearingItems.Add( FItemData() );
		}
	}

	return WearingItems;
}

FWearingIventory UInventoryBaseComponent::GetWeraringInven( EWearingInvenType InvenType )
{
	FWearingIventory* WearingInven = nullptr;

	switch ( InvenType )
	{
	case EWearingInvenType::Weapon:
		WearingInven = &WearingWeapon;
		break;
	case EWearingInvenType::Armor:
		WearingInven = &WearingArmor;
		break;
	default:
		WearingInven = &WearingWeapon;
		break;
	}

	return *WearingInven;
}

TArray<FItemData> UInventoryBaseComponent::GetMoudulesInItem( FItemData ParentItem )
{
	TArray<FItemData> Modules = TArray<FItemData>();
	FInventory* ItemInven = &ModuleInven;

	if ( ItemInven != nullptr )
	{
		for ( int32 ModuleUid : ParentItem.ModuleUids )
		{
			if ( ModuleUid != 0 )
			{

				FItemData* Item = ItemInven->InventoryItems.Find( ModuleUid );

				if ( Item != nullptr ) Modules.Add( *Item );

			}
			else
			{
				Modules.Add( FItemData() );
			}

		}
	}

	return Modules;
}

bool UInventoryBaseComponent::GetItemFromUid( int32 Uid , FItemData& Item ) const
{

	FItemData* GetItem = nullptr;

	for ( FInventory* Inven : InventoryAll )
	{
		GetItem = Inven->InventoryItems.Find( Uid );

		if ( GetItem != nullptr )
		{
			Item = *GetItem;

			return true;
		}
	}

	return false;
}

int32 UInventoryBaseComponent::GetInventoryMaxSize() const
{
	return InventoryMaxSize;
}

int32 UInventoryBaseComponent::GetItemAmountInInventory(EInventoryType InvenType )
{
	const int32 ItemNum = GetInventoryItems( InvenType ).Num();

	return ItemNum;
}

void UInventoryBaseComponent::SetEquipInven( EWearingInvenType InvenType , TArray<EGWItemSubType> ItemSubTypes , TArray<FItemData> ItemDatas )
{

	switch ( InvenType )
	{
	case EWearingInvenType::Weapon:
		{
			WearingWeapon = FWearingIventory();

			for( uint16 i = 0 ;i< ItemSubTypes.Num(); i++ )
			{
				WeaponInven.InventoryItems.Add( ItemDatas[i].Uid , ItemDatas[i] );

				WearingWeapon.Slot.Add( ItemSubTypes[ i ] , ItemDatas[i].Uid );
			}

			WearingWeapon.RefInven = &WeaponInven;
		}
		break;
	case EWearingInvenType::Armor:
		{
			WearingArmor = FWearingIventory();

			WearingWeapon.RefInven = &ArmorInven;

		}
		break;
	default:
		break;
	}

	
}

void UInventoryBaseComponent::SetStatManager( class UStatManagerComponent* NewStatManager )
{
	this->StatManager = NewStatManager;

}

bool UInventoryBaseComponent::CheckCost_Implementation( FItemData ParentItem , FItemData ModuleItem )
{
	return true;
}


const TArray<int32> UInventoryBaseComponent::GetAllOptionInItem( const FItemData & Item )
{
	TArray<int32> Options = TArray<int32>();

	for(int32 Option : Item.OptionIds)
	{
		Options.Add( Option );
	}

    for(FItemData Module : GetMoudulesInItem( Item ))
	{
		for( int32 Option : Module.OptionIds )
		{
			Options.Add( Option );
		}
	}
  
	return Options;
}

void UInventoryBaseComponent::Server_SetGold_Implementation( int32 NewGold )
{
	Gold = NewGold;

	Client_SetGold( Gold );
}

bool UInventoryBaseComponent::Server_SetGold_Validate( int32 NewGold )
{
	return true;
}

void UInventoryBaseComponent::Client_SetGold_Implementation( int32 ServerGold )
{
	Gold = ServerGold;
}

bool UInventoryBaseComponent::Client_SetGold_Validate( int32 ServerGold )
{
	return true;
}

void UInventoryBaseComponent::Server_AddItem_Implementation( FItemData NewItem )
{
	AddItem( NewItem );

	Client_AddItem( NewItem );
}

bool UInventoryBaseComponent::Server_AddItem_Validate( FItemData NewItem )
{
	return true;
}

void UInventoryBaseComponent::Server_AddItemArray_Implementation( const TArray<FItemData>& NewItems )
{

	for( FItemData Item : NewItems )
	{
		AddItem( Item );
	}

	Client_AddItemArray( NewItems );

}

bool UInventoryBaseComponent::Server_AddItemArray_Validate( const TArray<FItemData>& NewItems )
{
	return true;
}

void UInventoryBaseComponent::Server_RemoveItemArray_Implementation( const TArray<FItemData>& RemoveItems )
{

	for(FItemData Item : RemoveItems )
	{
		RemoveItem( Item );
	}

}

bool UInventoryBaseComponent::Server_RemoveItemArray_Validate( const TArray<FItemData>& RemoveItems )
{
	return true;
}

void UInventoryBaseComponent::Server_RemoveItem_Implementation( FItemData RemoveItem )
{
	this->RemoveItem( RemoveItem );

	Client_RemoveItem( RemoveItem );
}

bool UInventoryBaseComponent::Server_RemoveItem_Validate( FItemData RemoveItem )
{
	return true;
}

void UInventoryBaseComponent::Server_EquipItem_Implementation( FItemData Item , EGWItemSubType ItemSubType , int32 SlotIndex )
{

	Client_EquipItem( Item , ItemSubType , SlotIndex );

	EquipItem( Item , ItemSubType , SlotIndex );
}

bool UInventoryBaseComponent::Server_EquipItem_Validate( FItemData Item , EGWItemSubType ItemSubType , int32 SlotIndex )
{
	return true;
}

void UInventoryBaseComponent::Server_UnEquipItem_Implementation( FItemData Item , EGWItemSubType ItemSubType )
{

	Client_UnEquipItem( Item , ItemSubType );

	UnEquipItem( Item , ItemSubType );
}

bool UInventoryBaseComponent::Server_UnEquipItem_Validate( FItemData Item , EGWItemSubType ItemSubType )
{
	return true;
}

void UInventoryBaseComponent::Server_EquipModule_Implementation( FItemData ParentItem , int32 ParentModuleSlot , FItemData Module )
{
	Client_EquipModule( ParentItem , ParentModuleSlot , Module );

	EquipModule( ParentItem , ParentModuleSlot , Module );
}

bool UInventoryBaseComponent::Server_EquipModule_Validate( FItemData ParentItem , int32 ParentModuleSlot , FItemData Module )
{
	return true;
}

void UInventoryBaseComponent::Server_UnEquipModule_Implementation( FItemData ParentItem , int32 ParentModuleSlot )
{
	Client_UnEquipModule( ParentItem , ParentModuleSlot );

	UnEquipModule( ParentItem , ParentModuleSlot );
}

bool UInventoryBaseComponent::Server_UnEquipModule_Validate( FItemData ParentItem , int32 ParentModuleSlot )
{
	return true;
}

void UInventoryBaseComponent::Server_SetEquipInven_Implementation( EWearingInvenType InvenType , const TArray<EGWItemSubType>& ItemSubTypes , const TArray<FItemData>& ItemDatas )
{
	SetEquipInven( InvenType , ItemSubTypes , ItemDatas );

	Client_SetEquipInven( InvenType , ItemSubTypes , ItemDatas );
}

bool UInventoryBaseComponent::Server_SetEquipInven_Validate( EWearingInvenType InvenType , const TArray<EGWItemSubType>& ItemSubTypes , const TArray<FItemData>& ItemDatas )
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UInventoryBaseComponent::Client_AddItem_Implementation( FItemData NewItem )
{
	AddItem( NewItem );

	AddItemCallBack.Broadcast( NewItem );

}

bool UInventoryBaseComponent::Client_AddItem_Validate( FItemData NewItem )
{
	return true;
}

void UInventoryBaseComponent::Client_AddItemArray_Implementation( const TArray<FItemData>& NewItems )
{

	for ( FItemData Item : NewItems )
	{
		AddItem( Item );
	}

	AddItemArrayCallBack.Broadcast( NewItems );

}

bool UInventoryBaseComponent::Client_AddItemArray_Validate( const TArray<FItemData>& NewItems )
{
	return true;
}

void UInventoryBaseComponent::Client_RemoveItem_Implementation( FItemData RemoveItem )
{
	this->RemoveItem( RemoveItem );

	RemoveItemCallBack.Broadcast( RemoveItem );
}

bool UInventoryBaseComponent::Client_RemoveItem_Validate( FItemData RemoveItem )
{
	return true;
}

void UInventoryBaseComponent::Client_RemoveItemArray_Implementation( const TArray<FItemData>& RemoveItems )
{
	for ( FItemData Item : RemoveItems )
	{
		RemoveItem( Item );
	}

	RemoveItemArrayCallBack.Broadcast( RemoveItems );

}

bool UInventoryBaseComponent::Client_RemoveItemArray_Validate( const TArray<FItemData>& RemoveItems )
{
	return true;
}

void UInventoryBaseComponent::Client_EquipItem_Implementation( FItemData Item , EGWItemSubType ItemSubType , int32 SlotIndex )
{
	EquipItem( Item , ItemSubType , SlotIndex );

	EquipItemCallBack.Broadcast( Item , ItemSubType , SlotIndex );
}

bool UInventoryBaseComponent::Client_EquipItem_Validate( FItemData Item , EGWItemSubType ItemSubType , int32 SlotIndex )
{
	return true;
}


void UInventoryBaseComponent::Client_UnEquipItem_Implementation( FItemData Item , EGWItemSubType ItemSubType )
{
	UnEquipItem( Item , ItemSubType );

	UnEquipItemCallBack.Broadcast( Item , ItemSubType );
}

bool UInventoryBaseComponent::Client_UnEquipItem_Validate( FItemData Item , EGWItemSubType ItemSubType )
{

	return true;
}

void UInventoryBaseComponent::Client_EquipModule_Implementation( FItemData ParentItem , int32 ParentModuleSlot , FItemData Module )
{
	EquipModule( ParentItem , ParentModuleSlot , Module );

	EquipModuleCallBack.Broadcast( ParentItem , ParentModuleSlot , Module );
}


bool UInventoryBaseComponent::Client_EquipModule_Validate( FItemData ParentItem , int32 ParentModuleSlot , FItemData Module )
{
	return true;
}

void UInventoryBaseComponent::Client_UnEquipModule_Implementation( FItemData ParentItem , int32 ParentModuleSlot )
{
	UnEquipModule( ParentItem , ParentModuleSlot );

	UnEquipModuleCallBack.Broadcast( ParentItem , ParentModuleSlot );
}

bool UInventoryBaseComponent::Client_UnEquipModule_Validate( FItemData ParentItem , int32 ParentModuleSlot )
{
	return true;
}

void UInventoryBaseComponent::Client_SetEquipInven_Implementation( EWearingInvenType InvenType , const TArray<EGWItemSubType>& ItemSubTypes , const TArray<FItemData>& ItemDatas )
{
	SetEquipInven( InvenType , ItemSubTypes ,ItemDatas );
}

bool UInventoryBaseComponent::Client_SetEquipInven_Validate( EWearingInvenType InvenType , const TArray<EGWItemSubType>& ItemSubTypes , const TArray<FItemData>& ItemDatas )
{
	return true;
}

void UInventoryBaseComponent::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	//DOREPLIFETIME( UInventoryBaseComponent , MyInventoryItems );
}