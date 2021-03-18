// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/GP2EnumTypes.h"
#include "Data/ItemDataType.h"
#include "InventoryBaseComponent.generated.h"

 static const uint16 ItemHasMouduleSize = 4;

 static const uint16 WearingWeaponIvenSize = 3;

 static const uint16 WearingArmorIvenSize = 5;

UENUM( BlueprintType )
enum class EInventoryType : uint8
{
	Weapon ,
	Armor ,
	Module ,
	CraftMaterial ,
	Misc
};

UENUM( BlueprintType )
enum class EWearingInvenType : uint8
{
	Weapon ,
	Armor ,
};

USTRUCT( BlueprintType )
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		int32 Uid;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		EGWItemType  ItemType;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		int32 ItemId;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		int32 Amount;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		int32 Durability;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		TArray<int32> OptionIds;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		TArray<int32> ModuleUids;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		int32 ItemLevel;
	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		bool bIsEquiped;

	FItemData()
		: Uid( 0 ) ,
		ItemType( EGWItemType::None ) ,
		ItemId( 0 ) ,
		Amount( 0 ) ,
		Durability( 0 ) ,
		OptionIds( TArray<int32>() ) ,
		ModuleUids( TArray<int32>() ) ,
		ItemLevel( 0),
		bIsEquiped( false )
	{
	}
};

USTRUCT( BlueprintType )
struct FWearingIventory
{
	GENERATED_BODY()

public:

	FInventory* RefInven;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
	TMap<EGWItemSubType , int32 > Slot;

	FWearingIventory()
	{
	
	};

	FWearingIventory( FInventory* RefInven , TArray<EGWItemSubType> InvenSlotType)
		: RefInven( RefInven )
	{
		for ( uint8 index = 0; index < InvenSlotType.Num(); index++ ) Slot.Add( InvenSlotType[index] ,-1);
	};

};

USTRUCT( BlueprintType )
struct FInventory
{
	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
	TMap<int32 , FItemData> InventoryItems;

	FInventory() :InventoryItems( TMap<int32 , FItemData>() )
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FAddItemCallBackDelegate , FItemData , AddItem );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FAddItemArrayCallBackDelegate , TArray<FItemData> , AddItems );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FRemoveItemCallBackDelegate , FItemData, RemoveItem );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FRemoveItemArrayCallBackDelegate , TArray<FItemData> , RemoveItem );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FEquipItemCallBackDelegate , FItemData , EquipItem ,EGWItemSubType ,ItemType, int32 , ItemSlot );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FUnEquipItemCallBackDelegate , FItemData,UnEquipItem , EGWItemSubType, ItemType);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FEquipModuleCallBackDelegate , FItemData ,ParentItem, int32,Slot , FItemData,ModuleItem );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FUnEquipModuleCallBackDelegate , FItemData ,ParentItem, int32 ,Slot);

UCLASS( Blueprintable , BlueprintType,  ClassGroup = ( Custom ) , meta = ( BlueprintSpawnableComponent ) )
class GUNSLINGERSW_API UInventoryBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	bool FindItemOptionInfoInTable( const FName& RowName , struct FWGItemoptioninfo * OutInfo );


public:
	// Called every frame
	virtual void TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

protected:

	FWearingIventory WearingWeapon;

	FWearingIventory WearingArmor;

	FInventory WeaponInven;

	FInventory ArmorInven;

	FInventory ModuleInven;

	FInventory CraftMaterialInven;

	FInventory MiscInven;

	TArray<FInventory*> InventoryAll;

	TMap<EGWItemType , FInventory* > InventoryMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0) ,Category = "Inventory")
	int32 InventoryMaxSize = 35;

	class UStatManagerComponent* StatManager;

private:

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 Gold;

