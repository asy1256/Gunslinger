// Fill out your copyright notice in the Description page of Project Settings.

#include "GP2GMBase.h"
#include "GunslingerSW.h"
#include "Kismet/GameplayStatics.h"
#include "GP2GameInstance.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"
#include "IEasyAntiCheatServer.h"

///================================================================================================
///		Name :	
///================================================================================================
AGP2GMBase::AGP2GMBase()
{
	InitData();
}

///================================================================================================
///		Name :	
///================================================================================================
void AGP2GMBase::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
}

///================================================================================================
///		Name :	PreLogin
///================================================================================================
void AGP2GMBase::PreLogin( const FString& Options , const FString& Address , const FUniqueNetIdRepl& UniqueId , FString& ErrorMessage )
{
#if WITH_GAMELIFT
	if ( Role != ROLE_Authority )
		return;

	UGP2GameInstance * getGameInstance = Cast<UGP2GameInstance>( GetWorld()->GetGameInstance() );

	if ( !getGameInstance )
	{
		ErrorMessage = "GameInstance Not Found";
		return;
	}

	if ( !getGameInstance->getGameLiftActive() )
	{
		ErrorMessage = "Not Active GameSession";
		return;
	}
#endif
}

///================================================================================================
///		Name :	
///================================================================================================
void AGP2GMBase::OnResponseReceived( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bWasSuccessful )
{
}

///================================================================================================
///		Name :	
///================================================================================================
void AGP2GMBase::InitData()
{
	m_RedTeamMap.Add( 0 , false );
	m_RedTeamMap.Add( 1 , false );
	m_RedTeamMap.Add( 2 , false );
	m_RedTeamMap.Add( 3 , false );

	m_BlueTeamMap.Add( 0 , false );
	m_BlueTeamMap.Add( 1 , false );
	m_BlueTeamMap.Add( 2 , false );
	m_BlueTeamMap.Add( 3 , false );

	m_AcceptList.Empty();
}

///================================================================================================
///		Name :	
///================================================================================================
void AGP2GMBase::getTeamInfo( int32 &getTeam , uint8 &getSlot )
{
	int32 selectTeam = 1;
	uint8 byRedCount = 0 , byBlueCount = 0;
	UGP2GameInstance * getGameInstance = nullptr;

	if ( GetWorld() )
		getGameInstance = Cast<UGP2GameInstance>( GetWorld()->GetGameInstance() );

	if ( !getGameInstance )
	{
		UE_LOG( LogTemp , Error , TEXT( "%s %d GetInstance Error" ) , __FUNCTION__ , __LINE__ );
		return;
	}

	for ( auto &Elem : m_RedTeamMap )
	{
		if ( Elem.Value )
			byRedCount++;
	}

	for ( auto &Elem : m_BlueTeamMap )
	{
		if ( Elem.Value )
			byBlueCount++;
	}

	if ( ( byRedCount == 0 && byBlueCount == 0 ) || ( getGameInstance->getGameMode() == EGWGameMode::PVE ) )
	{
		getTeam = 2;
	}
	else
	{
		if ( byRedCount > byBlueCount )
			getTeam = 2;
		else if ( byRedCount < byBlueCount )
			getTeam = 1;
		else
		{
			if ( m_eLastSelectTeam == 2 )
				getTeam = 1;
			else
				getTeam = 2;
		}
	}

	m_eLastSelectTeam = getTeam;
	getSlot = getEmptySlot( getTeam );
}

///================================================================================================
///		Name :	
///================================================================================================
void AGP2GMBase::LoginSessionCheck( const int &PlayerID , const FString &PlayerSessionID , const int &UserSN , bool &CheckResult , int &errorType )
{
#if WITH_GAMELIFT
	if ( GetWorld() )
	{
		UGP2GameInstance * getGameInstance = Cast<UGP2GameInstance>( GetWorld()->GetGameInstance() );

		if ( getGameInstance )
		{
			getGameInstance->LoginSessionCheck( PlayerID , PlayerSessionID , UserSN , CheckResult , errorType );

			if ( getGameInstance->getEnterUserCount() == 1 )
				InitData();
		}
	}

	if ( CheckResult )
	{
		m_AcceptList.AddUnique( UserSN );
	}
#endif
}

