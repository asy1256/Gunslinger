// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemDataType.h"
#include "Data/GP2EnumTypes.h"
#include "GWStatComponent.generated.h"

/** �ش� ������ ���������� ���� ������ �Ǵ��Ҷ� ���� �̳�*/
UENUM( BlueprintType )
enum class EGWAdjustment: uint8
{
	Positive ,
	Negative ,
};

/** ������ ���� , ADD �Ǵ� �� , Multiply �Ǵ� ���� min , max ������ �����ϴ� ������ 
    ���̺�� �ۼ��Ͽ� ���� ������Ʈ�� �ʱ�ȭ�߿� ���� ���� ���� ����     
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

/** ���ݿ� �߰��Ǵ� ADD ��, Multiply �� �����͸� �����ϴ� ��Ʈ��ó */
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

/** ���� ���ݿ� ���� �߰� �ϰ� �����Ҷ� ���Ǵ� �Ķ���� ��Ʈ��ó*/
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

/**  ������ ���� �����ϰ� �ִ� ���� ��Ʈ��ó */
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

	/** StatDataMap�� ���� EGWStatType �� ���� FGWStat ������ ��Ʈ��ó�� ���� ��Ű�� �Լ� $$���� ����ϴ� ���� ������Ʈ���� �������̵��ؼ� ���*/
	virtual void SetStatMapping();

	void SetDefaultStat( double Value , EGWStatType Type);

	/** StatRangeTable �� ���õ� ���� ���� ������ Add , Multiply ������ ���� */
	void SetStatRangeDatas();

	TMap< EGWStatType , FGWStat* > StatDataMap;

public:

	/** ���� ���߰�
	* @Param StatParam - �߰��Ǵ� ���� 
	*/
	virtual void AddStat( const FAddStatParam& StatParam );

	/** ���� ���߰�
	* @Param RangeParam - ������ ����, ������ ���� �߰� �Ǵ� ����� ����
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

