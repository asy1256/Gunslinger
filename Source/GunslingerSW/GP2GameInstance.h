// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <Engine/GameInstance.h>
#include "Actor/CharacterPC.h"
#include "Packet/PacketConsts.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Engine.h"
#include "EngineGlobals.h"

#if WITH_GAMELIFT
#include "GameLiftServerSDK.h"
#else 
#include "VivoxCore.h"
#endif

#include "IEasyAntiCheatClient.h"

#include "Data/GP2EnumTypes.h"
#include "Engine/DemoNetDriver.h"
#include "NetworkReplayStreaming.h"
#include "GP2GameInstance.generated.h"

class AGameMode;
class UUIManager;

struct FConnectInfo
{

	int     UserSN;          ///
	FString PlayerSessionID; ///

	FConnectInfo() : UserSN (0)
	{
	}

	FConnectInfo(FConnectInfo && connectInfo) : UserSN(0)
	{
	UserSN = connectInfo.UserSN;
	PlayerSessionID = connectInfo.PlayerSessionID;
	}

	FConnectInfo(int UserSN , const FString &PlayerSessionID)
	{
	this->UserSN = UserSN;
	this->PlayerSessionID = PlayerSessionID;
	}

	FConnectInfo & operator=(const FConnectInfo &Other)
	{
	this->UserSN = Other.UserSN;
	this->PlayerSessionID = Other.PlayerSessionID;

	return  *this;           
	}
};



USTRUCT(BlueprintType)
struct FGP2_ReplayInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadOnly)
		FString ReplayName;

	UPROPERTY(BlueprintReadOnly)
		FString FriendlyName;

	UPROPERTY(BlueprintReadOnly)
		FString ReplaySize;

	UPROPERTY(BlueprintReadOnly)
		FString ReplayCharacterName;

	UPROPERTY(BlueprintReadOnly)
		FString ReplayPlayedMap;

	UPROPERTY(BlueprintReadOnly)
		FDateTime Timestamp;

	UPROPERTY(BlueprintReadOnly)
		int32 LengthInMS;

	UPROPERTY(BlueprintReadOnly)
		bool bIsValid;

	FGP2_ReplayInfo(FString NewName, FString NewFriendlyName, FString Size , FString NewCharacterName, FString NewPlayedMap,  FDateTime NewTimestamp, int32 NewLengthInMS)
	{
		ReplayName = NewName;
		FriendlyName = NewFriendlyName;
		ReplaySize = Size;
		ReplayCharacterName = NewCharacterName;
		ReplayPlayedMap = NewPlayedMap;
		Timestamp = NewTimestamp;
		LengthInMS = NewLengthInMS;
		bIsValid = true;
	}

	FGP2_ReplayInfo()
	{
		ReplayName = "Replay";
		FriendlyName = "Replay";
		Timestamp = FDateTime::MinValue();
		LengthInMS = 0;
		bIsValid = false;
	}
};


template<class T>
class CachedProperty
{
public:
	explicit CachedProperty(T value) {
		m_dirty = false;
		m_value = value;
	}

	const T &GetValue() const {
		return m_value;
	}

	void SetValue(const T &value) {
		if (m_value != value) {
			m_value = value;
			m_dirty = true;
		}
	}

	void SetDirty(bool value) {
		m_dirty = value;
	}

	bool IsDirty() const {
		return m_dirty;
	}
protected:
	bool m_dirty;
	T m_value;
};

UENUM(BlueprintType)
enum class PTTKey : uint8
{
	PTTNoChannel,
	PTTAreaChannel,
	PTTTeamChannel
};

//DECLARE_DYNAMIC_DELEGATE_OneParam(FCharacterLoadCompleted, USkeletalMesh*, Mesh);

