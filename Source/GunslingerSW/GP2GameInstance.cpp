// Fill out your copyright notice in the Description page of Project Settings.

#include "GP2GameInstance.h"
#include "GunslingerSW.h"
#include "UI/UIManager.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/GameMode.h>
#include "Runtime/NetworkReplayStreaming/NullNetworkReplayStreaming/Public/NullNetworkReplayStreaming.h"
#include "NetworkVersion.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "Runtime/Core/Public/Serialization/MemoryReader.h"
#include "Runtime/Slate/Public/Framework/Application/SlateApplication.h"
#include "Engine.h"
#include "Kismet/KismetSystemLibrary.h"

#include "IEasyAntiCheatClient.h"
#include "IEasyAntiCheatServer.h"

#include "GameMode/GP2GMBase.h"

#if !WITH_GAMELIFT 
#include "Vivox/VivoxToken.h"
#endif

#if WITH_GAMELIFT
#include "SIOJsonValue.h"
int8 UGP2GameInstance::byInitGameLiftCount = 0;
#endif

/// Return the full name of a UEnum value as an FString
template<typename TEnum>
static FORCEINLINE FString GetUEnumAsString(const FString& Name, TEnum Value, bool ShortName)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!enumPtr)
		return FString("InvalidUEnum");
	if (ShortName)
		return enumPtr->GetNameStringByIndex((int64)Value);
	return enumPtr->GetNameByValue((int64)Value).ToString();
}
#define UEnumFullToString(Name, Value) GetUEnumAsString<Name>(#Name, Value, false)
#define UEnumShortToString(Name, Value) GetUEnumAsString<Name>(#Name, Value, true)


UGP2GameInstance::UGP2GameInstance()
{
	GP2LoadGlobals();
	GP2AppInit();

	InitGameData();
	
	m_iRoomNumber = 0;
	m_Subject.Empty();
	m_myDNS = "127.0.0.1:7501";
	m_WebServerIP = "127.0.0.1:3001";
	m_WebServerIP = g_LocalServerAddr;

	GetServerAddress( 0 );

#if WITH_GAMELIFT

	m_bActiveGameLiftSession = false;
	m_bSettingMap = false;
	m_Map = NULL;
	m_eGameMode = EGWGameMode::PVP;
	m_iLobbyType = 0;	//	1:normal, 2:test

	FParse::Bool(FCommandLine::Get(), TEXT("local="), m_bLocal);

	FString strweb = "";
	int iLobbyType = 0;
	if ( FParse::Value( FCommandLine::Get() , TEXT( "web=" ) , strweb ) )
	{
		m_WebServerIP = strweb;
	}

	FString strdns = "";
	if ( FParse::Value( FCommandLine::Get() , TEXT( "dns=" ) , strdns ) )
	{
		m_myDNS = strdns;
	}

	FParse::Value( FCommandLine::Get() , TEXT( "LobbyType=" ) , m_iLobbyType );

	UE_LOG( LogTemp , Log , TEXT( "LOBBY START : TYPE - %d : Web : %s" ) , m_iLobbyType , *strweb );


	/*
	FString				m_testMap;
	FString				m_testMode;
	FString				m_testRule;

	// EGWGameMode			m_etestGameMode;

	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create("{\"matchId\":\"a232844b-d049-4542-a92f-ee653a0bd687\",\"matchmakingConfigurationArn\":\"arn:aws:gamelift:ap-northeast-1:610306897249:matchmakingconfiguration/PvpTestForDev1vs1\",\"teams\":[{\"name\":\"BLUE\",\"players\":[{\"playerId\":\"1\",\"attributes\":{\"gamemap\":{\"attributeType\":\"STRING_LIST\",\"valueAttribute\":[\"G2_P_GoldenBridge\"]},\"gamemode\":{\"attributeType\":\"STRING\",\"valueAttribute\":\"Deathmatch\"},\"gamerule\":{\"attributeType\":\"STRING_LIST\",\"valueAttribute\":[\"Deathmatch\",\"Capture\"]},\"matchmode\":{\"attributeType\":\"STRING\",\"valueAttribute\":\"PvpTestForDev1vs1\"}}}]},{\"name\":\"RED\",\"players\":[{\"playerId\":\"2\",\"attributes\":{\"gamemap\":{\"attributeType\":\"STRING_LIST\",\"valueAttribute\":[\"G2_P_GoldenBridge\"]},\"gamemode\":{\"attributeType\":\"STRING\",\"valueAttribute\":\"Deathmatch\"},\"gamerule\":{\"attributeType\":\"STRING_LIST\",\"valueAttribute\":[\"Deathmatch\",\"Capture\"]},\"matchmode\":{\"attributeType\":\"STRING\",\"valueAttribute\":\"PvpTestForDev1vs1\"}}}]}],\"autoBackfillMode\":null,\"autoBackfillTicketId\":null}");
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());
	if (FJsonSerializer::Deserialize(reader, jsonObj) && jsonObj.IsValid())
	{
		TArray<TSharedPtr<FJsonValue>> teams = jsonObj->GetArrayField("teams");

		if (0 != teams.Num())
		{
			TSharedPtr<FJsonObject> teamsobj = teams[0]->AsObject();
			TArray<TSharedPtr<FJsonValue>> players = teamsobj->GetArrayField("players");
			if (0 != players.Num())
			{
				TSharedPtr<FJsonObject> playersobj = players[0]->AsObject();
				TSharedPtr<FJsonObject> attributes = playersobj->GetObjectField("attributes");
				if (nullptr != attributes)
				{
					// TSharedPtr<FJsonObject> attributesobj = attributes->AsObject();
					TSharedPtr<FJsonObject> gamemap = attributes->GetObjectField("gamemap");
					if (nullptr != gamemap)
					{
						// string array 형태로 되어 있기 때문에, 다수의 맵이 들어 올 수 있음
						// 예시) 1번 플레이어는 A, B 맵을 좋아하고, 2번 플레이어는 B, C 맵을 좋아할때 교집합으로 B 가 걸렸을 수 있음
						// 따라서 하위 코드는 무조건 플레이어들이 1개의 맵을 입력하여 매칭을 돌렸을 가정에 한정하여 동작함
						TArray<FString> map;
						if (true == gamemap->TryGetStringArrayField("valueAttribute", map))
						{
							m_testMap = map[0];

							// UE_LOG(LogTemp, Log, TEXT("map : %s"), m_Map);
						}
					}

					TSharedPtr<FJsonObject> matchmode = attributes->GetObjectField("matchmode");
					if (nullptr != matchmode)
					{
						FString mode = matchmode->GetStringField("valueAttribute");
						if (false == mode.IsEmpty())
						{
							m_testMode = mode;
							//switch (mode)
							//{
							//case "PVP": m_eGameMode = EGWGameMode::PVP; break;
							//case "PVE": m_eGameMode = EGWGameMode::PVE; break;
							//case "TUTORIAL": m_eGameMode = EGWGameMode::TUTORIAL; break;
							//default: // 여기 오면 안되는뎅;; 
							//	break;
							//}

							int ii = 0;


							// UE_LOG(LogTemp, Log, TEXT("mode : %s"), mode);

						}
					}

					const TSharedPtr<FJsonObject>* gamerule;
					if (true == attributes->TryGetObjectField("gamerule", gamerule))
					{
						TArray<FString> pvprule;
						if (gamerule && (*gamerule)->TryGetStringArrayField("valueAttribute", pvprule))
						{
							if (0 != pvprule.Num())
							{
								int ii = 0;
								
								//FString rule = pvprule[0];
								//switch (rule)
								//{
								//case "Deathmatch": m_pvpRule = EGWGamePVPRule::Deathmatch; break;
								//case "Capture": m_pvpRule = EGWGamePVPRule::Capture; break;
								//default: m_pvpRule = EGWGamePVPRule::None; break;
								//}
								
								m_testRule = pvprule[0];
							}
						}
					}
				}
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("LOBBY START : map - %s : mode - %s : rule - %s"), *m_testMap, *m_testMode, *m_testRule);
	*/


	m_bCheckEmptyGameSession = false;

	if (byInitGameLiftCount < 2)
	{
		byInitGameLiftCount++;
		return;
	}

	int port = 0;

	if (!FParse::Value(FCommandLine::Get(), TEXT("port="), port))
	{
		if (m_iLobbyType > 0) port = 7501;
		else port = 7777;
	}

	m_port = port;

	UE_LOG(LogTemp, Log, TEXT("UGP2GameInstance : port - %d"), m_port);

#endif	//	#if WITH_GAMELIFT

}

void UGP2GameInstance::HandleNetworkFailure(UWorld *World, UNetDriver *NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	UE_LOG(LogTemp, Error, TEXT("LevelEnterFail : %s"), *ErrorString);

	LevelEnterFail(ErrorString);

}

void UGP2GameInstance::HandleNetworkError(UWorld * World, UNetDriver * NetDriver, ENetworkFailure::Type FailureType, const FString & ErrorString)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetworkFailure"), true);
 
	if (EnumPtr == nullptr)
	{
		return;
	}

	FString FailureTypeString = (EnumPtr->GetNameByValue((int64)FailureType)).ToString();

	UE_LOG(LogTemp, Error, TEXT("GP2 NetworkFailure FailureType : %s"), *FailureTypeString);

	UE_LOG(LogTemp, Error, TEXT("GP2 NetworkFailure ErrorString : %s"), *ErrorString);
}

UGP2GameInstance::~UGP2GameInstance()
{
	GP2AppExit();
}

void UGP2GameInstance::Init()
{
	Super::Init();

	UIManager = NewObject< UUIManager >();
	UIManager->AddToRoot();

	EnumerateStreamsPtr = FNetworkReplayStreaming::Get().GetFactory().CreateReplayStreamer();

	OnEnumerateStreamsCompleteDelegate = FEnumerateStreamsCallback::CreateUObject(this, &UGP2GameInstance::OnEnumerateStreamsComplete);

	OnDeleteFinishedStreamCompleteDelegate = FDeleteFinishedStreamCallback::CreateUObject(this, &UGP2GameInstance::OnDeleteFinishedStreamComplete);

	GoToTimeCompleteDelegate = FOnGotoTimeDelegate::CreateUObject(this, &UGP2GameInstance::OnGotoTimeFinished);

	if (GEngine != nullptr)
	{
		GEngine->OnNetworkFailure().AddUObject(this, &UGP2GameInstance::HandleNetworkError);

	}
	
	// Set up UI integration for displaying errors.
	if (IEasyAntiCheatClient::IsAvailable())
	{
		IEasyAntiCheatClient::Get().ErrorDelegate.BindUObject(this, &UGP2GameInstance::EACErrorProc);
	}
}

void UGP2GameInstance::Shutdown()
{
	Super::Shutdown();
}

void UGP2GameInstance::InitGameData()
{
#if WITH_GAMELIFT

	//if(!m_bLocal)
	m_GameSessionID.Empty();

	m_byEnterUserCount = 0;
	m_bGameStart = false;
	m_bCheckEmptyGameSession = false;
	m_EmptyGameSessionCheckCount = 0;

#endif
}

