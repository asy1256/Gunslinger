// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP2PCInterface.h"
#include "GameFramework/PlayerController.h"
#include "../Data/GP2EnumTypes.h"
// #include "../Data/PlayerDataType.h"
#include "../Data/StageDataType.h"
#include "../Data/GP2DataStructTypes.h"
#include "../Data/GP2StructTypes.h"
#include "GP2PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class GUNSLINGERSW_API AGP2PlayerControllerBase
	:
	public APlayerController ,
	public IGP2PCInterface
{
	GENERATED_BODY()

public:
	AGP2PlayerControllerBase();



public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	float                    CurrentTime;           /// 

	UPROPERTY( Replicated, EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	struct FGWPlayerInfo              PlayerData;            ///rep

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	struct FGWStageInfo               StageInfo;             ///rep

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	int                      UserSn;                ///rep

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	FString                  AuthToken;             ///

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	TArray<struct FGWPlayerQuestData> PlayerQuestList;       ///rep

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	int                      PlayerExp;             ///rep

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	int                      PlayerMoney;           ///rep

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	int                      PlayerLv;              ///rep

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	bool                     IsChattingMode;        ///

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	FText                    SenderText;            ///rep

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	FText                    SenderName;            ///rep

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	FText                    RecentWhisperUserName; ///rep

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	bool                     LogOutProcess;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	bool                     InventoryMode;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	TArray< struct FGWSubLevel >      SubLevelInfos;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	int                      CurrentLoadCount;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	int                      TotalLoadCount;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	bool                     LoadCompleted;         ///

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	FText                    SystemInfo;            ///rep

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "GP2PlayerController|Base" )
	FTimerHandle             CPUSystemTimer;        ///


	/////�� �����Ѵ�.
	//UFUNCTION( BlueprintCallable , Category="" )
 //	void SetCurrentLoadCount( int CurrentLoadCount ) { CurrentLoadCount = CurrentLoadCount; }

	//UFUNCTION( BlueprintCallable , Category = "" )
 //	void SetTotalLoadCount( int TotalLoadCount ) { TotalLoadCount = TotalLoadCount; }

	/////�� �����Ѵ�.
 //	void SetLoadCompleted( bool LoadCompleted ) { LoadCompleted = LoadCompleted; }

	/////�� �����Ѵ�.
 //	void SetCPUSystemTimer( const FTimerHandle& CPUSystemTimer ) { CPUSystemTimer = CPUSystemTimer; }

	/////�� ��ȯ�Ѵ�.
 //	int GetCurrentLoadCount() const { return CurrentLoadCount; }

	/////�� ��ȯ�Ѵ�.
 //	int GetTotalLoadCount() const { return TotalLoadCount; }

	/////�� ��ȯ�Ѵ�.
 //	bool GetLoadCompleted() const { return LoadCompleted; }

	/////�� ��ȯ�Ѵ�.
 //	const FTimerHandle& GetCPUSystemTimer() const { return CPUSystemTimer; }



	/*
	UFUNCTION( BlueprintImplementableEvent , Category = "PlayerControllerBase" )
	UFUNCTION( BlueprintPure , Category = "PlayerControllerBase")
	*/

public:
	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//EGWTeam GetTeam() const;///

	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//uint8 GetSlot() const;///

	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//FString GetNickName() const;///

	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//int GetInfoId() const;/// 

	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//int GetWeaponInfoId() const;/// 

	//// UFUNCTION( BlueprintCallable )
	//// * GetHudComp() const;/// 

	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//int GetPlayerId() const;/// 

	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//int GetUserSn() const;/// 

	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//FPlayerInfo GetPlayerInfo() const;/// 

	/// UFUNCTION( BlueprintCallable )
	/// FPlayerQuestItemData GetPlayerQuestItemData() const;/// 

	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//FString GetAuthToken() const;/// 

	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//int GetUserSn_PC() const;///

	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//int GetLevel() const; /// 
	//
	////// 
	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//bool IsLogoutProcess() const
	//{
	//	return true;
	//}

	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase")
	//bool IsReadyState() const
	//{
	//	return true;
	//}

	//UFUNCTION( BlueprintPure , Category = "PlayerControllerBase" )
	//bool IsMaster() const
	//{
	//	return true;
	//}

	//UFUNCTION( BlueprintImplementableEvent )
	//void SetMaster( bool Master );

	//UFUNCTION( BlueprintImplementableEvent )
	//void SetReady( bool Ready );


	// UFUNCTION( BlueprintCallable )
	// TArray< FPCQuestItem > MakeTargetList( FQuestItemInfo ST_QuestItem_Info ); /// 
	/// UFUNCTION( BlueprintCallable )
	/// void QuestFindIndex( FName QuestID ); /// 



	//UFUNCTION( BlueprintImplementableEvent , Category = "PlayerControllerBase" )
	//void AllMessage(); /// 

	//UFUNCTION( BlueprintImplementableEvent , Category = "PlayerControllerBase" )
	//void TeamMessage(); /// 

	//UFUNCTION( BlueprintImplementableEvent , Category = "PlayerControllerBase" )
	//void WhispserMessage(); /// 

	// UFUNCTION( BlueprintImplementableEvent , Category = "PlayerControllerBase" )
	// EGWChatMessageType ChatCommandFunc( FText InText , EGWChatMessageType InChatType ); /// 




	// UFUNCTION( BlueprintImplementableEvent )
	// void Initialize(); /// 

	// UFUNCTION( BlueprintImplementableEvent )
	// void InitUI(); /// 

	//UFUNCTION( BlueprintCallable )
	//void SetUserSn( int UserSn ); /// 

	//UFUNCTION( BlueprintImplementableEvent )
	//void SetTeamInfo( EGWTeam Team , uint8 SlotId ); /// 

	// UFUNCTION( BlueprintCallable )
	// void SetLogoutProcess( bool LogOutProcess ); /// 

	//UFUNCTION( BlueprintImplementableEvent )
	//float GetScreenRatio() const; /// 

	// UFUNCTION( BlueprintCallable )
	// void InitPlayerInfoForTutorial( EGWTeam Team , int UserSn ); /// 

	// UFUNCTION( BlueprintImplementableEvent )
	// int GetPlayerLevel() const; /// 

	// UFUNCTION( BlueprintImplementableEvent )
	// void SetPlayerLevel( int level ); /// 

	// UFUNCTION( BlueprintImplementableEvent )
	// void ControllMouseByGamepad( bool GamePadConnected ); /// 

	// UFUNCTION( BlueprintImplementableEvent )
	// bool IsCheatText( FText InText ); ///


public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const override;
};