public:

	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	void AllClearInventory();

	/*
	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
    void CreateIventory( TArray<FItemData> InitItemData , TArray<EGWItemSubType> WeaponEquipment, TArray<EGWItemSubType> ArmorEquipment) ;
	*/
	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	void CreateWeaponEquipment( TArray<EGWItemSubType> WeaponEquipment );

	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	void CreateArmorEquipment( TArray<EGWItemSubType> ArmorEquipment );

	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	bool GetItemInfo( FItemData ItemDtat , struct FGWItemInfo& ItemInfo ) ;

	//UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	FInventory& GetIventoryByItemType( EGWItemType ItemType );

	//UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	FWearingIventory& GetEquipInvenByItemType( EGWItemType ItemType );

	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	bool AddItem( FItemData NewItem );

	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	bool RemoveItem( FItemData RemoveItem );
	/**
    * 만약 아이템이 슬롯에 존재하면 아이템의 Uid를 아니면 -1을 반환
    * @Param Item - 장착할 아이템
    * @Param ItemSlot - 장비 인벤토리에 슬롯 인덱스
    */
	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	int32 EquipItem( FItemData Item , EGWItemSubType ItemSubType , int32& SlotIndex );
	/**
     * 만약 아이템이 슬롯에 존재하면 아이템의 Uid를 아니면 -1을 반환
     * @Param Item - 장착해제할 아이템
     * @Param ItemSlot - 장비 인벤토리에 슬롯 인덱스
     */
	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	int32 UnEquipItem( FItemData Item , EGWItemSubType ItemSubType );
	/**
     * 만약 모듈 슬롯에 아이템이 존재하면 모듈의 Uid를 아니면 -1을 반환
     * @Param ParentItem - 부모 아이템
     * @Param ParentModuleSlot - 아이템의 모듈 슬롯 인덱스
     * @Param ParentModuleSlot - 모듈 아이템
    */
	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	int32 EquipModule( FItemData ParentItem , int32 ParentModuleSlot , FItemData Module );
	/**
     * 만약 모듈 슬롯에 아이템이 존재하면 모듈의 Uid를 아니면 -1을 반환
     * @Param ParentItem - 부모 아이템
     * @Param ParentModuleSlot - 아이템의 모듈 슬롯 인덱스
     */
	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	int32 UnEquipModule( FItemData ParentItem , int32 ParentModuleSlot);
	/**
	* Return Items In Inventroy
	* @Param InvenType - Inventory type
	*/
	UFUNCTION( BlueprintPure , Category = "Inventory|Function" )
	TArray<FItemData> GetInventoryItems( EInventoryType InvenType );
	/**
	* Return Current Equiped Items In WearingInventory
	* @Param InvenType - Inventory type
	*/
	UFUNCTION( BlueprintPure , Category = "Inventory|Function" )
	TArray<FItemData> GetWeraringInvenItems( EWearingInvenType InvenType );

	UFUNCTION( BlueprintPure , Category = "Inventory|Function" )
	FWearingIventory GetWeraringInven( EWearingInvenType InvenType );
	/**
	* Return Module Data In Item
	* @Param InvenType - Inventory type
	*/
	UFUNCTION( BlueprintPure , Category = "Inventory|Function" )
	TArray<FItemData> GetMoudulesInItem( FItemData ParentItem );
	/**
	* Return ItemData From Uid If Item not exist in Inventory return fasle
	* @Param InvenType - Inventory type
	*/
	UFUNCTION( BlueprintPure , Category = "Inventory|Function" )
	bool GetItemFromUid( int32 Uid , FItemData& Item) const;

	UFUNCTION( BlueprintNativeEvent , BlueprintPure, Category = "Inventory|Function" )
	bool CheckCost( FItemData ParentItem , FItemData ModuleItem );

	UFUNCTION( BlueprintPure , Category = "Inventory|Function" )
	int32 GetInventoryMaxSize() const;

	UFUNCTION( BlueprintPure , Category = "Inventory|Function" )
	int32 GetItemAmountInInventory( EInventoryType InvenType );

	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	void SetEquipInven( EWearingInvenType InvenType , TArray<EGWItemSubType> ItemSubTypes , TArray<FItemData> ItemDatas );

	UFUNCTION( BlueprintCallable , Category = "Inventory|Function" )
	void SetStatManager( class UStatManagerComponent* NewStatManager );

	UFUNCTION( BlueprintImplementableEvent , Category = "Inventory|Function" )
	void EquipItemOptionCallBackEvent(class UGWStatComponent* Target, const TArray<int32>& ItemOption );


	////////델리게이트///////////////

	UPROPERTY( BlueprintAssignable , Category = "Inventory|Delegate" )
	FAddItemCallBackDelegate AddItemCallBack;

	UPROPERTY( BlueprintAssignable , Category = "Inventory|Delegate" )
	FAddItemArrayCallBackDelegate AddItemArrayCallBack;

	UPROPERTY( BlueprintAssignable , Category = "Inventory|Delegate" )
	FRemoveItemCallBackDelegate RemoveItemCallBack;

	UPROPERTY( BlueprintAssignable , Category = "Inventory|Delegate" )
	FRemoveItemArrayCallBackDelegate RemoveItemArrayCallBack;

	UPROPERTY( BlueprintAssignable , Category = "Inventory|Delegate" )
	FEquipItemCallBackDelegate EquipItemCallBack;

	UPROPERTY( BlueprintAssignable , Category = "Inventory|Delegate" )
	FUnEquipItemCallBackDelegate UnEquipItemCallBack;

	UPROPERTY( BlueprintAssignable , Category = "Inventory|Delegate" )
	FEquipModuleCallBackDelegate EquipModuleCallBack;

	UPROPERTY( BlueprintAssignable , Category = "Inventory|Delegate" )
	FUnEquipModuleCallBackDelegate UnEquipModuleCallBack;