APlayerController* UGP2GameInstance::GetPlayerController() const
{
	UWorld* world = GetWorld();
	if ( !world )
		return nullptr;

	return UGameplayStatics::GetPlayerController( world , 0 );
}

ACharacterPC* UGP2GameInstance::GetPlayerCharacterPC()
{
	UWorld* world = GetWorld();
	if ( !world )
		return nullptr;

	ACharacter* character = UGameplayStatics::GetPlayerCharacter( world , 0 );

	if ( ACharacterPC* pc = Cast< ACharacterPC >( character ) )
		return pc;

	return nullptr;
}

ACharacter* UGP2GameInstance::GetPlayerCharacter()
{
	UWorld* world = GetWorld();
	if ( !world )
		return nullptr;

	return UGameplayStatics::GetPlayerCharacter( world , 0 );
}

AGameMode* UGP2GameInstance::GetGP2GameMode()
{
	UWorld* world = GetWorld();
	if ( !world )
		return nullptr;

	return Cast< AGameMode >( UGameplayStatics::GetGameMode( world ) );
}

////////////////////////////////////////////Replay function //////////////////////////////////////////////

void UGP2GameInstance::StartRecordingReplayFromBP(FString ReplayName, FString FriendlyName)
{
	
	StartRecordingReplay(ReplayName, FriendlyName);

}

void UGP2GameInstance::StopRecordingReplayFromBP()
{
	StopRecordingReplay();

	FindReplays();
}

void UGP2GameInstance::PlayReplayFromBP(FString ReplayName)
{
	PlayReplay(ReplayName);
}

void UGP2GameInstance::FindReplays()
{
	if (EnumerateStreamsPtr.Get() != nullptr)
	{
		EnumerateStreamsPtr.Get()->EnumerateStreams(FNetworkReplayVersion(), 0, FString(), TArray< FString >(), OnEnumerateStreamsCompleteDelegate);
	}
}

void UGP2GameInstance::RenameReplay(const FString & ReplayName, const FString & NewFriendlyReplayName)
{
	// Get File Info
	FNullReplayInfo Info;

	const FString DemoPath = FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("Demos/"));
	const FString StreamDirectory = FPaths::Combine(*DemoPath, *ReplayName);
	const FString StreamFullBaseFilename = FPaths::Combine(*StreamDirectory, *ReplayName);
	const FString InfoFilename = StreamFullBaseFilename + TEXT(".replayinfo");

	TUniquePtr<FArchive> InfoFileArchive(IFileManager::Get().CreateFileReader(*InfoFilename));

	if (InfoFileArchive.IsValid() && InfoFileArchive->TotalSize() != 0)
	{
		FString JsonString;
		*InfoFileArchive << JsonString;

		Info.FromJson(JsonString);
		Info.bIsValid = true;

		InfoFileArchive->Close();
	}

	// Set FriendlyName
	Info.FriendlyName = NewFriendlyReplayName;

	// Write File Info
	TUniquePtr<FArchive> ReplayInfoFileAr(IFileManager::Get().CreateFileWriter(*InfoFilename));

	if (ReplayInfoFileAr.IsValid())
	{
		FString JsonString = Info.ToJson();
		*ReplayInfoFileAr << JsonString;

		ReplayInfoFileAr->Close();
	}

}

void UGP2GameInstance::DeleteReplay(const FString & ReplayName)
{
	if (EnumerateStreamsPtr.Get())
	{
		EnumerateStreamsPtr.Get()->DeleteFinishedStream(ReplayName, OnDeleteFinishedStreamCompleteDelegate);
	}
}

void UGP2GameInstance::SaveGameInfo(const FString & ReplayName , const FString& PlayerCharacterName, const FString& PlayedMap)
{

	const FString DemoPath = FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("Demos/"));
	const FString StreamDirectory = FPaths::Combine(*DemoPath, *ReplayName);

	const FString SaveFileName = TEXT("ReplayInfo.sav");

	bool AllowOverwriting = false;

    TArray<FString> SaveInfo;

	SaveInfo.Add(PlayerCharacterName);
	SaveInfo.Add(PlayedMap);

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		// Get absolute file path
		FString AbsoluteFilePath = StreamDirectory + "/" + SaveFileName;

		// Allow overwriting or file doesn't already exist
		if (AllowOverwriting || !PlatformFile.FileExists(*AbsoluteFilePath))
		{
			FFileHelper::SaveStringArrayToFile(SaveInfo, *AbsoluteFilePath);
		}

}

bool UGP2GameInstance::IsReplayPlaying()
{
	if (GetWorld()->DemoNetDriver != nullptr)
	{
		return GetWorld()->DemoNetDriver->IsPlaying();

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DemoNetDriver Is Null"));
	}
	
	return false;
}

bool UGP2GameInstance::IsRecording()
{


	if (GetWorld()->DemoNetDriver != nullptr)
	{
		return GetWorld()->DemoNetDriver->IsRecording();

		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DemoNetDriver Is Null"));
	}

	return false;
}

bool UGP2GameInstance::IsGamePadconnected()
{
	auto genericApplication = FSlateApplication::Get().GetPlatformApplication();
	if (genericApplication.Get() != nullptr && genericApplication->IsGamepadAttached())
	{
		return true;
	}
	return false;
}

void UGP2GameInstance::TriggerMouseLMBDown()
{
	//trigger the mouse click event. This will fire any lmb click events within blueprints.
	FViewportClient* Client = GEngine->GameViewport->Viewport->GetClient();
	FKey MouseLMB = EKeys::LeftMouseButton;
	Client->InputKey(GEngine->GameViewport->Viewport, 0, MouseLMB, EInputEvent::IE_Pressed);

	TSet<FKey> PressedMouseButtons = TSet<FKey>();

	//Trigger mouse clicks in UI
//Get our slate application
	FSlateApplication& SlateApp = FSlateApplication::Get();

	//create a pointer event
	FPointerEvent MouseDownEvent(
		0,
		SlateApp.CursorPointerIndex,
		SlateApp.GetCursorPos(),
		SlateApp.GetLastCursorPos(),
	    PressedMouseButtons,
		EKeys::LeftMouseButton,
		0,
		SlateApp.GetPlatformApplication()->GetModifierKeys()
	);

	//send the mouse event to the slate handler
	TSharedPtr<FGenericWindow> GenWindow;
	SlateApp.ProcessMouseButtonDownEvent(GenWindow, MouseDownEvent);

}

void UGP2GameInstance::TriggerMouseLMBUp()
{
	//trigger the mouse click release event
	FViewportClient* Client = GEngine->GameViewport->Viewport->GetClient();
	FKey MouseLMB = EKeys::LeftMouseButton;
	Client->InputKey(GEngine->GameViewport->Viewport, 0, MouseLMB, EInputEvent::IE_Released);

	TSet<FKey> PressedMouseButtons = TSet<FKey>();

	//trigger the UI mouse click
	FSlateApplication& SlateApp = FSlateApplication::Get();

	FPointerEvent MouseUpEvent(
		0,
		SlateApp.CursorPointerIndex,
		SlateApp.GetCursorPos(),
		SlateApp.GetLastCursorPos(),
		PressedMouseButtons,
		EKeys::LeftMouseButton,
		0,
		SlateApp.GetPlatformApplication()->GetModifierKeys()
	);

	TSharedPtr<FGenericWindow> GenWindow;
	SlateApp.ProcessMouseButtonUpEvent(MouseUpEvent);
}

void UGP2GameInstance::FindReplayGameInfo(const FString & ReplayName)
{
	const FString DemoPath = FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("Demos/"));
	const FString StreamDirectory = FPaths::Combine(*DemoPath, *ReplayName);
	const FString SaveFileName = TEXT("ReplayInfo.sav");

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	FString AbsoluteFilePath = StreamDirectory + "/" + SaveFileName;

	//파일있는지 검증 없으면 info 배열에 임시 내용을 넣는다
	if (PlatformFile.FileExists(*AbsoluteFilePath))
	{
		FFileHelper::LoadFileToStringArray(FindingGameSaveInfo, *AbsoluteFilePath);
	}
	else
	{
		FindingGameSaveInfo.Add(FString("EmptyCharacterName"));
		FindingGameSaveInfo.Add(FString("EmptyMapName"));
	}

}

void UGP2GameInstance::OnEnumerateStreamsComplete(const FEnumerateStreamsResult& StreamResult)
{

	const TArray<FNetworkReplayStreamInfo>& StreamInfos = StreamResult.FoundStreams;

	TArray<FGP2_ReplayInfo> AllReplays;


	if (StreamInfos.Num() == 0)
	{
		return;
	}

	if (NumberOfSaveableReplay != 0)
	{
		if (StreamInfos.Num() > NumberOfSaveableReplay)
		{

			DeleteReplay(StreamInfos[0].Name);

		}
	}

		for (int32 Index = StreamInfos.Num() - 1; Index >= 0; Index--)
		{
			if (!StreamInfos[Index].bIsLive)
			{
				FindReplayGameInfo(StreamInfos[Index].Name);

				AllReplays.Add(FGP2_ReplayInfo(StreamInfos[Index].Name, StreamInfos[Index].FriendlyName, FString::FromInt(StreamInfos[Index].SizeInBytes),
					FindingGameSaveInfo[0], FindingGameSaveInfo[1], StreamInfos[Index].Timestamp, StreamInfos[Index].LengthInMS));

			}

		}
		
		BP_OnFindReplaysComplete(AllReplays);

}

void UGP2GameInstance::OnDeleteFinishedStreamComplete(const FDeleteFinishedStreamResult& DeleteFinish)
{
	//FindReplays();
}

void UGP2GameInstance::OnGotoTimeFinished(const bool FinishRoad)
{
	BP_OnGotoTimeFinished(FinishRoad);
}

