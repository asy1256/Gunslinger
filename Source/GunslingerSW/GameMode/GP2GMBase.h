// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameMode.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "../Data/GP2EnumTypes.h"
#include "../Data/GP2DataStructTypes.h"
#include "GP2GMBase.generated.h"

class AMonsterPool;

/**
 * 
 */
UCLASS()
class GUNSLINGERSW_API AGP2GMBase : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void Tick( float DeltaSeconds ) override;
	

public:
	AGP2GMBase();

	virtual void PreLogin( const FString& Options , const FString& Address , const FUniqueNetIdRepl& UniqueId , FString& ErrorMessage ) override;

	void OnResponseReceived( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bWasSuccessful );

	void InitData();

	UFUNCTION( BlueprintCallable , Category = "GP2GMBase" )
	void getTeamInfo( int32 &getTeam , uint8 &getSlot );

	UFUNCTION( BlueprintCallable , Category = "GP2GMBase" )
	void LoginSessionCheck( const int &PlayerID , const FString &PlayerSessionID , const int &UserSN , bool &CheckResult , int &errorType );

	UFUNCTION( BlueprintCallable , Category = "GP2GMBase" )
	void LogoutProcess( const int &PlayerID , const int &LogOutUserSN , const int32 &LogOutTeam , const int &LogOutSlot , int &MasterUserSN );

	UFUNCTION( BlueprintCallable )
	void eacLogEventGameRoundStart();

	UFUNCTION( BlueprintCallable )
	void eacLogEventGameRoundEnd();

	UFUNCTION( BlueprintCallable , Category = "GP2GMBase" )
	uint8 getEmptySlot( int32 &Team );

	UFUNCTION( BlueprintCallable , Category = "GP2GMBase" )
	void TeamChange( const int& Slot , const int32& Team , bool& Result , int& ChangeSlot , int32& ChangedTeam );

	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2GMBase" )
	bool IsEmptySlot( int32 team , uint8 slot );

	UFUNCTION(BlueprintCallable)
	AMonsterPool*& GetMonsterPool() { return MonsterPool; }

	UFUNCTION(BlueprintCallable)
	void SetMonsterPool(AMonsterPool* pool) { MonsterPool = pool; }

private:
	UPROPERTY()
	TMap< int8 , bool > m_RedTeamMap;      ///

	UPROPERTY()
	TMap< int8 , bool > m_BlueTeamMap;     ///

	UPROPERTY()
	TArray< int >       m_AcceptList;      ///

	UPROPERTY()
	int32             m_eLastSelectTeam; ///


	//////////////////////////////////
protected:
	float                        CurrentTime;           /// ����ð�
	float                        MaxTime;               /// �ִ�ð�
	struct FGWStageInfo          StageInfo;             /// �������� ����

	FString StageName; /// �������� �̸�
	int StageInfoId; /// �������� �ε���

	EGWGameMode CurrentGameMode; /// ���� ���Ӹ��

	AMonsterPool* MonsterPool;

public:
	/// ����ð��� �����Ѵ�.
 	UFUNCTION( BlueprintCallable , Category = "GP2GMBase" )
	void SetCurrentTime( float _CurrentTime ) { CurrentTime = _CurrentTime; }

	/// �ִ�ð��� �����Ѵ�.
 	UFUNCTION( BlueprintCallable , Category = "GP2GMBase" )
	void SetMaxTime( float _MaxTime ) { MaxTime = _MaxTime; }

	/// �������� ������ �����Ѵ�.
	UFUNCTION( BlueprintCallable , Category = "GP2GMBase" )
	void SetStageInfo( const struct FGWStageInfo& _StageInfo ) { StageInfo = _StageInfo; }

	/// ����ð��� ��ȯ�Ѵ�.
 	UFUNCTION( BlueprintCallable , BlueprintPure,  Category = "GP2GMBase" )
	float GetCurrentTime() const { return CurrentTime; }

	/// �ִ�ð��� ��ȯ�Ѵ�.
 	UFUNCTION( BlueprintCallable, BlueprintPure , Category = "GP2GMBase" )
	float GetMaxTime() const { return MaxTime; }

	/// �������� ������ ��ȯ�Ѵ�.
	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "GP2GMBase" )
	const struct FGWStageInfo& GetStageInfo() const { return StageInfo; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GP2GMBase")
	const FString GetStageName() const { return StageName; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GP2GMBase")
	const int& GetStageInfoId() const { return StageInfoId; }


public:
	UFUNCTION( BlueprintImplementableEvent , Category = "GP2GMBase" )
	void SetFlexMatchData( int MapIndex , const FString& MapName , int MaxUserCount , EGWGameMode GameMode , EGWGamePVPRule GamePvpRule );

	UFUNCTION( BlueprintImplementableEvent , Category = "GP2GMBase" )
	void SetCustomMatchData( const int MapIndex , const FString& MapName , const int MaxUserCount , EGWGameMode GameMode , const FString& Master , const FString& Title);


};