UCLASS( Blueprintable , BlueprintType ,Config = Game)
class GUNSLINGERSW_API UGP2GameInstance
	:
	public UGameInstance
{
	GENERATED_BODY()

private:
//	TSharedPtr<FSocketIONative> NativeClient;
	EGWGameMode        m_eGameMode;
	bool              m_bGameStart;       
	bool              m_bLocal;           
	int8			  m_iLobbyType;				//	1:normal, 2:test
	int8              m_byEnterUserCount; 
	int32             m_iRoomNumber;      
	FString           m_Subject;          
	FString           m_GameSessionID;    
	FString           m_ServerSystemInfo; 
	FString           m_WebServerIP;      
	FString           m_myDNS;
	FString           m_Map;              
	FString			  m_strcurMaster;
	FString			  m_strcurTitle;


	bool			m_isMatchmakerRoom{ false };	// checking flag of flex match created this game session
	int				m_maximumPlayerSessionCount{ 0 };
	EGWGamePVPRule	m_pvpRule{ EGWGamePVPRule::None };

	TArray< FString > ServerIPList;       

	 

#if WITH_GAMELIFT
	       TSharedPtr <FGameLiftServerSDKModule> gameLiftSdkModule;            

	       int                                   m_port;                       
	       FTimerHandle                          m_timer;
		   FTimerHandle                          m_counttimer;
	       int8                                  m_EmptyGameSessionCheckCount; 
	       bool                                  m_bCheckEmptyGameSession;     

	       TMap<int32, FConnectInfo>             m_ConnectUserList;            
	static int8                                  byInitGameLiftCount;          

	       bool                                  m_bActiveGameLiftSession;     
	       bool                                  m_bSettingMap;                

public:

	void EmptyGameSessionCheckTick();
#endif

	UFUNCTION(BlueprintCallable)
	void GameLiftStartProcess();

	void InitGameData();

	virtual void OnStart();

//<--  test server function
	void WebReq_ServerReg();
	void WebRes_ServerReg(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void WebReq_ServerReuse();
	void WebRes_ServerReuse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void WebReq_RoomEnterUser();
	void WebRes_RoomEnterUser(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void WebReq_RoomOutUser();
	void WebRes_RoomOutUser(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void WebReq_GameStart();
	void WebRes_GameStart(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
//-->
	void WebReq_GameEnd();
	void WebRes_GameEnd(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void WebReq_SendUsercount();
	void WebRes_SendUsercount(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

public:

	UFUNCTION(BlueprintCallable)
	void LoginSessionCheck(const int &PlayerID, const FString &PlayerSessionID, const int &UserSN, bool &CheckResult, int &errorType);

	UFUNCTION(BlueprintCallable)
	void LogoutProcess(const int &PlayerID);

	UFUNCTION(BlueprintPure)
	bool IsLobbyServer();

	UFUNCTION( BlueprintPure )
	bool IsWithEditor();

	UFUNCTION( BlueprintCallable , meta = ( HidePin = "WorldContextObject" , DefaultToSelf = "WorldContextObject" ) )
	static EWebResultEnum ToWebResultEnum(UObject* WorldContextObject, float fValue);

	UFUNCTION(BlueprintCallable)
	bool getGameStart();

	UFUNCTION(BlueprintPure)
	EGWGameMode getGameMode();

	UFUNCTION(BlueprintPure)
	int32 getRoomNumber();

	UFUNCTION(BlueprintPure)
	const FString & getRoomSubject();

	UFUNCTION(BlueprintPure)
	const FString & getGameSession();

	UFUNCTION(BlueprintPure)
	const FString & getServerSystemInfo();

	UFUNCTION(BlueprintPure)
	const FString & getWebURL();

	UFUNCTION(BlueprintPure)
	const FString & getMyDNS();

	UFUNCTION(BlueprintPure)
	int32 getCurrnetTickCount();

	UFUNCTION(BlueprintImplementableEvent)
	void LevelEnterFail(const FString &FailMessage);

	void HandleNetworkFailure(UWorld *World, UNetDriver *NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

	void HandleNetworkError(UWorld * World, UNetDriver * NetDriver, ENetworkFailure::Type FailureType, const FString & ErrorString);

	int8 getEnterUserCount();
	bool getLocal();
	bool getGameLiftActive();

	UFUNCTION( BlueprintPure , Category = "DefaultGame" )
	const bool GetAutoLogin();

	UFUNCTION( BlueprintPure , Category = "DefaultGame" )
	const FString& GetAutoLoginId();

	UFUNCTION( BlueprintPure , Category = "DefaultGame" )
	const bool GetLocalMode();

	UFUNCTION( BlueprintPure , Category = "DefaultGame" )
	const bool GetUsingCharacterArray();

	UFUNCTION( BlueprintPure , Category = "DefaultGame" )
	const int GetDefaultCharacter();

	UFUNCTION( BlueprintPure , Category = "DefaultGame" )
	const TArray<FString> GetDefaultCharacters();

	UFUNCTION( BlueprintPure , Category = "DefaultGame" )
	const bool GetSkipAdvent();

	UFUNCTION( BlueprintPure , Category = "DefaultGame" )
	const bool GetShowDebugArrow();

	UFUNCTION(BlueprintPure, Category = "Server")
	void GetFlexMatchData(int& MapIndex, FString& MapName, int& MaxUserCount, EGWGameMode& GameMode, EGWGamePVPRule& GamePvpRule);

	UFUNCTION(BlueprintPure, Category = "Server")
	void GetCustomMatchData(int& MapIndex, FString& MapName, int& MaxUserCount, EGWGameMode& GameMode, FString& Master, FString& Title);



public:
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly , Category = "UI" )
	UUIManager* UIManager;

public:
	/// ������
	UGP2GameInstance();

	/// �Ҹ���
	virtual ~UGP2GameInstance();


	///-------------------------------------------------------------------------------------------------
	/// UGameInstance's virtual functions
	///-------------------------------------------------------------------------------------------------
	virtual void Init() override;

	virtual void Shutdown() override;

	///-------------------------------------------------------------------------------------------------
	/// 
	///-------------------------------------------------------------------------------------------------
	void Clear() {}
	void NetxWorld() {}
	void MoveToTitle() {}
	void MoveToSelectCharacter() {}


	///-------------------------------------------------------------------------------------------------
	/// getter & setter
	///-------------------------------------------------------------------------------------------------
	APlayerController* GetPlayerController() const;

	/// PC �� ��ȯ�Ѵ�.
	ACharacterPC* GetPlayerCharacterPC();

	/// ĳ���͸� ��ȯ�Ѵ�.
	ACharacter* GetPlayerCharacter();

	/// GameMode�� ��ȯ�Ѵ�.
	AGameMode* GetGP2GameMode();

	/// UI �Ŵ����� ��ȯ�Ѵ�.
	UUIManager* GetUIManager() const { return UIManager; }
public:

	// �񵿱� �ε带 ����ϱ� ���� ���·δ�
	//UPROPERTY()
	FStreamableManager AssetLoader;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FStringAssetReference> CharacterAssets;

	//// ĳ���� �ε����� �ɸ��� �񵿱� �ε�.
	//UFUNCTION()
	//void AsyncCharacterLoad(int CharacterIndex, FCharacterLoadCompleted CompletedFunc);

	

	/**
	* Replay can save infinitly if number is zero.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Replays")
		int32 NumberOfSaveableReplay = 0;

	////// Replay //////

public:

	/** BP���� ����� �����մϴ�.ReplayName = ��ũ���� ���� �̸�, FriendlyName = UI������ ��� �̸� */
	UFUNCTION(BlueprintCallable, DisplayName = "StartRecordingReplay" ,Category = "Replays")
		void StartRecordingReplayFromBP(FString ReplayName, FString FriendlyName);

	/** BP���� �������� ���÷��̸� ��ȭ�ϰ� ����. */
	UFUNCTION(BlueprintCallable, DisplayName = "StopRecordingReplay", Category = "Replays")
		void StopRecordingReplayFromBP();

	/** BP���� ������ ���� �� Replay�� ���� ��� ���� */
	UFUNCTION(BlueprintCallable, DisplayName = "PlayReplay", Category = "Replays")
		void PlayReplayFromBP(FString ReplayName);

	/** �ϵ� ����̺꿡�� ���÷��� �˻� / ã�� ���� */
	UFUNCTION(BlueprintCallable, Category = "Replays")
		void FindReplays();

	/** �� �̸��� ����� �����մϴ�(UI �� �ش�) */
	UFUNCTION(BlueprintCallable, Category = "Replays")
		void RenameReplay(const FString & ReplayName, const FString & NewFriendlyReplayName);

	/** ������ ����� ��� ���� */
	UFUNCTION(BlueprintCallable, Category = "Replays")
		void DeleteReplay(const FString & ReplayName);

	UFUNCTION(BlueprintCallable, Category = "Replays")
		void SaveGameInfo(const FString & ReplayName, const FString& PlayerCharacterName, const FString& PlayedMap);

	UFUNCTION(BlueprintPure, Category = "Replays")
		bool IsReplayPlaying();

	UFUNCTION(BlueprintPure, Category = "Replays")
		bool IsRecording();

	UFUNCTION(BlueprintPure, Category = "GamePad")
		static bool IsGamePadconnected();

	UFUNCTION(BlueprintCallable)
		void TriggerMouseLMBDown();

	UFUNCTION(BlueprintCallable)
		void TriggerMouseLMBUp();

	FOnGotoTimeDelegate GoToTimeCompleteDelegate;
	
protected:

	/** ���÷��� �˻��� �Ϸ�Ǹ� ȣ��� */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "FindReplayComplete", Category = "Replays")
		void BP_OnFindReplaysComplete(const TArray <FGP2_ReplayInfo> & AllReplays);


	UFUNCTION(BlueprintImplementableEvent, DisplayName = "GotoTimeFinished", Category = "Replays")
		void BP_OnGotoTimeFinished(const bool Finished);

private:

	TArray<FString> FindingGameSaveInfo;

	void FindReplayGameInfo(const FString & ReplayName);

	// ���÷��̸� ��û�ϴ� Streamer
	TSharedPtr<INetworkReplayStreamer> EnumerateStreamsPtr;

	FEnumerateStreamsCallback OnEnumerateStreamsCompleteDelegate;

	//FindReplays() �� ������ִ� delegate
	void OnEnumerateStreamsComplete(const FEnumerateStreamsResult& StreamResult);

	FDeleteFinishedStreamCallback OnDeleteFinishedStreamCompleteDelegate;

	//DeleteReplay �� ������ִ� delegate
	void OnDeleteFinishedStreamComplete(const FDeleteFinishedStreamResult& DeleteFinish);


	//GoToTimeCompleteDelegate �� ����Ǿ��ִ� �Լ�
	void OnGotoTimeFinished(const bool FinishRoad);

	// Display EAC client messages.
	bool EACErrorProc(const FString& Message);

public:
	UFUNCTION( BlueprintCallable , Category = "Json Security" )
	const bool GetJsonSecurity( int InIndex );

public:
	UFUNCTION( BlueprintCallable , Category = "Server" )
	FString GetServerAddress( int InIndex );

public:
	UFUNCTION( BlueprintPure , Category = "Matchmaking")
	bool IsMatchmakerRoom() { return m_isMatchmakerRoom; };

	UFUNCTION( BlueprintPure , Category = "Matchmaking")
	int GetMaximumPlayerSessionCount() { return m_maximumPlayerSessionCount; };
	
	UFUNCTION( BlueprintPure , Category = "Matchmaking")
	FString GetMapName() { return m_Map; };
	
	

	//UFUNCTION(BlueprintCallable, Category = "Matchmaking")
	//EGWGamePVPRule GetPvpRule() { return m_pvpRule; };

#if !WITH_GAMELIFT
private:
	bool bInitialized;
	bool bInitializing;

	bool bLoggedIn;
	bool bLoggingIn;

	IClient *VivoxVoiceClient;
	AccountId LoggedInAccountID;
	FString LoggedInPlayerName;

	TPair<ChannelId, bool> PTTAreaChannel;
	TPair<ChannelId, bool> PTTTeamChannel;
	ChannelId ConnectedPositionalChannel; // You can only be in one Positional channel at a time.
	ChannelId LastKnownTransmittingChannel;

public:

	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegateSetActiveDevicechange, int32, const FString &)

	//FDelegateSetActiveDevicechange FOnVivoxInputDeviceChanged;

	/// Runtime console commands.
	virtual bool Exec(UWorld* Inworld, const TCHAR* Cmd, FOutputDevice& Ar) override;

	virtual bool IsInitialized();
	virtual bool IsLoggedIn();


	void OnLoginSessionStateChanged(LoginState State);
	void OnChannelParticipantAdded(const IParticipant& Participant);
	void OnChannelParticipantRemoved(const IParticipant& Participant);
	void OnChannelParticipantUpdated(const IParticipant& Participant);
	void OnChannelAudioStateChanged(const IChannelConnectionState& State);
	void OnChannelTextStateChanged(const IChannelConnectionState& State);
	void OnChannelTextMessageReceived(const IChannelTextMessage& Message);



	ILoginSession *GetVivoxLoginSessionForRoster();
	TSharedPtr<IChannelSession> GetVivoxChannelSessionForRoster();
	ChannelId GetLastKnownTransmittingChannel() { return LastKnownTransmittingChannel; }

	void BindLoginSessionHandlers(bool DoBind, ILoginSession& LoginSession);
	void BindChannelSessionHandlers(bool DoBind, IChannelSession& ChannelSession);
#endif


	UFUNCTION(BlueprintCallable)
		int32 Vivox_Initialize(int logLevel);

	UFUNCTION(BlueprintCallable)
		void Vivox_Uninitialize();

	UFUNCTION(BlueprintCallable)
		int32 Vivox_Login(const FString& PlayerName);

	UFUNCTION(BlueprintCallable)
		void Vivox_Logout();

	//UFUNCTION(BlueprintCallable)
	//int32 JoinVoiceChannels(FString GameMode, FString OnlineSessionId, int32 TeamNum = -1);
	UFUNCTION(BlueprintCallable)
		int32 Vivox_Join(int iChannelType, bool ShouldTransmitOnJoin, const FString& ChannelName, PTTKey AssignChanneltoPTTKey = PTTKey::PTTNoChannel);

	UFUNCTION(BlueprintCallable)
		void LeaveVoiceChannels();

	UFUNCTION(BlueprintCallable)
		int32 MultiChanPushToTalk(PTTKey Key, bool PTTKeyPressed);

	UFUNCTION(BlueprintCallable)
		int32 MultiChanToggleChat(PTTKey Key);

	UFUNCTION(BlueprintCallable)
		bool SetVivoxPlayerMuted(const FString& PlayerName, bool MuteState);

	UFUNCTION(BlueprintCallable)
		int32 GetVoiceMicVolume();

	UFUNCTION(BlueprintCallable)
		void SetVoiceMicVolume(int MicVolumeValue);

	UFUNCTION(BlueprintCallable)
		int32 GetVoiceOutputVolume();

	UFUNCTION(BlueprintCallable)
		void SetVoiceOutputVolume(int OutputVolumeValue);

	UFUNCTION(BlueprintCallable)
		TMap<FString, FString> GetVivoxInputAudioDevices();

	UFUNCTION(BlueprintCallable)
		FString GetCurVivoxInputAudioDevice();

	UFUNCTION(BlueprintCallable)
		TMap<FString, FString> GetVivoxOutputAudioDevices();

	UFUNCTION(BlueprintCallable)
		FString GetCurVivoxOutputAudioDevice();

	UFUNCTION(BlueprintCallable)
		int32 SetVivoxInputDeviceChange(FString strDeviceID);// , const FOnVivoxInputDeviceChanged& theDelegate = FOnVivoxInputDeviceChanged());
	
	UFUNCTION(BlueprintImplementableEvent)
		void VivoxDeviceChangeComplete(const FString& strDeviceID);

	UFUNCTION(BlueprintImplementableEvent)
		void VivoxPushtoTalkState(const FString& PlayerName, bool isSpeaking, bool isMy);

	UFUNCTION(BlueprintImplementableEvent)
		void VivoxChannelAdded(const FString& PlayerName, bool isMy);

	UFUNCTION(BlueprintImplementableEvent)
		void VivoxChannelRemoved(const FString& PlayerName, bool isMy);

	UFUNCTION(BlueprintImplementableEvent)
		void VivoxchannelConneced();

	UFUNCTION(BlueprintImplementableEvent)
		void VivoxLogined();



public:
	int CurrentLevelInfoId;  /// ���� �������� �����ĺ���
	int PrevLevelInfoId;     /// ���� �������� �����ĺ���
	int ReservedLevelInfoId; /// ���� �������� �����ĺ���


public:
	/// ���� �������� �����ĺ��ڸ� �����Ѵ�.
 	UFUNCTION( BlueprintCallable  , Category = "Guns2W|Stage" )
	void SetCurrentLevelInfoId( int _CurrentLevelInfoId ) { CurrentLevelInfoId = _CurrentLevelInfoId; }

	/// ���� �������� �����ĺ��ڸ� �����Ѵ�.
	UFUNCTION( BlueprintCallable , Category = "Guns2W|Stage" )
	void SetPrevLevelInfoId( int _PrevLevelInfoId ) { PrevLevelInfoId = _PrevLevelInfoId; }

	/// ���� �������� �����ĺ��ڸ� �����Ѵ�.
	UFUNCTION( BlueprintCallable , Category = "Guns2W|Stage" )
	void SetReservedLevelInfoId( int _ReservedLevelInfoId ) { ReservedLevelInfoId = _ReservedLevelInfoId; }

	/// ���� �������� �����ĺ��ڸ� ��ȯ�Ѵ�.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "Guns2W|Stage" )
	int GetCurrentLevelInfoId() const { return CurrentLevelInfoId; }

	/// ���� �������� �����ĺ��ڸ� ��ȯ�Ѵ�.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "Guns2W|Stage" )
	int GetPrevLevelInfoId() const { return PrevLevelInfoId; }

	/// ���� �������� �����ĺ��ڸ� ��ȯ�Ѵ�.
 	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "Guns2W|Stage" )
	int GetReservedLevelInfoId() const { return ReservedLevelInfoId; }

};