void UGP2GameInstance::OnStart()
{
	if (!IsDedicatedServerInstance())
	{
		UE_LOG(LogTemp, Error, TEXT("UGP2GameInstance::OnStart HandleNetworkFailure Add"));
		GEngine->OnNetworkFailure().AddUObject(this, &UGP2GameInstance::HandleNetworkFailure);
	}

#if WITH_GAMELIFT

	FString strAddress = GetWorld()->GetAddressURL();
	FString strPort = "0";

	int index = 0;
	if (strAddress.FindChar(':', index))
	{
		strPort = strAddress.Mid(index + 1);
		m_port = (int)FCString::Atoi(*strPort);
	}

	// UE_LOG(LogTemp, Log, TEXT("GP2GameInstance:OnStart port : [%s]"), *strAddress);
	UE_LOG(LogTemp, Log, TEXT("GP2GameInstance:OnStart port : [%d]"), m_port);
	FString dnsData = FString::Printf(TEXT("%s:%d"), *m_myDNS, m_port);
	m_myDNS = dnsData;
	UE_LOG(LogTemp, Log, TEXT("GP2GameInstance:OnStart myDNS : [%s]"), *m_myDNS);

	if (m_iLobbyType == 0)
	{
		gameLiftSdkModule = MakeShareable(new FGameLiftServerSDKModule);

		//InitSDK establishes a local connection with GameLift's agent to enable further communication.
		gameLiftSdkModule->InitSDK();

		if (!this->GetTimerManager().IsTimerActive(m_timer))
			this->GetTimerManager().SetTimer(m_timer, this, &UGP2GameInstance::EmptyGameSessionCheckTick, 1, true);

		auto onGameSession = [=](Aws::GameLift::Server::Model::GameSession gameSession)
		{
			//UE_LOG(LogTemp, Log, TEXT("GetGameSessionData %s"), ANSI_TO_TCHAR(gameSession.GetGameSessionData()));

			const FString& matchmakingJsonData = gameSession.GetMatchmakerData();
			m_isMatchmakerRoom = matchmakingJsonData.IsEmpty() ? false : true;

			if (m_isMatchmakerRoom)		// flex match setting
			{
				TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(gameSession.GetMatchmakerData());
				TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());
				if (FJsonSerializer::Deserialize(reader, jsonObj) && jsonObj.IsValid())
				{
					TArray<TSharedPtr<FJsonValue>> teams = jsonObj->GetArrayField("teams");

					if (0 != teams.Num())
					{
						TSharedPtr<FJsonObject> teamsobj = teams[0]->AsObject();
						TArray<TSharedPtr<FJsonValue>> players = teamsobj->GetArrayField("players");
						if (0 != players.Num())
						{
							TSharedPtr<FJsonObject> playersobj = players[0]->AsObject();
							TSharedPtr<FJsonObject> attributes = playersobj->GetObjectField("attributes");
							if (nullptr != attributes)
							{
								TSharedPtr<FJsonObject> gamemap = attributes->GetObjectField("gamemap");
								if (nullptr != gamemap)
								{
									// string array 형태로 되어 있기 때문에, 다수의 맵이 들어 올 수 있음
									// 예시) 1번 플레이어는 A, B 맵을 좋아하고, 2번 플레이어는 B, C 맵을 좋아할때 교집합으로 B 가 걸렸을 수 있음
									// 따라서 하위 코드는 무조건 플레이어들이 1개의 맵을 입력하여 매칭을 돌렸을 가정에 한정하여 동작함
									TArray<FString> map;
									if (true == gamemap->TryGetStringArrayField("valueAttribute", map))
									{
										m_Map = map[0];
									}
								}

								TSharedPtr<FJsonObject> matchmode = attributes->GetObjectField("matchmode");
								if (nullptr != matchmode)
								{
									FString mode = matchmode->GetStringField("valueAttribute");
									if (false == mode.IsEmpty())
									{
										if(mode.Equals(TEXT("PVP"), ESearchCase::CaseSensitive)) m_eGameMode = EGWGameMode::PVP;
										else if (mode.Equals(TEXT("PVE"), ESearchCase::CaseSensitive)) m_eGameMode = EGWGameMode::PVE;
										else if (mode.Equals(TEXT("TUTORIAL"), ESearchCase::CaseSensitive)) m_eGameMode = EGWGameMode::TUTORIAL;
									}
								}

								const TSharedPtr<FJsonObject>* gamerule;
								if (true == attributes->TryGetObjectField("gamerule", gamerule))
								{
									TArray<FString> pvprule;
									if (gamerule && (*gamerule)->TryGetStringArrayField("valueAttribute", pvprule))
									{
										if (0 != pvprule.Num())
										{
											FString rule = pvprule[0];
											if (rule.Equals(TEXT("Deathmatch"), ESearchCase::CaseSensitive)) m_pvpRule = EGWGamePVPRule::Deathmatch;
											else if (rule.Equals(TEXT("Capture"), ESearchCase::CaseSensitive)) m_pvpRule = EGWGamePVPRule::Capture;
											else m_pvpRule = EGWGamePVPRule::None;
										}
									}
								}
							}
						}
					}
				}
			}
			else						// custom match setting
			{

				int count = 0;

				auto getProperty = gameSession.GetGameProperties(count);

				UWorld* world = this->GetWorld();

				for (int i = 0; i < count; i++)
				{
					if (strcmp(getProperty[i].GetKey(), "mode") == 0)
					{
						if (strcmp(getProperty[i].GetValue(), "PVP") == 0)
						{
							UE_LOG(LogTemp, Log, TEXT("PVP MODE"));

							m_eGameMode = EGWGameMode::PVP;
						}
						else if (strcmp(getProperty[i].GetValue(), "TUTORIAL") == 0)
						{
							UE_LOG(LogTemp, Log, TEXT("TUTORIAL MODE"));

							m_eGameMode = EGWGameMode::TUTORIAL;
						}
						else
						{
							UE_LOG(LogTemp, Log, TEXT("PVE MODE"));

							m_eGameMode = EGWGameMode::PVE;
						}
					}

					if (strcmp(getProperty[i].GetKey(), "serverip") == 0)
					{
						m_WebServerIP = getProperty[i].GetValue();
					}

					/*
					if (strcmp(getProperty[i].GetKey(), "Map") == 0)
					{
						m_Map = getProperty[i].GetValue();
					}
					*/

					//UE_LOG(LogTemp, Log, TEXT("Property key : %s , value : %s"), ANSI_TO_TCHAR(getProperty[i].GetKey()), getProperty[i].GetValue());
				}

				m_Subject = gameSession.GetName();
				UE_LOG(LogTemp, Log, TEXT("void UGP2GameInstance::OnStart() Custommatch subject : %s"), *m_Subject);

				TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(m_Subject);
				TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());
				if (FJsonSerializer::Deserialize(reader, jsonObj) && jsonObj.IsValid())
				{
					m_strcurTitle = jsonObj->GetStringField("title");			// 방제목
					m_Map = jsonObj->GetStringField("Map");					// 맵이름
					m_strcurMaster = jsonObj->GetStringField("master");		// 방장
				}

				UE_LOG(LogTemp, Log, TEXT("void UGP2GameInstance::OnStart() Custommatch Data!!!! , %s %s %s"), *m_Map, *m_strcurMaster, *m_strcurTitle);
			}

			//UE_LOG(LogTemp, Log, TEXT("Is Room Created Matchmaker : %d"), m_isMatchmakerRoom);
			//UE_LOG(LogTemp, Log, TEXT("Room Max Player count : %d"), gameSession.GetMaximumPlayerSessionCount());
			//UE_LOG(LogTemp, Log, TEXT("LOBBY START : map - %s : mode - %s : rule - %s"), *m_testMap, *m_testMode, *m_testRule);

			InitGameData();

			m_iRoomNumber = atoi(gameSession.GetGameSessionData());
			m_GameSessionID = gameSession.GetGameSessionId();
			m_maximumPlayerSessionCount = gameSession.GetMaximumPlayerSessionCount();
			m_bCheckEmptyGameSession = true;
			m_bActiveGameLiftSession = true;
			m_bSettingMap = false;
			//gameLiftSdkModule->ActivateGameSession();

			/// by evilkiki 게임모드 초기화 함수 콜.
			// AGameMode * pGamemode = GetWorld()->GetAuthGameMode();

			/*	gamemode에서 호출하는 방식으로 진행하자. 여기서 set 했지만 gamemode에서 이후 초기화해서 문제가 되었음.
			//	대신 Get함수로 제공하자. GetFlexMatchData, GetCustomMatchData
			AGP2GMBase * pGamemode = Cast< AGP2GMBase >( GetWorld()->GetAuthGameMode() );

			if ( pGamemode )
			{
				UE_LOG( LogTemp , Log , TEXT( "void UGP2GameInstance::OnStart() Call Data!!!! , %s" ) , *m_Map);

				if ( m_isMatchmakerRoom )
					pGamemode->SetFlexMatchData( 1 , m_Map , m_maximumPlayerSessionCount , m_eGameMode , m_pvpRule );
				else
					pGamemode->SetCustomMatchData( 1 , m_Map , m_maximumPlayerSessionCount , m_eGameMode , strcurMaster, strcurTitle);

				UE_LOG(LogTemp, Log, TEXT("void UGP2GameInstance::OnStart() Call Data!!!! , %s"), *pGamemode->GetStageName());
			}
			else
			{
				UE_LOG( LogTemp , Log , TEXT( "void UGP2GameInstance::OnStart() - Gamemode Cast Failed." ) );
			}			

			// void SetFlexMatchData(int Mapindex, FString Mapname, int Maxusercount, EGWGameMode Gamemode, EGWGamePVPRule GameRule);
			// void SetCustomMatchData(int mapindex, FString mapname, int Maxusercount, EGWGameMode egamemode,FString mater, FString Title);
			*/
		};

		FProcessParameters* params = new FProcessParameters();
		params->OnStartGameSession.BindLambda(onGameSession);

		////OnProcessTerminate callback. GameLift invokes this callback before shutting down an instance hosting this game server.
		////It gives this game server a chance to save its state, communicate with services, etc., before being shut down.
		////In this case, we simply tell GameLift we are indeed going to shut down.
		params->OnTerminate.BindLambda([=]() {
			gameLiftSdkModule->ProcessEnding();
		});

		////This is the HealthCheck callback.
		////GameLift invokes this callback every 60 seconds or so.
		////Here, a game server might want to check the health of dependencies and such.
		////Simply return true if healthy, false otherwise.
		////The game server has 60 seconds to respond with its health status. GameLift defaults to 'false' if the game server doesn't respond in time.
		////In this case, we're always healthy!
		params->OnHealthCheck.BindLambda([]() {
			return true;
		});

		////This game server tells GameLift that it listens on port 7777 for incoming player connections.
		params->port = m_port;

		////Here, the game server tells GameLift what set of files to upload when the game session ends.
		////GameLift uploads everything specified here for the developers to fetch later.
		TArray<FString> logfiles;
		logfiles.Add(TEXT("aLogFile.txt"));
		params->logParameters = logfiles;

		////Calling ProcessReady tells GameLift this game server is ready to receive incoming game sessions!
		FGameLiftGenericOutcome ReadyOutcome = gameLiftSdkModule->ProcessReady(*params);

		if (!ReadyOutcome.IsSuccess())
		{
			UE_LOG(LogTemp, Error, TEXT("ProcessReady Fail : %s"), *ReadyOutcome.GetError().m_errorMessage);
		}
	}
	else
	{

		// 2020.04.09 UserCount 패킷 전달을 블루프린트로 옮겨서 제외했습니다. / 정리필요 / By.안성용
		//if (m_iLobbyType == 1)
		//{
		//	if (!this->GetTimerManager().IsTimerActive(m_counttimer))
		//		this->GetTimerManager().SetTimer(m_counttimer, this, &UGP2GameInstance::WebReq_SendUsercount, 10, true);
		//}

		InitGameData();

		//	m_iRoomNumber = atoi(gameSession.GetGameSessionData());
		//m_GameSessionID = gameSession.GetGameSessionId();
		//m_Subject = gameSession.GetName();
		if (m_iLobbyType > 1)
		{
			UGameplayStatics::OpenLevel(GetWorld(), "PVPMAP");
			UE_LOG(LogTemp, Log, TEXT("OpenLevel : PVPMAP"));
		}

		m_bSettingMap = true;
		m_bActiveGameLiftSession = true;
	}

#endif



