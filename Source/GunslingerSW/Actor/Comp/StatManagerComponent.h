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

	/**���� ��� ������Ʈ���� �ʱ�ȭ �Ǿ��ִ��� Ȯ���ϴ� �Լ�*/
	UFUNCTION( BlueprintPure , Category = "StatManager|Function" )
	bool IsAllocatedAllComponent();

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite )
	class UDataTable* OptionInfoTable;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite )
	class UDataTable* MasteryTable;

public:

	/**��� ���� ������Ʈ���� �ʱ�ȭ �Ǹ� ȣ��Ǵ� ��������Ʈ*/
	UPROPERTY( BlueprintAssignable , Category = "Statmanager|Delegate" )
	FAllStatCompCompleteDelegate AllStatCompAllocated;

	/** ���� �߰�
	 * @param Stat - �߰��Ǵ� stat ������
	 * @param StatComponent - �߰���ų ���� ������Ʈ
	 */
	UFUNCTION( BlueprintCallable , Category = "StatManager|Function" )
	void AddStat( FAddStatParam Stat , EGWStatCompType ApplyComponent );

	/** �ɼ� �߰�
	 * @param SlotIndex - �߰��Ǵ� statComponentIndex
	 * @param OptionIds - �߰���ų �ɼ� id 
	 * @param AdjumentType(��Ÿ) - �ش� �ɼ��� �߰� ��ų���� ������ ���� Positive / Negative
	 */
	UFUNCTION( BlueprintCallable , Category = "StatManager|Function" )
	void AddOptionDatas(  int32 SlotIndex ,const TArray<int32>& OptionIds  , EGWAdjustment AdjumentType);

	/** Ư�� �߰�
	 * @param MasteryIds - �߰��Ǵ� Ư�� id
	 */
	void AddMasteryDatas( const TArray<int32>& MasteryIds  );

	/** Ư�� ����
	 * @param MasteryIds - ���ŵǴ� Ư�� id
	 */
	void RemoveMasteryDatas( const TArray<int32>& MasteryIds );

	/** ���� ���� ������Ʈ�� �ʱ�ȭ �Ҷ� ����ϴ� �Լ�
	 * @param StatCompType - ���� �����ʴ� Ÿ�� 
	 */
	UFUNCTION( BlueprintCallable , Category = "StatManager|Function" )
	void SetStatComponent( EGWStatCompType StatCompType  , UGWStatComponent* StatComponent );

};
