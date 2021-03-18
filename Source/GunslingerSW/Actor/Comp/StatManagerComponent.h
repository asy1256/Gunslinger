// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemDataType.h"
#include "Actor/Comp/CharacterStatComponent.h"
#include "Actor/Comp/WeaponStatComponent.h"
#include "StatManagerComponent.generated.h"


UENUM( BlueprintType )
enum class EGWStatCompType : uint8
{
	Character ,
	WeaponFirstSlot ,
	WeaponSecondSlot ,
	WeaponThirdSlot ,
	WeaponAll,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FAllStatCompCompleteDelegate );

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUNSLINGERSW_API UStatManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatManagerComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UGWStatComponent* CharacterStat;

	TArray<UGWStatComponent*> WeaponStats;

	TArray<FGWItemOptionInfo> AddStatList;


protected:

	/*
	UFUNCTION( BlueprintCallable , Category = "Stat|Function" )
    void AddStats(  FAddStatInfoParam AddStats );

	void AddStat(  FGWItemOptionInfo AddStat );

	void ApplyAddStat();
	*/

	/**현재 모든 컴포넌트들이 초기화 되어있는지 확인하는 함수*/
	UFUNCTION( BlueprintPure , Category = "StatManager|Function" )
	bool IsAllocatedAllComponent();

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite )
	class UDataTable* OptionInfoTable;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite )
	class UDataTable* MasteryTable;

public:

	/**모든 스텟 컴포넌트들이 초기화 되면 호출되는 델리게이트*/
	UPROPERTY( BlueprintAssignable , Category = "Statmanager|Delegate" )
	FAllStatCompCompleteDelegate AllStatCompAllocated;

	/** 스텟 추가
	 * @param Stat - 추가되는 stat 데이터
	 * @param StatComponent - 추가시킬 스텟 컴포넌트
	 */
	UFUNCTION( BlueprintCallable , Category = "StatManager|Function" )
	void AddStat( FAddStatParam Stat , EGWStatCompType ApplyComponent );

	/** 옵션 추가
	 * @param SlotIndex - 추가되는 statComponentIndex
	 * @param OptionIds - 추가시킬 옵션 id 
	 * @param AdjumentType(오타) - 해당 옵션을 추가 시킬건지 뺄건지 선택 Positive / Negative
	 */
	UFUNCTION( BlueprintCallable , Category = "StatManager|Function" )
	void AddOptionDatas(  int32 SlotIndex ,const TArray<int32>& OptionIds  , EGWAdjustment AdjumentType);

	/** 특성 추가
	 * @param MasteryIds - 추가되는 특성 id
	 */
	void AddMasteryDatas( const TArray<int32>& MasteryIds  );

	/** 특성 제거
	 * @param MasteryIds - 제거되는 특성 id
	 */
	void RemoveMasteryDatas( const TArray<int32>& MasteryIds );

	/** 각각 스텟 컴포넌트를 초기화 할때 사용하는 함수
	 * @param StatCompType - 스텟 컴포너는 타입 
	 */
	UFUNCTION( BlueprintCallable , Category = "StatManager|Function" )
	void SetStatComponent( EGWStatCompType StatCompType  , UGWStatComponent* StatComponent );

};