///================================================================================================
///		Name :	
///================================================================================================
void AGP2GMBase::LogoutProcess( const int &PlayerID , const int &LogOutUserSN , const int32 &LogOutTeam , const int &LogOutSlot , int &MasterUserSN )
{
	UGP2GameInstance * getGameInstance = Cast<UGP2GameInstance>( GetWorld()->GetGameInstance() );

	getGameInstance->LogoutProcess( PlayerID );

	if ( getGameInstance && getGameInstance->getEnterUserCount() == 0 )
	{
		InitData();
	}
	else
	{
		MasterUserSN = 0;

		if ( m_AcceptList.Num() > 1 )
		{
			int32 Index;

			if ( m_AcceptList.Find( LogOutUserSN , Index ) )
			{
				m_AcceptList.RemoveAt( Index );

				if ( Index == 0 )
					MasterUserSN = m_AcceptList[ 0 ];
			}
		}

		if ( LogOutTeam == 2 )
		{
			if ( m_BlueTeamMap.Contains( LogOutSlot ) )
				m_BlueTeamMap[ LogOutSlot ] = false;
		}
		else if ( LogOutTeam == 1 )
		{
			if ( m_RedTeamMap.Contains( LogOutSlot ) )
				m_RedTeamMap[ LogOutSlot ] = false;
		}
	}
#if 0
	FHttpModule* Http;

	Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject( this , &AGP2GMBase::OnResponseReceived );

	UWorld* World = GetWorld();

	if ( World )
	{
		FString PostData = FString::Printf( TEXT( "gamesessionid=%s" ) , *m_GameSessionID );

		Request->SetURL( "http://localhost:3001/testServer/roomout" );
		Request->SetVerb( "POST" );
		Request->SetHeader( TEXT( "User-Agent" ) , "X-UnrealEngine-Agent" );
		Request->SetHeader( "Content-Type" , TEXT( "application/x-www-form-urlencoded" ) );
		Request->SetContentAsString( PostData );
		Request->ProcessRequest();
	}
#endif
}

///================================================================================================
///		Name :	
///================================================================================================
void AGP2GMBase::eacLogEventGameRoundStart()
{
	// Log round start to EAC.
	if ( IEasyAntiCheatServer::IsAvailable() && IEasyAntiCheatServer::Get().IsActive() && GetWorld() )
	{
		IEasyAntiCheatServer::Get().LogEventGameRoundStart( GetWorld()->GetMapName() , this->GetName() , ( uint32 ) MaxTime );
	}
}

///================================================================================================
///		Name :	
///================================================================================================
void AGP2GMBase::eacLogEventGameRoundEnd()
{
	// Log round end to EAC. It seems that ShooterGame doesn't actually determine
		// which team won by default so just log it as a constant 0.
	if ( IEasyAntiCheatServer::IsAvailable() && IEasyAntiCheatServer::Get().IsActive() )
	{
		IEasyAntiCheatServer::Get().LogEventGameRoundEnd( 0 );
	}
}

///================================================================================================
///		Name :	
///================================================================================================
uint8 AGP2GMBase::getEmptySlot( int32 &Team )
{
	uint8 bySlotIdx = 0;

	if ( Team == 2 )
	{
		for ( auto Elem : m_BlueTeamMap )
		{
			if ( !Elem.Value )
			{
				m_BlueTeamMap.Add( bySlotIdx , true );
				return bySlotIdx;
			}

			bySlotIdx++;
		}
	}
	else
	{
		for ( auto Elem : m_RedTeamMap )
		{
			if ( !Elem.Value )
			{
				m_RedTeamMap.Add( bySlotIdx , true );
				return bySlotIdx;
			}

			bySlotIdx++;
		}
	}

	return bySlotIdx;
}

void AGP2GMBase::TeamChange( const int& Slot , const int32& Team , bool& Result, int& ChangeSlot, int32& ChangedTeam )
{
	Result = false;

	if( Team == 2 )
	{
		for ( auto elem : m_RedTeamMap )
		{
			if ( !elem.Value )
			{
				ChangedTeam = 1;
				ChangeSlot = elem.Key;
				Result = true;
				m_BlueTeamMap[ Slot ] = false;
				m_RedTeamMap[ ChangeSlot ] = true;
				return;
			}
		}	
	}
	else if ( Team == 1 )
	{
		for ( auto elem : m_BlueTeamMap )
		{
			if ( !elem.Value )
			{
				ChangedTeam = 2;
				ChangeSlot = elem.Key;
				Result = true;
				m_BlueTeamMap[ ChangeSlot ] = true;
				m_RedTeamMap[ Slot ] = false;
				return;
			}
		}
	}
}

bool AGP2GMBase::IsEmptySlot( int32 team , uint8 slot )
{
	if( team == 1 )
	{
		return m_RedTeamMap[ slot ];
	}
	else if ( team == 2 )
	{
		return m_BlueTeamMap[ slot ];
	}

	return false;
}