// 내부 데디케이트 서버리스트 등록을 위해 socket.io 구현 했던 코드 임시로 남겨 둔다. sjg 18.08.09
#if 0
	if (!NativeClient.IsValid() && this->IsDedicatedServerInstance())
		NativeClient = MakeShareable(new FSocketIONative);

	if (NativeClient.IsValid() && this->IsDedicatedServerInstance())
	{

		NativeClient->Connect(FString("http://172.20.30.106:3002"), nullptr, nullptr);

		int port = 0;

		if (!FParse::Value(FCommandLine::Get(), _T("port"), port))
		{
			UE_LOG(LogTemp, Log, TEXT("Port Not Found Default Setting 7777"));
			port = 7777;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Port Found Default Setting %d"), port);
		}

		auto message = sio::int_message::create(port);

		NativeClient->EmitRaw(FString("ServerReg"), message);

		NativeClient->OnRawEvent(FString(TEXT("ServerReg")), [&](const FString& Name, const sio::message::ptr& Message)
		{
			//if you expected an object e.g. {}
			if (Message->get_flag() != sio::message::flag_object)
			{
				UE_LOG(LogTemp, Warning, TEXT("Warning! event did not receive expected Object."));
				return;
			}

			auto MessageMap = Message->get_map();

			//use the map to decode an object key e.g. type string
			auto typeMessage = MessageMap["result"];

			if (typeMessage->get_flag() == typeMessage->flag_boolean)
			{
				if (typeMessage->get_bool())
				{
					UE_LOG(LogTemp, Log, TEXT("ServerReg ok"));
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("ServerReg fail"));
				}
			}

		});
	}
#endif

	//WebReq_ServerReg();

	Super::OnStart();
}

void UGP2GameInstance::WebReq_ServerReg()
{
#if WITH_GAMELIFT
	if (!m_bLocal)
		return;

	if (m_iLobbyType > 0) return;

	FHttpModule* Http;

	Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGP2GameInstance::WebRes_ServerReg);

	int port = 0;

	if (!FParse::Value(FCommandLine::Get(), TEXT("port="), port))
	{
		UE_LOG(LogTemp, Log, TEXT("Port Not Found Default Setting 7777"));
		port = 7777;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Port Found Default Setting %d"), port);
	}

	FString GameMode;

	if (m_eGameMode == EGWGameMode::PVP )
		GameMode = "PVP";
	else
		GameMode = "PVE";

	FString PostData = FString::Printf(TEXT("port=%d&gameMode=%s"), port, *GameMode);

	Request->SetURL("http://localhost:3001/testServer/serverReg");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/x-www-form-urlencoded"));
	Request->SetContentAsString(PostData);
	Request->ProcessRequest();
#endif
}

void UGP2GameInstance::WebRes_ServerReg(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
#if WITH_GAMELIFT
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		if (JsonObject->GetIntegerField("result"))
		{
			UE_LOG(LogTemp, Log, TEXT("WebRes_ServerReg"));
			m_GameSessionID = JsonObject->GetStringField("GameSessionID");
			UE_LOG(LogTemp, Log, TEXT("GameSessionID : %s"), *m_GameSessionID);
		}
	}
#endif
}

void UGP2GameInstance::WebReq_ServerReuse()
{
#if WITH_GAMELIFT
	FHttpModule* Http;

	Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGP2GameInstance::WebRes_ServerReuse);

	FString GameSessinID = "0";

	GameSessinID = m_GameSessionID;

	FString PostData = FString::Printf(TEXT("serverID=%s"), *GameSessinID);

	Request->SetURL("http://localhost:3001/testServer/serverReuse");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/x-www-form-urlencoded"));
	Request->SetContentAsString(PostData);
	Request->ProcessRequest();
#endif
}

void UGP2GameInstance::WebRes_ServerReuse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
#if WITH_GAMELIFT
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		if (JsonObject->GetIntegerField("result"))
		{
			UE_LOG(LogTemp, Log, TEXT("WebRes_ServerReuse"));
			InitGameData();
		}
	}
#endif
}

void UGP2GameInstance::WebReq_RoomEnterUser()
{
#if WITH_GAMELIFT
	if (!m_bLocal)
		return;

	FHttpModule* Http;

	Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGP2GameInstance::WebRes_RoomEnterUser);

	FString GameSessinID = "0";

	GameSessinID = m_GameSessionID;

	FString PostData = FString::Printf(TEXT("serverID=%s"), *GameSessinID);

	Request->SetURL("http://localhost:3001/testServer/roomenter");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/x-www-form-urlencoded"));
	Request->SetContentAsString(PostData);
	Request->ProcessRequest();
#endif
}

void UGP2GameInstance::WebRes_RoomEnterUser(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
#if WITH_GAMELIFT
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		if (!JsonObject->GetIntegerField("result"))
		{
			UE_LOG(LogTemp, Log, TEXT("WebRes_RoomEnterUser Fail"));
		}
	}
#endif
}

void UGP2GameInstance::WebReq_RoomOutUser()
{
#if WITH_GAMELIFT
	if (!m_bLocal)
		return;

	FHttpModule* Http;

	Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGP2GameInstance::WebRes_RoomOutUser);

	FString GameSessinID = "0";

	GameSessinID = m_GameSessionID;

	FString PostData = FString::Printf(TEXT("serverID=%s"), *GameSessinID);

	Request->SetURL("http://localhost:3001/testServer/roomout");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/x-www-form-urlencoded"));
	Request->SetContentAsString(PostData);
	Request->ProcessRequest();
#endif
}

void UGP2GameInstance::WebRes_RoomOutUser(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
#if WITH_GAMELIFT
	TSharedPtr<FJsonObject> JsonObject;

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		if (!JsonObject->GetIntegerField("result"))
		{
			UE_LOG(LogTemp, Log, TEXT("WebRes_RoomOutUser Fail"));
		}
	}
#endif
}

void UGP2GameInstance::WebReq_GameStart()
{
#if WITH_GAMELIFT
	if (!m_bLocal)
		return;

	FHttpModule* Http;

	Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGP2GameInstance::WebRes_GameStart);

	FString GameSessinID = "0";

	GameSessinID = m_GameSessionID;

	FString PostData = FString::Printf(TEXT("serverID=%s"), *GameSessinID);

	Request->SetURL("http://localhost:3001/testServer/gamestart");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/x-www-form-urlencoded"));
	Request->SetContentAsString(PostData);
	Request->ProcessRequest();
#endif
}

void UGP2GameInstance::WebRes_GameStart(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
#if WITH_GAMELIFT
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		if (!JsonObject->GetIntegerField("result"))
		{
			UE_LOG(LogTemp, Log, TEXT("WebRes_GameStart Fail"));
		}
	}
#endif
}

void UGP2GameInstance::WebReq_GameEnd()
{
#if WITH_GAMELIFT
	FHttpModule* Http;

	Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGP2GameInstance::WebRes_GameEnd);

	int port = 0;

	if (!FParse::Value(FCommandLine::Get(), TEXT("port="), port))
	{
		UE_LOG(LogTemp, Log, TEXT("Port Not Found Default Setting 7777"));
		port = 7777;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Port Found Default Setting %d"), port);
	}

	FString PostData = FString::Printf(TEXT("port=%d"), port);

	Request->SetURL("http://localhost:3001/testServer/serverReg");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/x-www-form-urlencoded"));
	Request->SetContentAsString(PostData);
	Request->ProcessRequest();
#endif
}

void UGP2GameInstance::WebRes_GameEnd(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

}

void UGP2GameInstance::WebReq_SendUsercount()
{

#if WITH_GAMELIFT
	UE_LOG(LogTemp, Log, TEXT("begin WebReq_SendUsercount"));
	// UE_LOG(LogTemp, Error, TEXT("WebReq_SendUsercount lobbytype : %d, usercount : %d"), m_iLobbyType, m_byEnterUserCount);

	if (m_iLobbyType != 1) return;		// 로비서버만 실행한다.

	UWorld* world = GetWorld();
	
	if (!world) return;

	FHttpModule* Http;

	Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGP2GameInstance::WebRes_SendUsercount);

	int32 usercount = world->GetNumPlayerControllers();

	FString PostData = FString::Printf(TEXT("address=%s&usercount=%d"), *m_myDNS, usercount);

	FString address = FString::Printf(TEXT("%s/server/usercount"), *m_WebServerIP);
	Request->SetURL(address);
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/x-www-form-urlencoded"));
	Request->SetContentAsString(PostData);
	Request->ProcessRequest();

	UE_LOG(LogTemp, Log, TEXT("end WebReq_SendUsercount"));
#endif
}

void UGP2GameInstance::WebRes_SendUsercount(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

#if WITH_GAMELIFT
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		if (JsonObject->GetIntegerField("flag") == 1) {
			// 유저들 내보내야함.
			FGenericPlatformMisc::RequestExit(false);
			UE_LOG(LogTemp, Log, TEXT("Success to Kick Every Player"));
		}

		if (!JsonObject->GetIntegerField("result"))
		{
			UE_LOG(LogTemp, Log, TEXT("WebRes_SendUsercount Fail"));
		}
	}
#endif
}

bool UGP2GameInstance::IsLobbyServer()
{
	if (m_iLobbyType == 1) { return true; }

	return false;
}

bool UGP2GameInstance::IsWithEditor()
{
#if WITH_EDITOR
	return true;
#else
	return false;
#endif
}

EWebResultEnum UGP2GameInstance::ToWebResultEnum(UObject* WorldContextObject, float fValue)
{
	int iTemp = static_cast<int>(fValue);

	return static_cast<EWebResultEnum>(iTemp);
}


void UGP2GameInstance::LoginSessionCheck(const int &PlayerID, const FString &PlayerSessionID, const int &UserSN, bool &CheckResult, int &errorType)
{
#if WITH_GAMELIFT
	CheckResult = true;


	if ( ( m_eGameMode == EGWGameMode::PVE ) && m_byEnterUserCount >= 4)
	{
		UE_LOG(LogTemp, Log, TEXT("PVE User Full"));
		CheckResult = false;
	}
	else if ( ( m_eGameMode == EGWGameMode::PVP ) && m_byEnterUserCount >= 8)
	{
		UE_LOG(LogTemp, Log, TEXT("PVP User Full"));
		CheckResult = false;
	}

	if (m_bGameStart)
	{
		UE_LOG(LogTemp, Log, TEXT("Already GameStart"));
		CheckResult = false;
	}

	if (m_bLocal)
	{
	//	CheckResult = true;
	//	m_ConnectUserList.Emplace(PlayerID, FConnectInfo(UserSN, PlayerSessionID));
		WebReq_RoomEnterUser();
	//	return;
	}

	FGameLiftGenericOutcome result = gameLiftSdkModule->AcceptPlayerSession(PlayerSessionID);

	UE_LOG(LogTemp, Error, TEXT("LoginSessionCheck m_byEnterUserCount : %d"), m_byEnterUserCount);

	m_bCheckEmptyGameSession = false;

	m_byEnterUserCount++;

	if ( result.IsSuccess() )
	{
		m_ConnectUserList.Emplace(PlayerID, FConnectInfo(UserSN, PlayerSessionID));
	}
	else
	{
		CheckResult = false;

		gameLiftSdkModule->RemovePlayerSession(PlayerSessionID);
		UE_LOG(LogTemp, Error, TEXT("### AcceptPlayerSession Fail : %s , UserSN : %d"), result.GetError().m_errorMessage.GetCharArray().GetData(), UserSN);
	}
#endif
}


