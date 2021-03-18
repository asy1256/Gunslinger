// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Data/GP2EnumTypes.h"
#include "ModuleManagerBaseComponent.generated.h"


UENUM( BlueprintType )
enum class EModuleEquipState : uint8
{
	Sueccess,
	NotMatch,
	LackCost
};

// ModuleStructBase
// 각 모듈에 종류 별로 기본 모듈 데이터를 상속하여 만든다.
USTRUCT( BlueprintType )
struct FGWModuleData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWModuleData()
	:           
	ModuleName     ( TEXT( "" ) ) ,
	ModuleSlotType ( EGWModuleSlotType::CommonAll ) ,
	ModuleImage    ( nullptr ) ,
	ModuleCost     ( 0 )
	{
	}

public:

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite , Category = "ModuleItem|Base" )
	FString ModuleName;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite , Category = "ModuleItem|Base" )
	EGWModuleSlotType ModuleSlotType;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite , Category = "ModuleItem|Base" )
	class UTexture2D* ModuleImage;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite , Category = "ModuleItem|Base" )
	int32 ModuleCost;
};

USTRUCT( BlueprintType )
struct FModuleSlotData : public FTableRowBase
{
	GENERATED_BODY()

	EGWModuleSlotType SlotType;

	FGWModuleData* ModuleData;

	FModuleSlotData() :

		SlotType( EGWModuleSlotType::CommonAll ) ,
		ModuleData( nullptr )
	{
	}
};

USTRUCT( BlueprintType )
struct FMouleInitParam : public FTableRowBase
{
	GENERATED_BODY()

	int32 TotalMouduleCost;

	int32 SocketNumber;

	TMap<int32 , FModuleSlotData > InitModuleSlotInfos;

	FMouleInitParam() :
		TotalMouduleCost( 0 ) ,
		SocketNumber(0),
		InitModuleSlotInfos( TMap<int32 , FModuleSlotData >() )
	{}

};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUNSLINGERSW_API UModuleManagerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UModuleManagerBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void EquipInitModules( TMap<int32 , FGWModuleData> InitModuleDatas );

	virtual void InitModule( FMouleInitParam InitData );

	UFUNCTION(BlueprintCallable,Category = "ModuleSystem|Function")
	EModuleEquipState EquipModule( FGWModuleData& OldModule , int32 SocketIndex , FGWModuleData ModuleData );

	UFUNCTION( BlueprintCallable , Category = "ModuleSystem|Function" )
	FGWModuleData RemoveModule( int32 SocketIndex );
private:

	void CreateModuleSocket(int32 SockeIndex , FModuleSlotData ModuleData);

public:	


protected:

	int32 MaxSockeNumber = 0;

	int32 TotalModuleCost;

	TMap<int32  , FModuleSlotData> ModuleSlots;

};
