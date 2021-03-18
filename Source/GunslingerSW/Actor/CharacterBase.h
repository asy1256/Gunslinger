// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP2CharacterInterface.h"
#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/GenericTeamAgentInterface.h"
#include "../Data/GP2EnumTypes.h"
#include "../Data/CharacterDataType.h"
#include "../Data/GP2DataStructTypes.h"
#include "CharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;

USTRUCT(BlueprintType)
struct FGWWeaponSlot
{
	GENERATED_BODY()

public:
	FGWWeaponSlot()
		:
		FirstSlotInfoId  ( -1 ),
		SecondSlotInfoId ( -1 ),
		ThirdSlotInfoId  ( -1 )
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Custom Info/Weapon")
	int32 FirstSlotInfoId; /// 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Custom Info/Weapon")
	int32 SecondSlotInfoId; /// 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Custom Info/Weapon")
	int32 ThirdSlotInfoId; /// 
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterMeshLoadCompleted, const int32&, Index);

UCLASS()
class GUNSLINGERSW_API ACharacterBase 
	:
	public ACharacter ,
	public IGenericTeamAgentInterface ,
	public IGP2CharacterInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "MobSpawn" )
	FGenericTeamId TeamId;

	/// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	/// int ObjId; /// ���� �ĺ���

	/// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	/// int InfoId; /// ĳ���� �ĺ��� - pve : sex , pvp : class

	/// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	/// FString Name; /// �÷��̾� �̸�

	/// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	FGWWeaponSlot WeaponSlotInfos; ///

	/// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	EGWPCType PcType; /// �÷��̾� ����

	/// EGWCharacterClass ClassType;


public:
	// Sets default values for this character's properties
	ACharacterBase();


public:
	///-------------------------------------------------------------------------------------------------
	/// ACharacter's Virtual Functions
	///-------------------------------------------------------------------------------------------------
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// Called before destroying the object.  
	virtual void BeginDestroy() override;

	/// Overridable function called whenever this actor is being removed from a level
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

	/// Called every frame.
	virtual void Tick( float DeltaSeconds ) override;


	///-------------------------------------------------------------------------------------------------
	/// Getter - Setter
	///-------------------------------------------------------------------------------------------------
	/** Returns CameraBoom subobject **/
	virtual USpringArmComponent* GetCameraBoom() const { return nullptr; }

	/** Returns FollowCamera subobject **/
	virtual UCameraComponent* GetFollowCamera() const { return nullptr; }

	virtual AController* GetController() { return nullptr; }

	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; };

	
public:
	UFUNCTION( BlueprintCallable , Category = "CoreState" )
	void SetTeamID( FGenericTeamId newTeamID ) { TeamId = newTeamID; return; };

	UFUNCTION( BlueprintCallable , Category = "CoreState" )
	FGenericTeamId GetTeamID() { return TeamId; };

	//UFUNCTION( BlueprintCallable, Category = "Player Info" )
	//int GetObjId() const { return ObjId;}

	//UFUNCTION(BlueprintCallable, Category = "Player Info")
	//EGWCharacterClass GetClass() const { return ClassType; }

	// UFUNCTION( BlueprintCallable, Category = "Player Info" )
	// int GetInfoId() const { return InfoId; }

	//UFUNCTION( BlueprintCallable, Category = "Player Info" )
	//FString GetName() const { return Name; }

	UFUNCTION( BlueprintCallable, Category = "Player Info" )
	FGWWeaponSlot GetWeaponSlotInfos() const { return WeaponSlotInfos;  }

	UFUNCTION(BlueprintCallable, Category = "Player Info")
	EGWPCType GetPcType() const { return PcType ; }
	
	//UFUNCTION( BlueprintCallable, Category = "Player Info" )
	//void SetObjId( int InObjId ) { ObjId = InObjId; }

	//UFUNCTION(BlueprintCallable, Category = "Player Info")
	//void SetClass( EGWCharacterClass InClassType ) { ClassType = InClassType;  }

	// UFUNCTION( BlueprintCallable, Category = "Player Info" )
	// void SetInfoId( int InInfoId ) { InfoId = InInfoId; }

	//UFUNCTION( BlueprintCallable, Category = "Player Info" )
	//void SetName( const FString& InName ) { Name = InName; }

	UFUNCTION( BlueprintCallable, Category = "Player Info" )
	void SetWeaponSlotInfos( const FGWWeaponSlot& InWeaponSlot ) { WeaponSlotInfos = InWeaponSlot; }

	UFUNCTION(BlueprintCallable, Category = "Player Info")
	void SetPcType(EGWPCType InPcType ) { PcType = InPcType; }


public:
	///---------------------------------------------------------------------------
	/// Character SkeletalMesh Async Load
	///---------------------------------------------------------------------------
	
	// �񵿱� �ε��� �Ϸ�Ǹ� ����Ǵ� �ε���
	int32 CharacterIndex;

	// �񵿱� �ε��� �Ϸ�Ǳ� ���� ����Ǵ� �ε���
	int32 AsyncLoadIndex;

	// �񵿱� �ε����� ����
	UFUNCTION(BlueprintCallable, Category = "Async")
	void AsyncLoadCharacterMesh(int32 NewIndex);

	// �񵿱� �ε� �Ϸ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Async")
	void AsyncLoadCompletedCharacterMesh();
	virtual void AsyncLoadCompletedCharacterMesh_Implementation();

	// �񵿱� �ε� �Ϸ������ ��������Ʈ
	UPROPERTY(BlueprintAssignable, Category = "Async")
	FCharacterMeshLoadCompleted CharacterLoadCompleted;
};