void UGP2GameInstance::LogoutProcess(const int &PlayerID)
{
#if WITH_GAMELIFT

	//if (m_ConnectUserList.Contains(PlayerID))

	if(m_byEnterUserCount > 0)
		m_byEnterUserCount--;
	
	UE_LOG(LogTemp, Log, TEXT("getGameInstance LogoutProcess m_byEnterUserCount : %d"), m_byEnterUserCount);

	//if (m_byEnterUserCount <= 0)
	//{
	//	if (GetWorld())
	//	{
	//		if (m_eGameMode == EGWGameMode::PVE)
	//		{
	//			UE_LOG(LogTemp, Log, TEXT("getGameInstance->getGameMode() == EGWGameMode::PVE"));
	//			GetWorld()->ServerTravel("/Game/Maps/Room_PVE_Lobby");
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Log, TEXT("getGameInstance->getGameMode() == EGWGameMode::PVP"));
	//			GetWorld()->ServerTravel("/Game/Maps/Room_PVP_Lobby");


	//		}
	//	}
	//}

	if (m_bLocal)
	{
		//if (m_byEnterUserCount <= 0)
		//{
		//	m_bGameStart = false;
		//	m_ConnectUserList.Empty();
		//}
		//else
		//{
		//	if (m_ConnectUserList.Contains(PlayerID))
		//	{
		//		m_ConnectUserList.Remove(PlayerID);
		//	}
		//}

		//if (m_byEnterUserCount <= 0)
		//	WebReq_ServerReuse();
		//else
		if(m_ConnectUserList.Contains(PlayerID))
			WebReq_RoomOutUser();

		//return;
	}

	if (m_iLobbyType == 0)
	{
		if (gameLiftSdkModule.IsValid() && m_ConnectUserList.Contains(PlayerID) && m_ConnectUserList[PlayerID].PlayerSessionID.Len() > 0)
		{
			FGameLiftGenericOutcome OutCom = gameLiftSdkModule->RemovePlayerSession(m_ConnectUserList[PlayerID].PlayerSessionID);

			if (!OutCom.IsSuccess())
			{
				UE_LOG(LogTemp, Error, TEXT("### RemovePlayerSession Fail UserSN : %d SessionID %s"), m_ConnectUserList[PlayerID].UserSN, *(m_ConnectUserList[PlayerID].PlayerSessionID));
			}
		}
	}

	if (m_byEnterUserCount <= 0)
	{
		m_bGameStart = false;
		m_ConnectUserList.Empty();
	}
	else
	{
		if (m_ConnectUserList.Contains(PlayerID))
		{
			m_ConnectUserList.Remove(PlayerID);
		}
	}

	if(m_iLobbyType == 0)
	{
		if (m_byEnterUserCount <= 0 && m_bActiveGameLiftSession)
		{
			if ( m_eGameMode == EGWGameMode::PVP )
				UGameplayStatics::OpenLevel(GetWorld(), "G2_E_MatchingRoom_PVP");
			else
				UGameplayStatics::OpenLevel(GetWorld(), "G2_E_MatchingRoom_PVE");

			FGameLiftGenericOutcome OutCom = gameLiftSdkModule->TerminateGameSession();

			m_bActiveGameLiftSession = false;

			if (OutCom.IsSuccess())
			{
				UE_LOG(LogTemp, Error, TEXT("### TerminateGameSession success"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("### TerminateGameSession fail %s"), *OutCom.GetError().m_errorMessage);
			}
		}
	}
#endif
}

void UGP2GameInstance::GameLiftStartProcess()
{
	if (m_bGameStart)
	{
		return;
	}

	m_bGameStart = true;

#if WITH_GAMELIFT

	if (m_bLocal)
	{
		WebReq_GameStart();
	//	return;
	}

	if(m_iLobbyType == 0)
	{
		if (gameLiftSdkModule.IsValid())
		{
			FGameLiftGenericOutcome outcome = gameLiftSdkModule->UpdatePlayerSessionCreationPolicy(EPlayerSessionCreationPolicy::DENY_ALL);

			if (!outcome.IsSuccess())
			{
				UE_LOG(LogTemp, Error, TEXT("### UpdatePlayerSessionCreationPolicy Fail %s"), *outcome.GetError().m_errorMessage);
			}
		}
	}
#endif
}

EGWGameMode UGP2GameInstance::getGameMode()
{
	return m_eGameMode;
}

bool UGP2GameInstance::getGameStart()
{
	return m_bGameStart;
}

#if WITH_GAMELIFT
void UGP2GameInstance::EmptyGameSessionCheckTick()
{
//	if (m_bLocal)
//		return;

	if (!m_bCheckEmptyGameSession)
		return;

	if (m_bActiveGameLiftSession)
	{
		if (!m_bSettingMap)
		{
//			if (m_Map == NULL)
			{
				if (m_eGameMode == EGWGameMode::PVP )
					UGameplayStatics::OpenLevel(GetWorld(), "G2_E_MatchingRoom_PVP");
				else if (m_eGameMode == EGWGameMode::TUTORIAL)
					UGameplayStatics::OpenLevel(GetWorld(), "G2_Tutorial");
				else
					UGameplayStatics::OpenLevel(GetWorld(), "G2_E_MatchingRoom_PVE");
			}
//			else
//				UGameplayStatics::OpenLevel(GetWorld(), m_Map);

			m_bSettingMap = true;

			UE_LOG(LogTemp, Error, TEXT("### EmptyGameSessionCheckTick ActivateGameSession"));

			gameLiftSdkModule->ActivateGameSession();
		}
	}

	if ( m_byEnterUserCount <= 0 )
	{
		m_EmptyGameSessionCheckCount++;

		if ( m_EmptyGameSessionCheckCount >= 15 )
		{
			if (m_iLobbyType == 0)
			{
				FGameLiftGenericOutcome OutCom = gameLiftSdkModule->TerminateGameSession();

				if (OutCom.IsSuccess())
				{
					UE_LOG(LogTemp, Error, TEXT("### TerminateGameSession success"));
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("### TerminateGameSession fail %s"), *OutCom.GetError().m_errorMessage);
				}
			}

			m_EmptyGameSessionCheckCount = 0;
			m_bCheckEmptyGameSession = false;
			m_bActiveGameLiftSession = false;
		}
	}
	else
	{
		m_EmptyGameSessionCheckCount = 0;
	}
}
#endif

int8 UGP2GameInstance::getEnterUserCount()
{
	return m_byEnterUserCount;
}

int32 UGP2GameInstance::getRoomNumber()
{
	return m_iRoomNumber;
}

const FString &  UGP2GameInstance::getRoomSubject()
{
	return m_Subject;
}

const FString & UGP2GameInstance::getGameSession()
{
	return m_GameSessionID;
}

const FString & UGP2GameInstance::getServerSystemInfo()
{
	m_ServerSystemInfo = FString::Printf( TEXT( "CPU Usage : %0.1f%% Memory Usage : %skb  VRAM Usage :%skb" ) , FPlatformTime::GetCPUTime().CPUTimePct , *FString::FormatAsNumber( FPlatformMemory::GetStats().UsedPhysical / 1024 ), *FString::FormatAsNumber(FPlatformMemory::GetStats().UsedVirtual / 1024));

	return m_ServerSystemInfo;
}

bool UGP2GameInstance::getLocal()
{
	return m_bLocal;
}

bool UGP2GameInstance::getGameLiftActive()
{
	if(m_iLobbyType > 0) return true;

#if WITH_GAMELIFT
	return m_bActiveGameLiftSession;
#else
	return false;
#endif
}

const FString & UGP2GameInstance::getWebURL()
{

	return m_WebServerIP;
}

const FString & UGP2GameInstance::getMyDNS()
{

	return m_myDNS;
}

int32 UGP2GameInstance::getCurrnetTickCount()
{
	return FPlatformTime::Seconds();
}


//void UGP2GameInstance::AsyncCharacterLoad(int CharacterIndex, FCharacterLoadCompleted CompletedFunc)
//{
//	
//}

const bool UGP2GameInstance::GetAutoLogin()
{
	return g_AutoLogin;
}

const FString& UGP2GameInstance::GetAutoLoginId()
{
	return g_AutoLoginId;
}

const bool UGP2GameInstance::GetLocalMode()
{
	return g_LocalMode;
}

const bool UGP2GameInstance::GetUsingCharacterArray()
{
	return g_bUsingCharacterArray;
}

const int UGP2GameInstance::GetDefaultCharacter()
{
	return g_DefaultCharacter;
}

const TArray<FString> UGP2GameInstance::GetDefaultCharacters()
{
	return g_DefaultCharacters;
}

const bool UGP2GameInstance::GetSkipAdvent()
{
	return g_SkipAdvent;
}

const bool UGP2GameInstance::GetShowDebugArrow()
{
	return g_ShowDebug;
}

const bool UGP2GameInstance::GetJsonSecurity( int InIndex )
{
	switch ( InIndex )
	{
	case 0:  return g_JsonSecurity;
	case 1:  return g_JsonSecurityJpn;
	case 2:  return g_JsonSecurityUsa;
	case 3:  return g_JsonSecurityEu;
	case 4:  return g_JsonSecurityNo4;
	case 5:  return g_JsonSecurityNo5;
	}

	return g_JsonSecurity;
}

FString UGP2GameInstance::GetServerAddress( int InIndex )
{
	FString FullUrl = TEXT( "" );

	if (g_direct_server_url.Len() > 0)
		return g_direct_server_url;

	/// FULL URL 형식으로 변경 - 포트 제거.
	switch (InIndex)
	{
	case 0:  FullUrl = g_LocalServerAddr; break;
	case 1:  FullUrl = g_JapanServerAddr; break;
	case 2:  FullUrl = g_UsaServerAddr;   break;
	case 3:  FullUrl = g_EUServerAddr;   break;
	case 4:  FullUrl = g_No4ServerAddr;   break;
	case 5:  FullUrl = g_No5ServerAddr;   break;
	default: FullUrl = g_LocalServerAddr; break;
	}

	return FullUrl;
}

#if !WITH_GAMELIFT 
DEFINE_LOG_CATEGORY_STATIC(LogVivoxGameInstance, Log, All);

#define VIVOX_VOICE_SERVER TEXT("https://vdx5.www.vivox.com/api2")
#define VIVOX_VOICE_DOMAIN TEXT("vdx5.vivox.com")
#define VIVOX_VOICE_ISSUER TEXT("gunspc2-gu07-w-dev")


