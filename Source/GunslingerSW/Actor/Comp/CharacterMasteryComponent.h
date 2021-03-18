// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/GP2EnumTypes.h"
#include "Actor/Comp/GWStatComponent.h"
#include "Actor/Comp/StatManagerComponent.h"
#include "CharacterMasteryComponent.generated.h"

UENUM( BlueprintType )
enum class EGWMasteryCategory : uint8
{
	Weapon ,   ///
	Body , ///
	Assistance, //
};


UENUM( BlueprintType )
enum class EGWMasteryTarget: uint8
{
	Character,
	Weapon  ///
};

USTRUCT( BlueprintType )
struct FGWMasteryDataParam : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
	FName SkillGroupId ;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
	EGWJobType ClassType;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
	EGWMasteryCategory Category;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
	EGWMasteryTarget ApplyTarget;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
	FAddStatParam StatParam;

	FGWMasteryDataParam()
		: SkillGroupId( "" ) ,
		ClassType( EGWJobType::none ) ,
		Category( EGWMasteryCategory::Weapon ) ,
		ApplyTarget( EGWMasteryTarget::Character )
	{
	};

};
USTRUCT( BlueprintType )
struct FGWMasteryGroupParam : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		FName SkillGroupId ;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		EGWJobType ClassType;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		EGWMasteryCategory Category;

	UPROPERTY( BlueprintReadWrite , EditAnywhere , meta = (ClampMin = "0") )
		int32 UiOrder;

	UPROPERTY( BlueprintReadWrite , EditAnywhere , meta = (ClampMin = "0") )
		int32 MaxLevel;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		FName SkillNameStringId;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		FName SkillEffectStringId;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		class UTexture2D* Icon;

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
		FString Description;

	FGWMasteryGroupParam()
		: SkillGroupId( "" ) ,
		ClassType( EGWJobType::none ) ,
		Category( EGWMasteryCategory::Weapon ) ,
		UiOrder( 0 ) ,
		MaxLevel(0 ) ,
		SkillNameStringId( "" ) ,
		SkillEffectStringId( "" ) ,
		Icon( nullptr ) ,
		Description( "" )
	{
	};

};

UCLASS( Blueprintable , BlueprintType ,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUNSLINGERSW_API UCharacterMasteryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterMasteryComponent();

private:

	void AddActiveMastery( const uint16& MasteryId );

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	* Set NewActive MasteryData From WebServer  
	* @Param MasteryArray - MasteryGroupIdKey Using Table
	*/
	UFUNCTION( BlueprintCallable , Category = "Function" )
	void SetActiveMastery( const TArray<int32>& MasteryArray );

	/**
	* Set CurrentStatManager In Character
	* @Param NewStatManager - StatManager
	*/
	UFUNCTION( BlueprintCallable , Category = "Function" )
	void InitComponent( class UStatManagerComponent* NewStatManager);

	UFUNCTION(  BlueprintPure , Category = "Function" )
	TArray<int32> GetActiveSkillIds() const ;

	UFUNCTION( BlueprintPure , Category = "Function" )
	int32 GetCurrentSkillPoint() const ;

	/**
	* Set SkillPoint 
	* @Param NewSkillPoint - NewCalculatedValue And Initilize 
	*/
	UFUNCTION( BlueprintCallable , Category = "Function" )
	void SetSkillPoint( const int32& NewSkillPoint );


	/////// ClientRPC //////

	UFUNCTION( BlueprintCallable , Client , Reliable, Category = "Function" )
	void Client_SetSkillPoint( const int32& NewSkillPoint );

	void Client_SetSkillPoint_Implementation( const int32& NewSkillPoint );

	bool Client_SetSkillPoint_Validate(  const int32& NewSkillPoint );


	UFUNCTION( BlueprintCallable , Client , Reliable , Category = "Function" )
	void Client_SetActiveMastery( const TArray<int32>& MasteryArray );

	void Client_SetActiveMastery_Implementation( const TArray<int32>& MasteryArray );

	bool Client_SetActiveMastery_Validate( const TArray<int32>& MasteryArray );

private:

	const uint16 MaxSkillPoint = 30;

	TArray<int32> ActiveSkillIds;

	uint16 SkillPoint;

	class UStatManagerComponent* StatManager;

protected :

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite )
	class UDataTable* MasteryDataTable;


		
};