protected:

	const TArray<int32> GetAllOptionInItem( const FItemData& Item );

public:

	UFUNCTION(BlueprintCallable, Server , Reliable , WithValidation )
	void Server_SetGold(int32 NewGold );
	void Server_SetGold_Implementation( int32 NewGold );
	bool Server_SetGold_Validate( int32 NewGold );

	UFUNCTION( Client , Reliable , WithValidation )
	void Client_SetGold( int32 ServerGold );
	void Client_SetGold_Implementation( int32 ServerGold );
	bool Client_SetGold_Validate( int32 ServerGold );

	////////////////// Run on Server //////////////////////////

	UFUNCTION( BlueprintCallable , Server , Reliable ,Category = "Inventory|Function" )
	void Server_AddItem( FItemData NewItem );
	void Server_AddItem_Implementation( FItemData NewItem );
	bool Server_AddItem_Validate( FItemData NewItem );

	UFUNCTION( BlueprintCallable , Server , Reliable , Category = "Inventory|Function" )
	void Server_AddItemArray( const TArray<FItemData>& NewItems );
	void Server_AddItemArray_Implementation( const TArray<FItemData>& NewItems );
	bool Server_AddItemArray_Validate( const TArray<FItemData>& NewItems );

	UFUNCTION( BlueprintCallable , Server , Reliable , Category = "Inventory|Function" )
	void Server_RemoveItemArray( const TArray<FItemData>& RemoveItems );
	void Server_RemoveItemArray_Implementation( const TArray<FItemData>& RemoveItems );
	bool Server_RemoveItemArray_Validate( const TArray<FItemData>& RemoveItems );

	UFUNCTION( BlueprintCallable , Server , Reliable ,Category = "Inventory|Function" )
	void Server_RemoveItem( FItemData RemoveItem );
	void Server_RemoveItem_Implementation( FItemData RemoveItem );
	bool Server_RemoveItem_Validate( FItemData RemoveItem );

	UFUNCTION( BlueprintCallable , Server , Reliable , WithValidation )
	void Server_EquipItem( FItemData Item , EGWItemSubType ItemSubType , int32 SlotIndex );
	void Server_EquipItem_Implementation( FItemData Item , EGWItemSubType ItemSubType , int32 SlotIndex );
	bool Server_EquipItem_Validate( FItemData Item , EGWItemSubType ItemSubType , int32 SlotIndex );

	UFUNCTION( BlueprintCallable , Server , Reliable , WithValidation )
	void Server_UnEquipItem( FItemData Item , EGWItemSubType ItemSubType );
	void Server_UnEquipItem_Implementation( FItemData Item , EGWItemSubType ItemSubType );
	bool  Server_UnEquipItem_Validate( FItemData Item , EGWItemSubType ItemSubType );

	UFUNCTION( BlueprintCallable , Server , Reliable , WithValidation )
	void Server_EquipModule( FItemData ParentItem , int32 ParentModuleSlot , FItemData Module );
	void Server_EquipModule_Implementation( FItemData ParentItem , int32 ParentModuleSlot , FItemData Module );
	bool Server_EquipModule_Validate( FItemData ParentItem , int32 ParentModuleSlot , FItemData Module );

	UFUNCTION( BlueprintCallable , Server , Reliable , WithValidation )
	void Server_UnEquipModule( FItemData ParentItem , int32 ParentModuleSlot );
	void Server_UnEquipModule_Implementation( FItemData ParentItem , int32 ParentModuleSlot );
	bool Server_UnEquipModule_Validate( FItemData ParentItem , int32 ParentModuleSlot );


	UFUNCTION( BlueprintCallable , Server , Reliable , WithValidation )
	void Server_SetEquipInven( EWearingInvenType InvenType , const TArray<EGWItemSubType>& ItemSubTypes , const TArray<FItemData>& ItemDatas );
	void Server_SetEquipInven_Implementation( EWearingInvenType InvenType , const TArray<EGWItemSubType>& ItemSubTypes , const TArray<FItemData>& ItemDatas );
	bool Server_SetEquipInven_Validate( EWearingInvenType InvenType , const TArray<EGWItemSubType>& ItemSubTypes , const TArray<FItemData>& ItemDatas );

	////////////////// Run Owing client //////////////////////////

	UFUNCTION( BlueprintCallable , Client , Reliable , Category = "Inventory|Function" )
	void Client_AddItem( FItemData NewItem );
	void Client_AddItem_Implementation( FItemData NewItem );
	bool Client_AddItem_Validate( FItemData NewItem );

	UFUNCTION( BlueprintCallable , Client , Reliable , Category = "Inventory|Function" )
	void Client_AddItemArray( const TArray<FItemData>& NewItems );
	void Client_AddItemArray_Implementation( const TArray<FItemData>& NewItems );
	bool Client_AddItemArray_Validate( const TArray<FItemData>& NewItems );

	UFUNCTION( BlueprintCallable , Client , Reliable , Category = "Inventory|Function" )
	void Client_RemoveItem( FItemData RemoveItem );
	void Client_RemoveItem_Implementation( FItemData RemoveItem );
	bool Client_RemoveItem_Validate( FItemData RemoveItem );

	UFUNCTION( BlueprintCallable , Client , Reliable , Category = "Inventory|Function" )
	void Client_RemoveItemArray( const TArray<FItemData>& RemoveItems );
	void Client_RemoveItemArray_Implementation( const TArray<FItemData>& RemoveItems );
	bool Client_RemoveItemArray_Validate( const TArray<FItemData>& RemoveItems );

	UFUNCTION( BlueprintCallable , Client , Reliable , WithValidation )
	void Client_EquipItem( FItemData Item , EGWItemSubType ItemSubType , int32 SlotIndex );
	void Client_EquipItem_Implementation( FItemData Item , EGWItemSubType ItemSubType , int32 SlotIndex );
	bool Client_EquipItem_Validate( FItemData Item , EGWItemSubType ItemSubType , int32 SlotIndex );


	UFUNCTION( BlueprintCallable , Client , Reliable , WithValidation )
	void Client_UnEquipItem( FItemData Item , EGWItemSubType ItemSubType );
	void Client_UnEquipItem_Implementation( FItemData Item , EGWItemSubType ItemSubType );
	bool  Client_UnEquipItem_Validate( FItemData Item , EGWItemSubType ItemSubType );


	UFUNCTION( BlueprintCallable , Client , Reliable , WithValidation )
	void Client_EquipModule( FItemData ParentItem , int32 ParentModuleSlot , FItemData Module );
	void Client_EquipModule_Implementation( FItemData ParentItem , int32 ParentModuleSlot , FItemData Module );
	bool Client_EquipModule_Validate( FItemData ParentItem , int32 ParentModuleSlot , FItemData Module );


	UFUNCTION( BlueprintCallable , Client , Reliable , WithValidation )
	void Client_UnEquipModule( FItemData ParentItem , int32 ParentModuleSlot );
	void Client_UnEquipModule_Implementation( FItemData ParentItem , int32 ParentModuleSlot );
	bool Client_UnEquipModule_Validate( FItemData ParentItem , int32 ParentModuleSlot );

	UFUNCTION( BlueprintCallable , Client , Reliable , WithValidation )
	void Client_SetEquipInven( EWearingInvenType InvenType , const TArray<EGWItemSubType>& ItemSubTypes , const TArray<FItemData>& ItemDatas );
	void Client_SetEquipInven_Implementation( EWearingInvenType InvenType , const TArray<EGWItemSubType>& ItemSubTypes , const TArray<FItemData>& ItemDatas );
	bool Client_SetEquipInven_Validate( EWearingInvenType InvenType , const TArray<EGWItemSubType>& ItemSubTypes , const TArray<FItemData>& ItemDatas );

	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

};