bool UGP2GameInstance::Exec(UWorld * Inworld, const TCHAR * Cmd, FOutputDevice & Ar)
{
	if (FParse::Command(&Cmd, TEXT("VIVOXSTATE")))
	{
		UE_LOG(LogVivoxGameInstance, Log, TEXT("Initialized: %s"), IsInitialized() ? TEXT("YES") : TEXT("NO"));
		UE_LOG(LogVivoxGameInstance, Log, TEXT("Logged in: %s"), IsLoggedIn() ? TEXT("YES") : TEXT("NO"));
		UE_LOG(LogVivoxGameInstance, Log, TEXT("Logging in: %s"), bLoggingIn ? TEXT("YES") : TEXT("NO"));

		if (VivoxVoiceClient->GetLoginSession(LoggedInAccountID).ChannelSessions().Num() > 0)
		{
			UE_LOG(LogVivoxGameInstance, Log, TEXT("Current Channel List:"));
			UE_LOG(LogVivoxGameInstance, Log, TEXT("===================="));
			for (auto &Session : VivoxVoiceClient->GetLoginSession(LoggedInAccountID).ChannelSessions())
			{
				UE_LOG(LogVivoxGameInstance, Log, TEXT("Name: %s, Type: %s, IsTransmitting: %s, AudioState: %s, TextState: %s"),
					*Session.Value->Channel().Name(),
					*UEnumShortToString(ChannelType, Session.Value->Channel().Type()),
					Session.Value->IsTransmitting() ? TEXT("Yes") : TEXT("No"),
					*UEnumShortToString(ConnectionState, Session.Value->AudioState()),
					*UEnumShortToString(ConnectionState, Session.Value->TextState()));
			}
			UE_LOG(LogVivoxGameInstance, Log, TEXT("===================="));
		}
		else
		{
			UE_LOG(LogVivoxGameInstance, Log, TEXT("Current Channel List: Empty"));
		}

		return true;
	}
	else if (FParse::Command(&Cmd, TEXT("VIVOXAUDIO")))
	{
		UE_LOG(LogVivoxGameInstance, Log, TEXT("Initialized: %s"), IsInitialized() ? TEXT("YES") : TEXT("NO"));
		if (IsInitialized())
		{
			IAudioDevices &audiodevices = VivoxVoiceClient->AudioInputDevices();
			for (auto &device : audiodevices.AvailableDevices())
			{
				UE_LOG(LogVivoxGameInstance, Log, TEXT("Vivox input device Key = %s, Value = %s, ID = %s"), *device.Key, *device.Value->Name(), *device.Value->Id());
			}

				UE_LOG(LogVivoxGameInstance, Log, TEXT("Vivox input Activedevice  Value = %s, ID = %s, Systemdevice name = %s, ID = %s"), *audiodevices.ActiveDevice().Name(), *audiodevices.ActiveDevice().Id(), *audiodevices.SystemDevice().Name(), *audiodevices.SystemDevice().Id());
			audiodevices = VivoxVoiceClient->AudioOutputDevices();
			for (auto &device : audiodevices.AvailableDevices())
			{
				UE_LOG(LogVivoxGameInstance, Log, TEXT("Vivox output device Key = %s, Value = %s, ID = %s"), *device.Key, *device.Value->Name(), *device.Value->Id());
			}
			UE_LOG(LogVivoxGameInstance, Log, TEXT("Vivox Outpue Activedevice  Value = %s, ID = %s, Systemdevice name = %s, ID = %s"), *audiodevices.ActiveDevice().Name(), *audiodevices.ActiveDevice().Id(), *audiodevices.SystemDevice().Name(), *audiodevices.SystemDevice().Id());
		}
		else return false;

		return true;
	}

	return false;
}

bool UGP2GameInstance::IsInitialized()
{
	return bInitialized;
}

bool UGP2GameInstance::IsLoggedIn()
{
	return bLoggedIn;
}

/*
int32 UGP2GameInstance::JoinVoiceChannels(FString GameMode, FString OnlineSessionId, int32 TeamNum)
{

	FString channelName = *OnlineSessionId;
#if PLATFORM_XBOXONE
	OnlineSessionId.Split(TEXT("/"), NULL, &channelName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	UE_LOG(LogVivoxGameInstance, Log, TEXT("Split OnlineSessionId: %s"), *channelName);
	channelName = channelName.ToUpper();
#endif

	if (GameMode.Equals(TEXT("FFA"))) // Free For All
	{
		UE_LOG(LogVivoxGameInstance, Log, TEXT("FreeForAll GameType detected"));
		Vivox_Join(ChannelType::Positional, true, FString::Printf(TEXT("FP%s"), *channelName));

		return VxErrorSuccess;
	}
	else if (GameMode.Equals(TEXT("TDM"))) // Team Deathmatch
	{
		UE_LOG(LogVivoxGameInstance, Log, TEXT("TeamDeathmatch GameType detected"));
		Vivox_Join(ChannelType::Positional, false, FString::Printf(TEXT("TP%s"), *channelName), PTTKey::PTTAreaChannel);

		bool bTeamChatOnAtStart = false;
#if (PLATFORM_PS4 || PLATFORM_XBOXONE || PLATFORM_SWITCH)
		bTeamChatOnAtStart = true; // on console, team chat should be toggled on at start
#endif
		Vivox_Join(ChannelType::NonPositional, bTeamChatOnAtStart, FString::Printf(TEXT("TN%d_%s"), TeamNum, *channelName), PTTKey::PTTTeamChannel);

		return VxErrorSuccess;
	}
	else
	{
		UE_LOG(LogVivoxGameInstance, Warning, TEXT("Joining no voice channels: Invalid GameType detected(%s)"), *GameMode);
		return VxErrorInvalidState;
	}
}*/


void UGP2GameInstance::OnLoginSessionStateChanged(LoginState State)
{
	switch (State)
	{
	case LoginState::LoggedOut:
		UE_LOG(LogVivoxGameInstance, Error, TEXT("Unexpectedly Logged Out by Network"));
		LoggedInAccountID = AccountId();
		LoggedInPlayerName = FString();
		bLoggingIn = false;
		bLoggedIn = false;
		break;
	default:
		UE_LOG(LogVivoxGameInstance, Log, TEXT("LoginSession State Change: %s"), *UEnumShortToString(LoginState, State));
		if (State == LoginState::LoggedIn)
		{
			VivoxLogined();
		}
		break;
	}
}

void UGP2GameInstance::OnChannelParticipantAdded(const IParticipant & Participant)
{
	ChannelId Channel = Participant.ParentChannelSession().Channel();
	UE_LOG(LogVivoxGameInstance, Log, TEXT("User %s has joined channel %s (self = %s)"), *Participant.Account().Name(), *Channel.Name(), Participant.IsSelf() ? TEXT("true") : TEXT("false"));
	VivoxChannelAdded(*Participant.Account().Name(), Participant.IsSelf());
}

void UGP2GameInstance::OnChannelParticipantRemoved(const IParticipant & Participant)
{
	ChannelId Channel = Participant.ParentChannelSession().Channel();
	UE_LOG(LogVivoxGameInstance, Log, TEXT("User %s has left channel %s (self = %s)"), *Participant.Account().Name(), *Channel.Name(), Participant.IsSelf() ? TEXT("true") : TEXT("false"));
	VivoxChannelRemoved(*Participant.Account().Name(), Participant.IsSelf());
}

void UGP2GameInstance::OnChannelParticipantUpdated(const IParticipant & Participant)
{
	if (Participant.IsSelf()) {
		UE_LOG(LogVivoxGameInstance, Log, TEXT("Self Participant Updated (audio=%d, text=%d, speaking=%d)"), Participant.InAudio(), Participant.InText(), Participant.SpeechDetected());
		
	}
	VivoxPushtoTalkState(*Participant.Account().Name(), Participant.SpeechDetected(), Participant.IsSelf());

}

void UGP2GameInstance::OnChannelAudioStateChanged(const IChannelConnectionState & State)
{
	UE_LOG(LogVivoxGameInstance, Log, TEXT("ChannelSession Audio State Change in %s: %s"), *State.ChannelSession().Channel().Name(), *UEnumShortToString(ConnectionState, State.State()));
	if (State.State() == ConnectionState::Connected)
	{
		VivoxchannelConneced();
	}
}

void UGP2GameInstance::OnChannelTextStateChanged(const IChannelConnectionState & State)
{
	UE_LOG(LogVivoxGameInstance, Log, TEXT("ChannelSession Text State Change in %s: %s"), *State.ChannelSession().Channel().Name(), *UEnumShortToString(ConnectionState, State.State()));
}

void UGP2GameInstance::OnChannelTextMessageReceived(const IChannelTextMessage & Message)
{
	UE_LOG(LogVivoxGameInstance, Log, TEXT("Message Received from %s: %s"), *Message.Sender().Name(), *Message.Message());
}

ILoginSession * UGP2GameInstance::GetVivoxLoginSessionForRoster()
{
	if (!LoggedInAccountID.IsEmpty())
	{
		return &VivoxVoiceClient->GetLoginSession(LoggedInAccountID);
	}
	return NULL;
}

TSharedPtr<IChannelSession> UGP2GameInstance::GetVivoxChannelSessionForRoster()
{
	for (auto& Session : VivoxVoiceClient->GetLoginSession(LoggedInAccountID).ChannelSessions())
	{
		if (Session.Value->Channel().Name().StartsWith("TN", ESearchCase::CaseSensitive))
		{
			return Session.Value;
		}
	}
	return NULL;
}

void UGP2GameInstance::BindLoginSessionHandlers(bool DoBind, ILoginSession & LoginSession)
{
	if (DoBind)
	{
		LoginSession.EventStateChanged.AddUObject(this, &UGP2GameInstance::OnLoginSessionStateChanged);
	}
	else
	{
		LoginSession.EventStateChanged.RemoveAll(this);
	}
}

void UGP2GameInstance::BindChannelSessionHandlers(bool DoBind, IChannelSession & ChannelSession)
{
	if (DoBind)
	{
		ChannelSession.EventAfterParticipantAdded.AddUObject(this, &UGP2GameInstance::OnChannelParticipantAdded);
		ChannelSession.EventBeforeParticipantRemoved.AddUObject(this, &UGP2GameInstance::OnChannelParticipantRemoved);
		ChannelSession.EventAfterParticipantUpdated.AddUObject(this, &UGP2GameInstance::OnChannelParticipantUpdated);
		ChannelSession.EventAudioStateChanged.AddUObject(this, &UGP2GameInstance::OnChannelAudioStateChanged);
		ChannelSession.EventTextStateChanged.AddUObject(this, &UGP2GameInstance::OnChannelTextStateChanged);
		ChannelSession.EventTextMessageReceived.AddUObject(this, &UGP2GameInstance::OnChannelTextMessageReceived);
	}
	else
	{
		ChannelSession.EventAfterParticipantAdded.RemoveAll(this);
		ChannelSession.EventBeforeParticipantRemoved.RemoveAll(this);
		ChannelSession.EventAfterParticipantUpdated.RemoveAll(this);
		ChannelSession.EventAudioStateChanged.RemoveAll(this);
		ChannelSession.EventTextStateChanged.RemoveAll(this);
		ChannelSession.EventTextMessageReceived.RemoveAll(this);
	}
}
#endif


