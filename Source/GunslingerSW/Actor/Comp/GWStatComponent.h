// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemDataType.h"
#include "Data/GP2EnumTypes.h"
#include "GWStatComponent.generated.h"

/** 해당 스텟이 증감형인지 가감 형인지 판단할때 쓴느 이넘*/
UENUM( BlueprintType )
enum class EGWAdjustment: uint8
{
	Positive ,
	Negative ,
};

/** 스탯의 총합 , ADD 되는 값 , Multiply 되는 값의 min , max 범위를 설정하는 데이터 
    테이블로 작성하여 스텟 컴포넌트가 초기화중에 각각 스텟 마다 설정     
*/
USTRUCT( BlueprintType )
struct FGWStatRangeParam : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString ParamId;
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EGWStatType OriginType;
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EGWAdjustment Adjustment;
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float AddMinRange;   
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float AddMaxRange;
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float MultiplyMinRange;
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float MultiplyMaxRange;
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float TotalMinRange;
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float ToTalMaxRange;
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString Description;

	FGWStatRangeParam() : ParamId(""), Description("")
	{}

};

/** 스텟에 추가되는 ADD 값, Multiply 값 데이터를 저장하는 스트럭처 */
USTRUCT()
struct FGWStatAdjustment
{
	GENERATED_BODY()

public:

	UPROPERTY()
	double AdjValue;

	UPROPERTY()
	double MinRange;

	UPROPERTY()
	double MaxRange;

	UPROPERTY()
	int8 Adj = 1;

	FGWStatAdjustment( double Value , double Min , double Max )
		: AdjValue( Value ) , MinRange( Min ) , MaxRange( Max )
	{}
	FGWStatAdjustment( )
	{}
	FORCEINLINE void AddValue(double Value)
	{
		AdjValue = FMath::Clamp( AdjValue + (Value * Adj) , MinRange , MaxRange );
	};
	FORCEINLINE void SetAdjustmentType( EGWAdjustment Type )
	{
		if( Type == EGWAdjustment::Negative )
		{
			Adj = -1;
		}
	};
};

/** 현재 스텟에 값을 추가 하고 제거할때 사용되는 파라미터 스트럭처*/
USTRUCT( BlueprintType )
struct FAddStatParam : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite)
	EGWStatCalculateType CalculateType;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EGWStatType StatType;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float Value = 0.0f;

};

/**  스텟의 값을 저장하고 있는 스텟 스트럭처 */
USTRUCT()
struct FGWStat
{
	GENERATED_BODY()

public:

	UPROPERTY()
	double DefualtValue;

	UPROPERTY()
	FGWStatAdjustment Add;

	UPROPERTY()
	FGWStatAdjustment Multiply;

	UPROPERTY()
	double TotalMin;

	UPROPERTY()
	double TotalMax;

	FGWStat()
	: DefualtValue( 0.0f ) , Add( FGWStatAdjustment( 0 , 0 , 0 ) ) , Multiply( FGWStatAdjustment( 0 , 0 , 0 ) ) , TotalMin(0.f) , TotalMax(0.f)
	{};

	FORCEINLINE double GetTotalStatValue() { return  FMath::Clamp( ( DefualtValue*( 1 + Multiply.AdjValue ) + Add.AdjValue ) , TotalMin , TotalMax ); }
};

UCLASS( Blueprintable , BlueprintType , ClassGroup=(Custom), meta = (BlueprintSpawnableComponent) )
class GUNSLINGERSW_API UGWStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGWStatComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
protected:	
	// Called every frame
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** StatDataMap에 각각 EGWStatType 과 실제 FGWStat 데이터 스트럭처를 맵핑 시키는 함수 $$실제 사용하는 스텟 컴포넌트에서 오버라이드해서 사용*/
	virtual void SetStatMapping();

	void SetDefaultStat( double Value , EGWStatType Type);

	/** StatRangeTable 에 세팅된 값을 가각 스텟의 Add , Multiply 변수에 설정 */
	void SetStatRangeDatas();

	TMap< EGWStatType , FGWStat* > StatDataMap;

public:

	/** 스텟 값추가
	* @Param StatParam - 추가되는 스텟 
	*/
	virtual void AddStat( const FAddStatParam& StatParam );

	/** 스텟 값추가
	* @Param RangeParam - 스텟의 범위, 스텟의 값이 추가 되는 방식을 결정
	*/
	void SetStatRange(const FGWStatRangeParam& RangeParam);

	UFUNCTION( BlueprintPure , Category = "StatComponent" )
	float GetStat( EGWStatType StatType );

	UFUNCTION( BlueprintPure , Category = "StatComponent" )
	float GetAdditionalStat( EGWStatType StatType );

	UFUNCTION( BlueprintPure , Category = "StatComponent" )
	float GetDefaultStat( EGWStatType StatType );

	UFUNCTION( BlueprintCallable , Category = "StatComponent" )
	virtual void GetAllStatInfo( TArray<FString>& StatName ,TArray<float>& StatValue );

protected:

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite )
	class UDataTable* StatRangeTable;

	
};