int32 UGP2GameInstance::Vivox_Initialize(int logLevel)
{
#if !WITH_GAMELIFT

	GP2LOG("Vivox_Init-------------------->");
	bInitialized = false;
	bInitializing = false;
	bLoggedIn = false;
	bLoggingIn = false;
	VivoxVoiceClient = &static_cast<FVivoxCoreModule *>(&FModuleManager::Get().LoadModuleChecked(TEXT("VivoxCore")))->VoiceClient();

//	if (bInitialized || bInitializing)
//	{
//		return VxErrorSuccess;
//	}

	VivoxConfig Config;
	Config.SetLogLevel((vx_log_level)logLevel);
	VivoxCoreError Status = VivoxVoiceClient->Initialize(Config);
	if (Status != VxErrorSuccess)
	{
		UE_LOG(LogVivoxGameInstance, Error, TEXT("Initialize failed: %s (%d)"), ANSI_TO_TCHAR(FVivoxCoreModule::ErrorToString(Status)), Status);
	}
	else
	{
		bInitialized = true;
	}

	return Status;
#endif
	return -1;
}

void UGP2GameInstance::Vivox_Uninitialize()
{
#if !WITH_GAMELIFT
	if (!bInitialized && !bInitializing)
	{
		return;
	}

	VivoxVoiceClient->Uninitialize();
#endif
}


int32 UGP2GameInstance::Vivox_Login(const FString & PlayerName)
{
#if !WITH_GAMELIFT
	if (bLoggedIn)
	{
		UE_LOG(LogVivoxGameInstance, Verbose, TEXT("Already logged in"));
		return VxErrorSuccess;
	}

	if (bLoggingIn)
	{
		UE_LOG(LogVivoxGameInstance, Verbose, TEXT("Already logging in"));
		return VxErrorSuccess;
	}

	if (!bInitialized)
	{
		UE_LOG(LogVivoxGameInstance, Verbose, TEXT("Not initialized"));
		return VxErrorNotInitialized;
	}

	LoggedInPlayerName = PlayerName;
	LoggedInAccountID = AccountId(VIVOX_VOICE_ISSUER, LoggedInPlayerName, VIVOX_VOICE_DOMAIN);
	ILoginSession &LoginSession = VivoxVoiceClient->GetLoginSession(LoggedInAccountID);

	// IMPORTANT: in production, developers should NOT use the insecure client-side token generation methods.
	// To generate secure access tokens, call GenerateClientLoginToken or a custom implementation from your game server.
	// This is important not only to secure access to chat features, but tokens issued by the client could
	// appear expired if the client's clock is set incorrectly, resulting in rejection.
	FString LoginToken;
	FVivoxToken::GenerateClientLoginToken(LoginSession, LoginToken);

	UE_LOG(LogVivoxGameInstance, Verbose, TEXT("Logging in %s with token %s"), *LoggedInPlayerName, *LoginToken);

	ILoginSession::FOnBeginLoginCompletedDelegate OnBeginLoginCompleteCallback;
	OnBeginLoginCompleteCallback.BindLambda([this, &LoginSession](VivoxCoreError Status)
	{
		bLoggingIn = false;
		if (VxErrorSuccess != Status)
		{
			UE_LOG(LogVivoxGameInstance, Error, TEXT("Login failure for %s: %s (%d)"), *LoggedInPlayerName, ANSI_TO_TCHAR(FVivoxCoreModule::ErrorToString(Status)), Status);
			BindLoginSessionHandlers(false, LoginSession); // Unbind handlers if we fail to log in
			LoggedInAccountID = AccountId();
			LoggedInPlayerName = FString();
			bLoggedIn = false; // should already be false, but we'll just make sure
		}
		else
		{
			UE_LOG(LogVivoxGameInstance, Log, TEXT("Login success for %s"), *LoggedInPlayerName);
			bLoggedIn = true;
		}
	});
	BindLoginSessionHandlers(true, LoginSession);
	bLoggingIn = true;

	return LoginSession.BeginLogin(VIVOX_VOICE_SERVER, LoginToken, OnBeginLoginCompleteCallback);
#endif
	return -1;
}


void UGP2GameInstance::Vivox_Logout()
{
#if !WITH_GAMELIFT
	if (!bLoggedIn && !bLoggingIn)
	{
		UE_LOG(LogVivoxGameInstance, Verbose, TEXT("Not logged in, skipping logout"));
		return;
	}

	ILoginSession &LoginSession = VivoxVoiceClient->GetLoginSession(LoggedInAccountID);

	LoginSession.Logout();

	LoggedInAccountID = AccountId();
	LoggedInPlayerName = FString();
	bLoggingIn = false;
	bLoggedIn = false;
#endif
}


int32 UGP2GameInstance::Vivox_Join(int iChannelType, bool ShouldTransmitOnJoin, const FString & ChannelName, PTTKey AssignChanneltoPTTKey)
{
#if !WITH_GAMELIFT
	if (!bLoggedIn)
	{
		UE_LOG(LogVivoxGameInstance, Warning, TEXT("Not logged in; cannot join a channel"));
		return VxErrorNotLoggedIn;
	}
	ensure(!LoggedInPlayerName.IsEmpty());
	ensure(!ChannelName.IsEmpty());

	ChannelType cChannelType = (ChannelType)iChannelType;

	ILoginSession &LoginSession = VivoxVoiceClient->GetLoginSession(LoggedInAccountID);
	// It's perfectly safe to add 3D properties to any channel type (they don't have any effect if the channel type is not Positional)
	ChannelId Channel = ChannelId(VIVOX_VOICE_ISSUER, ChannelName, VIVOX_VOICE_DOMAIN, cChannelType, Channel3DProperties(8100, 270, 1.0, EAudioFadeModel::InverseByDistance));
	IChannelSession &ChannelSession = LoginSession.GetChannelSession(Channel);

	// IMPORTANT: in production, developers should NOT use the insecure client-side token generation methods.
	// To generate secure access tokens, call GenerateClientJoinToken or a custom implementation from your game server.
	// This is important not only to secure access to Chat features, but tokens issued by the client could
	// appear expired if the client's clock is set incorrectly, resulting in rejection.
	FString JoinToken;
	FVivoxToken::GenerateClientJoinToken(ChannelSession, JoinToken);

	UE_LOG(LogVivoxGameInstance, Verbose, TEXT("Joining %s to %s with token %s"), *LoggedInPlayerName, *ChannelName, *JoinToken);

	IChannelSession::FOnBeginConnectCompletedDelegate OnBeginConnectCompleteCallback;
	OnBeginConnectCompleteCallback.BindLambda([this, ShouldTransmitOnJoin, AssignChanneltoPTTKey, &LoginSession, &ChannelSession](VivoxCoreError Status)
	{
		if (VxErrorSuccess != Status)
		{
			UE_LOG(LogVivoxGameInstance, Error, TEXT("Join failure for %s: %s (%d)"), *ChannelSession.Channel().Name(), ANSI_TO_TCHAR(FVivoxCoreModule::ErrorToString(Status)), Status);
			BindChannelSessionHandlers(false, ChannelSession); // Unbind handlers if we fail to join.
			LoginSession.DeleteChannelSession(ChannelSession.Channel()); // Disassociate this ChannelSession from the LoginSession.
		}
		else
		{
			UE_LOG(LogVivoxGameInstance, Log, TEXT("Join success for %s"), *ChannelSession.Channel().Name());
			if (ChannelType::Positional == ChannelSession.Channel().Type())
			{
				ConnectedPositionalChannel = ChannelSession.Channel();
			}

			if (PTTKey::PTTAreaChannel == AssignChanneltoPTTKey)
			{
				PTTAreaChannel = TPairInitializer<ChannelId, bool>(ChannelSession.Channel(), false);
			}
			else if (PTTKey::PTTTeamChannel == AssignChanneltoPTTKey)
			{
				PTTTeamChannel = TPairInitializer<ChannelId, bool>(ChannelSession.Channel(), false);
			}

			// NB: It is usually not necessary to adjust transmission when joining channels.
			// The conditional below controls desired behavior specific to this application.
			if (ShouldTransmitOnJoin)
			{
				if (AssignChanneltoPTTKey != PTTKey::PTTNoChannel)
					MultiChanToggleChat(AssignChanneltoPTTKey);
				else
					LoginSession.SetTransmissionMode(TransmissionMode::All);
			}
			else if (LoginSession.ChannelSessions().Num() == 1)
			{
				LoginSession.SetTransmissionMode(TransmissionMode::None);
			}
		}
	});
	BindChannelSessionHandlers(true, ChannelSession);

	return ChannelSession.BeginConnect(true, false, ShouldTransmitOnJoin, JoinToken, OnBeginConnectCompleteCallback);

#endif
	return -1;
}


void UGP2GameInstance::LeaveVoiceChannels()
{
#if !WITH_GAMELIFT
	if (!bLoggedIn)
	{
		UE_LOG(LogVivoxGameInstance, Verbose, TEXT("Not logged in; cannot leave channel(s)"));
		return;
	}

	TArray<ChannelId> ChannelSessionKeys;
	VivoxVoiceClient->GetLoginSession(LoggedInAccountID).ChannelSessions().GenerateKeyArray(ChannelSessionKeys);
	for (ChannelId SessionKey : ChannelSessionKeys)
	{
		UE_LOG(LogVivoxGameInstance, Log, TEXT("Disconnecting from channel %s"), *SessionKey.Name());
		BindChannelSessionHandlers(false, VivoxVoiceClient->GetLoginSession(LoggedInAccountID).GetChannelSession(SessionKey));
		VivoxVoiceClient->GetLoginSession(LoggedInAccountID).DeleteChannelSession(SessionKey);
	}

	// Always clear stashed Positional channel and PTT channels
	ConnectedPositionalChannel = ChannelId();
	PTTAreaChannel.Key = ChannelId();
	PTTTeamChannel.Key = ChannelId();
#endif
}


int32 UGP2GameInstance::MultiChanPushToTalk(PTTKey Key, bool PTTKeyPressed)
{
#if !WITH_GAMELIFT
	FString Channel;
	if (PTTKey::PTTAreaChannel == Key && !PTTAreaChannel.Key.IsEmpty())
	{
		UE_LOG(LogVivoxGameInstance, Log, TEXT("MultiChanPushToTalk: %s talking in %s"), PTTKeyPressed ? TEXT("Started") : TEXT("Stopped"), *PTTAreaChannel.Key.Name());
		PTTAreaChannel.Value = PTTKeyPressed;
	}
	else if (PTTKey::PTTTeamChannel == Key && !PTTTeamChannel.Key.IsEmpty())
	{
		UE_LOG(LogVivoxGameInstance, Log, TEXT("MultiChanPushToTalk: %s talking in %s"), PTTKeyPressed ? TEXT("Started") : TEXT("Stopped"), *PTTTeamChannel.Key.Name());
		PTTTeamChannel.Value = PTTKeyPressed;
	}
	else
	{
		UE_LOG(LogVivoxGameInstance, Warning, TEXT("MultiChanPushToTalk: No ChannelId assigned to %s"), *UEnumFullToString(PTTKey, Key));
		return VxErrorInvalidState;
	}

	if (PTTAreaChannel.Value && PTTTeamChannel.Value) // Both
	{
		LastKnownTransmittingChannel = LastKnownTransmittingChannel == PTTAreaChannel.Key ? PTTTeamChannel.Key : PTTAreaChannel.Key; // flip
		return VivoxVoiceClient->GetLoginSession(LoggedInAccountID).SetTransmissionMode(TransmissionMode::All);
	}
	else if (PTTAreaChannel.Value) // Area Only
	{
		LastKnownTransmittingChannel = PTTAreaChannel.Key;
		return VivoxVoiceClient->GetLoginSession(LoggedInAccountID).SetTransmissionMode(TransmissionMode::Single, PTTAreaChannel.Key);
	}
	else if (PTTTeamChannel.Value) // Team Only
	{
		LastKnownTransmittingChannel = PTTTeamChannel.Key;
		return VivoxVoiceClient->GetLoginSession(LoggedInAccountID).SetTransmissionMode(TransmissionMode::Single, PTTTeamChannel.Key);
	}
	else // None
	{
		return VivoxVoiceClient->GetLoginSession(LoggedInAccountID).SetTransmissionMode(TransmissionMode::None);
	}
#endif
	return -1;
}

int32 UGP2GameInstance::MultiChanToggleChat(PTTKey Key)
{
#if !WITH_GAMELIFT
	if (PTTKey::PTTAreaChannel == Key && !PTTAreaChannel.Key.IsEmpty())
	{
		PTTAreaChannel.Value = !PTTAreaChannel.Value;
		UE_LOG(LogVivoxGameInstance, Log, TEXT("MultiChanToggleChat: Toggling transmission %s for %s"), PTTAreaChannel.Value ? TEXT("on") : TEXT("off"), *PTTAreaChannel.Key.Name());
		if (PTTAreaChannel.Value && PTTTeamChannel.Value)
		{
			UE_LOG(LogVivoxGameInstance, Log, TEXT("MultiChanToggleChat: Toggling transmission off for %s"), *PTTTeamChannel.Key.Name());
			PTTTeamChannel.Value = false;
		}
	}
	else if (PTTKey::PTTTeamChannel == Key && !PTTTeamChannel.Key.IsEmpty())
	{
		PTTTeamChannel.Value = !PTTTeamChannel.Value;
		UE_LOG(LogVivoxGameInstance, Log, TEXT("MultiChanToggleChat: Toggling transmission %s for %s"), PTTTeamChannel.Value ? TEXT("on") : TEXT("off"), *PTTTeamChannel.Key.Name());
		if (PTTTeamChannel.Value && PTTAreaChannel.Value)
		{
			UE_LOG(LogVivoxGameInstance, Log, TEXT("MultiChanToggleChat: Toggling transmission off for %s"), *PTTAreaChannel.Key.Name());
			PTTAreaChannel.Value = false;
		}
	}
	else
	{
		UE_LOG(LogVivoxGameInstance, Warning, TEXT("MultiChanToggleChat: No ChannelId assigned to %s"), *UEnumFullToString(PTTKey, Key));
		return VxErrorInvalidState;
	}

	if (PTTAreaChannel.Value && PTTTeamChannel.Value) // Both
	{
		ensureMsgf(false, TEXT("MultiChanToggleChat: Transmitting to all channels on console. This is safe, but was designed not to happen in this sample."));
		LastKnownTransmittingChannel = LastKnownTransmittingChannel == PTTAreaChannel.Key ? PTTTeamChannel.Key : PTTAreaChannel.Key; // flip
		return VivoxVoiceClient->GetLoginSession(LoggedInAccountID).SetTransmissionMode(TransmissionMode::All);
	}
	else if (PTTAreaChannel.Value) // Area Only
	{
		LastKnownTransmittingChannel = PTTAreaChannel.Key;
		return VivoxVoiceClient->GetLoginSession(LoggedInAccountID).SetTransmissionMode(TransmissionMode::Single, PTTAreaChannel.Key);
	}
	else if (PTTTeamChannel.Value) // Team Only
	{
		LastKnownTransmittingChannel = PTTTeamChannel.Key;
		return VivoxVoiceClient->GetLoginSession(LoggedInAccountID).SetTransmissionMode(TransmissionMode::Single, PTTTeamChannel.Key);
	}
	else // None
	{
		return VivoxVoiceClient->GetLoginSession(LoggedInAccountID).SetTransmissionMode(TransmissionMode::None);
	}
#endif
	return -1;
}

bool UGP2GameInstance::SetVivoxPlayerMuted(const FString & PlayerName, bool MuteState)
{
#if !WITH_GAMELIFT
	if (IsInitialized())
	{
		IChannelSession &ChannelSession = VivoxVoiceClient->GetLoginSession(LoggedInAccountID).GetChannelSession(PTTTeamChannel.Key);
		for (auto &pPlayer : ChannelSession.Participants())
		{
			if (pPlayer.Key == PlayerName)
			{
				pPlayer.Value->SetLocalMute(MuteState);
				return true;
			}
		}
	}
#endif
	return false;
}

int32 UGP2GameInstance::GetVoiceMicVolume()
{
#if !WITH_GAMELIFT
	return VivoxVoiceClient->AudioInputDevices().VolumeAdjustment();
#else
	return 0;
#endif
}

void UGP2GameInstance::SetVoiceMicVolume(int MicVolumeValue)
{
#if !WITH_GAMELIFT
	UE_LOG(LogVivoxGameInstance, Log, TEXT("Vivox Set Mic Volume = %d"), MicVolumeValue);
	VivoxVoiceClient->AudioInputDevices().SetVolumeAdjustment(MicVolumeValue);
#endif
}

int32 UGP2GameInstance::GetVoiceOutputVolume()
{
#if !WITH_GAMELIFT
	return  VivoxVoiceClient->AudioOutputDevices().VolumeAdjustment();
#endif
	return 0;
}

void UGP2GameInstance::SetVoiceOutputVolume(int OutputVolumeValue)
{
#if !WITH_GAMELIFT
	UE_LOG(LogVivoxGameInstance, Log, TEXT("Vivox Set Audio Output Volume = %d"), OutputVolumeValue);
	VivoxVoiceClient->AudioOutputDevices().SetVolumeAdjustment(OutputVolumeValue);
#endif
}

TMap<FString, FString> UGP2GameInstance::GetVivoxInputAudioDevices()
{
	TMap<FString, FString> InputDevices;
#if !WITH_GAMELIFT
	if (IsInitialized())
	{
		IAudioDevices &audiodevices = VivoxVoiceClient->AudioInputDevices();
		for (auto &device : audiodevices.AvailableDevices())
		{
			InputDevices.Add(*device.Key, *device.Value->Name());
		}
	}
	else {
		UE_LOG(LogVivoxGameInstance, Log, TEXT("Vivox Not Initalized"));
	}
#endif
	return InputDevices;
}

FString UGP2GameInstance::GetCurVivoxInputAudioDevice()
{
	FString CurInputDeviceID = "NONE";
#if !WITH_GAMELIFT
	if (IsInitialized())
	{
		IAudioDevices &audiodevices = VivoxVoiceClient->AudioInputDevices();
		if (!audiodevices.SystemDevice().IsEmpty())
		{
			CurInputDeviceID = audiodevices.SystemDevice().Id();
		}
		else {
			UE_LOG(LogVivoxGameInstance, Log, TEXT("Vivox Input Audio Device IS Empty"));
		}
	}
	else {
		UE_LOG(LogVivoxGameInstance, Log, TEXT("Vivox Not Initalized"));
	}
#endif
	return CurInputDeviceID;
}

TMap<FString, FString> UGP2GameInstance::GetVivoxOutputAudioDevices()
{
	TMap<FString, FString> OutputDevices;
#if !WITH_GAMELIFT
	if (IsInitialized())
	{
		IAudioDevices &audiodevices = VivoxVoiceClient->AudioOutputDevices();
		for (auto &device : audiodevices.AvailableDevices())
		{
			OutputDevices.Add(*device.Key, *device.Value->Name());
		}
	}
	else {
		UE_LOG(LogVivoxGameInstance, Log, TEXT("Vivox Not Initalized"));
	}
#endif
	return OutputDevices;
}

FString UGP2GameInstance::GetCurVivoxOutputAudioDevice()
{
	FString CurOutputDeviceID = "NONE";
#if !WITH_GAMELIFT
	if (IsInitialized())
	{
		IAudioDevices &audiodevices = VivoxVoiceClient->AudioOutputDevices();
		if (!audiodevices.SystemDevice().IsEmpty())
		{
			CurOutputDeviceID = audiodevices.SystemDevice().Id();
		}
		else {
			UE_LOG(LogVivoxGameInstance, Log, TEXT("Vivox Output Audio Device IS Empty"));
		}
	}
	else {
		UE_LOG(LogVivoxGameInstance, Log, TEXT("Vivox Not Initalized"));
	}
#endif
	return CurOutputDeviceID;
}

int32 UGP2GameInstance::SetVivoxInputDeviceChange(FString strDeviceID)//, const FOnVivoxInputDeviceChanged& theDelegate)
{
	// VX_E_FAILED = 1004
	int32 tempstatus = 1004;

#if !WITH_GAMELIFT
	if (IsInitialized())
	{
		IAudioDevices &audiodevices = VivoxVoiceClient->AudioOutputDevices();
		IAudioDevice &ChangeAudio = **audiodevices.AvailableDevices().Find(strDeviceID);
		IAudioDevices::FOnSetActiveDeviceCompletedDelegate OnSetActiveDeviceCompleteCallback;
		audiodevices.SetActiveDevice(ChangeAudio, OnSetActiveDeviceCompleteCallback);
		OnSetActiveDeviceCompleteCallback.BindLambda([this, &tempstatus](VivoxCoreError Status, const FString& strDevice)
		{
			if (VxErrorSuccess == Status)
			{
				VivoxDeviceChangeComplete(strDevice);
			}
			tempstatus = Status;
		});
		//return audiodevices.SetActiveDevice(ChangeAudio, theDelegate);
		return tempstatus;
	}
	else
		return tempstatus;
#endif
	return tempstatus;
}

// Called by the EAC client when a message should be presented to the user.
bool UGP2GameInstance::EACErrorProc(const FString& Message)
{
	// 자신의 UI를 사용하여 플레이어에게 메시지를 표시합니다.
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
	// 선택 사항: 온라인 플레이 보안과 관련된 일부 기능을 비활성화합니다.
	// 이벤트가 처리되었음을 나타내려면 참을 반환합니다.
	return true;
}

void UGP2GameInstance::GetFlexMatchData(int& MapIndex, FString& MapName, int& MaxUserCount, EGWGameMode& GameMode, EGWGamePVPRule& GamePvpRule)
{
	MapIndex = 1;
	MapName = m_Map;
	MaxUserCount = m_maximumPlayerSessionCount;
	GameMode = m_eGameMode;
	GamePvpRule = m_pvpRule;
}

void UGP2GameInstance::GetCustomMatchData(int& MapIndex, FString& MapName, int& MaxUserCount, EGWGameMode& GameMode, FString& Master, FString& Title)
{
	MapIndex = 1;
	MapName = m_Map;
	MaxUserCount = m_maximumPlayerSessionCount;
	GameMode = m_eGameMode;
	Master = m_strcurMaster;
	Title = m_strcurTitle;
}