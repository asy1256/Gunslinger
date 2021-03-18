// Fill out your copyright notice in the Description page of Project Settings.

#include "GunslingerSW.h"
#include "Modules/ModuleManager.h"
#include <ConfigCacheIni.h>
#include "GP2GameInstance.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, GunslingerSW, "GunslingerSW" );

DEFINE_LOG_CATEGORY( GP2Log )

/// External Global Variables - DefaultGame.ini

/// NetworkSetting
FString g_LobbyServerAddr    = TEXT( "localhost" );     
int     g_LobbyServerPort    = 3001;                    
FString g_DedicateServerAddr = TEXT( "127.0.0.1" );     
int     g_DedicateServerPort = 3001;                    

/// External Global Variables - DefaultGame.ini
bool    g_AutoLogin          = false;                   
FString g_AutoLoginId        = TEXT( "" );              
bool    g_LocalMode          = false;                   
int     g_DefaultCharacter   = 0;           
///
bool    g_SkipTutorial       = false;                   
bool    g_SkipAdvent         = false;                   
bool    g_ShowDebug          = false;       
bool    g_bUsingCharacterArray = false;
TArray<FString> g_DefaultCharacters = TArray<FString>();


FString g_LocalServerAddr = TEXT( "172.20.35.221" );
int     g_LocalServerPort = 3001;
bool    g_JsonSecurity    = false;
                          
FString g_JapanServerAddr = TEXT( "54.178.72.81" );
int     g_JapanServerPort = 3001;
bool    g_JsonSecurityJpn = false;
                          
FString g_UsaServerAddr   = TEXT( "54.67.73.155" );
int     g_UsaServerPort   = 3001;
bool    g_JsonSecurityUsa = false;
                          
                          
FString g_EUServerAddr    = TEXT("172.20.35.221");
int     g_EUServerPort    = 3001;
bool    g_JsonSecurityEu  = false;
                          
FString g_No4ServerAddr   = TEXT("172.20.35.221");
int     g_No4ServerPort   = 3001;
bool    g_JsonSecurityNo4 = false;
                          
FString g_No5ServerAddr   = TEXT("172.20.35.221");
int     g_No5ServerPort   = 3001;
bool    g_JsonSecurityNo5 = false;

FString g_Country         = TEXT( "kr" );
FString g_Version         = TEXT( "2020.01" );
int     g_SourceRevision  = 0;
int     g_ContentRevision = 0;
int     g_BuildCount      = 1;
bool    g_QA              = false;

int     g_PlatformType    = 31;
int     g_AuthType        = 1;

bool    g_flexmatch_test  = false;

int g_Gender = 1; /// 1:male 2:female
int g_Class = 1; /// 1:striker...
int g_pvp_character_infoId = 101; /// 101:tohru....

FString g_direct_server_url = TEXT("");     /// ¸ÅÄª·ë Å×½ºÆ® ¸ðµå


bool g_skip_web = false;
bool g_gm_test_sc = false;
bool g_gm_test_mr = false;
bool g_inventory_test = false;

template< class T, class D >
void _IniLoader( T& outValue, D& InDelegate,  const TCHAR* InSection , const TCHAR* InKey )
{
	T val = T();
	if ( InDelegate.Execute( InSection , InKey , val , GGameIni ) )
		outValue = val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	
////////////////////////////////////////////////////////////////////////////////////////////////////
void GP2LoadGlobals()
{
	if ( !GConfig ) return;

	FConfigCacheIni::LoadGlobalIniFile( GGameIni , TEXT( "Game" ) , NULL , true );
	// FConfigCacheIni::LoadGlobalIniFile( GGameUserSettingsIni , TEXT( "" ) , NULL , true );

	DECLARE_DELEGATE_RetVal_FourParams( bool , FDelegateBool   , const TCHAR* , const TCHAR* , bool&    , const FString& );
	DECLARE_DELEGATE_RetVal_FourParams( bool , FDelegateInt    , const TCHAR* , const TCHAR* , int&     , const FString& );
	DECLARE_DELEGATE_RetVal_FourParams( bool , FDelegateFloat  , const TCHAR* , const TCHAR* , float&   , const FString& );
	DECLARE_DELEGATE_RetVal_FourParams( bool , FDelegateString , const TCHAR* , const TCHAR* , FString& , const FString& );
	DECLARE_DELEGATE_RetVal_FourParams( int , FDelegateArray  , const TCHAR* , const TCHAR* , TArray<FString>& , const FString& );



	FDelegateBool delBool;
	delBool.BindRaw( GConfig , &FConfigCacheIni::GetBool );
	FDelegateInt delInt;
	delInt.BindRaw( GConfig , &FConfigCacheIni::GetInt );
	FDelegateFloat delFloat;
	delFloat.BindRaw( GConfig , &FConfigCacheIni::GetFloat );
	FDelegateString delString;
	delString.BindRaw( GConfig , &FConfigCacheIni::GetString );

	FDelegateArray DelegateArray;
	DelegateArray.BindRaw(  GConfig , &FConfigCacheIni::GetArray );


	/// NetwortSetting                           
	_IniLoader( g_LobbyServerAddr    , delString , TEXT( "NetworkSetting" ) , TEXT( "LobbyServerAddr" ) );
	_IniLoader( g_LobbyServerPort    , delInt    , TEXT( "NetworkSetting" ) , TEXT( "LobbyServerPort" ) );
	_IniLoader( g_DedicateServerAddr , delString , TEXT( "NetworkSetting" ) , TEXT( "DedicateServerAddr" ) );
	_IniLoader( g_DedicateServerPort , delInt    , TEXT( "NetworkSetting" ) , TEXT( "DedicateServerPort" ) );
                                                 
	// _IniLoader( g_Https           , delBool   , TEXT( "NetworkSetting" ) , TEXT( "Https" ) );
                                                 
	_IniLoader( g_LocalServerAddr    , delString , TEXT( "NetworkSetting" ) , TEXT( "LocalServerAddr" ) );
	_IniLoader( g_LocalServerPort    , delInt    , TEXT( "NetworkSetting" ) , TEXT( "LocalServerPort" ) );
	_IniLoader( g_JsonSecurity       , delBool   , TEXT( "NetworkSetting" ) , TEXT( "JsonSecurity" ) );
                                                 
	_IniLoader( g_JapanServerAddr    , delString , TEXT( "NetworkSetting" ) , TEXT( "JapanServerAddr" ) );
	_IniLoader( g_JapanServerPort    , delInt    , TEXT( "NetworkSetting" ) , TEXT( "JapanServerPort" ) );
	_IniLoader( g_JsonSecurityJpn    , delBool   , TEXT( "NetworkSetting" ) , TEXT( "JsonSecurityJpn" ) );
                                                 
	_IniLoader( g_UsaServerAddr      , delString , TEXT( "NetworkSetting" ) , TEXT( "UsaServerAddr" ) );
	_IniLoader( g_UsaServerPort      , delInt    , TEXT( "NetworkSetting" ) , TEXT( "UsaServerPort" ) );
	_IniLoader( g_JsonSecurityUsa    , delBool   , TEXT( "NetworkSetting" ) , TEXT( "JsonSecurityUsa" ) );
                                                 
	_IniLoader( g_EUServerAddr       , delString , TEXT( "NetworkSetting" ) , TEXT( "EUServerAddr" ) );
	_IniLoader( g_EUServerPort       , delInt    , TEXT( "NetworkSetting" ) , TEXT( "EUServerPort" ) );
	_IniLoader( g_JsonSecurityEu     , delBool   , TEXT( "NetworkSetting" ) , TEXT( "JsonSecurityEU" ) );
                                                 
	_IniLoader( g_No4ServerAddr      , delString , TEXT( "NetworkSetting" ) , TEXT( "No4ServerAddr" ) );
	_IniLoader( g_No4ServerPort      , delInt    , TEXT( "NetworkSetting" ) , TEXT( "No4ServerPort" ) );
	_IniLoader( g_JsonSecurityNo4    , delBool   , TEXT( "NetworkSetting" ) , TEXT( "JsonSecurityNo4" ) );
                                                 
	_IniLoader( g_No5ServerAddr      , delString , TEXT( "NetworkSetting" ) , TEXT( "No5ServerAddr" ) );
	_IniLoader( g_No5ServerPort      , delInt    , TEXT( "NetworkSetting" ) , TEXT( "No5ServerPort" ) );
	_IniLoader( g_JsonSecurityNo5    , delBool   , TEXT( "NetworkSetting" ) , TEXT( "JsonSecurityNo5" ) );
                                                 
                                               
	/// NetwortSetting                           
	_IniLoader( g_AutoLogin          , delBool   , TEXT( "NetworkSetting" ) , TEXT( "AutoLogin" ) );
	_IniLoader( g_AutoLoginId        , delString , TEXT( "NetworkSetting" ) , TEXT( "AutoLoginId" ) );
	_IniLoader( g_LocalMode          , delBool   , TEXT( "NetworkSetting" ) , TEXT( "LocalMode" ) );
	_IniLoader( g_DefaultCharacter   , delInt    , TEXT( "NetworkSetting" ) , TEXT( "DefaultCharacter" ) );

	/// InGameSettings                           
	_IniLoader( g_SkipAdvent         , delBool   , TEXT( "InGameSettings" ) , TEXT( "SkipAdvent" ) );
	_IniLoader( g_ShowDebug          , delBool   , TEXT( "InGameSettings" ) , TEXT( "ShowDebugArrow" ) );
	_IniLoader( g_Country            , delString , TEXT( "InGameSettings" ) , TEXT( "Country" ) );
	_IniLoader( g_Version            , delString , TEXT( "InGameSettings" ) , TEXT( "Version" ) );
	_IniLoader( g_SourceRevision     , delInt    , TEXT( "InGameSettings" ) , TEXT( "SRev" ) );
	_IniLoader( g_ContentRevision    , delInt    , TEXT( "InGameSettings" ) , TEXT( "CRev" ) );
	_IniLoader( g_BuildCount         , delInt    , TEXT( "InGameSettings" ) , TEXT( "BuildCount" ) );
	_IniLoader( g_QA                 , delBool   , TEXT( "InGameSettings" ) , TEXT( "QA" ) );
	_IniLoader( g_bUsingCharacterArray , delBool , TEXT( "InGameSettings" ) , TEXT( "UsingCharacterArray" ) );
	_IniLoader( g_DefaultCharacters , DelegateArray , TEXT( "InGameSettings" ) , TEXT( "DefaultCharacters" ) );

                                                 
	_IniLoader( g_PlatformType       , delInt    , TEXT( "InGameSettings" ) , TEXT( "PlatformType" ) );
	_IniLoader( g_AuthType           , delInt    , TEXT( "InGameSettings" ) , TEXT( "AuthType" ) );
	_IniLoader( g_flexmatch_test     , delBool   , TEXT("InGameSettings")   , TEXT("FlexMatchTest"));
	
	/// InGameTestSettings
	_IniLoader( g_Gender               , delInt  , TEXT( "InGameTestSettings" ) , TEXT( "Gender") );
	_IniLoader( g_Class                , delInt  , TEXT( "InGameTestSettings" ) , TEXT( "Class") );
	_IniLoader( g_pvp_character_infoId , delInt  , TEXT( "InGameTestSettings" ) , TEXT( "PVP") );
	_IniLoader( g_SkipTutorial         , delBool , TEXT( "InGameTestSettings" ) , TEXT( "SkipTutorial" ) );

	_IniLoader( g_skip_web , delBool , TEXT( "InGameTestSettings" ) , TEXT( "SkipWeb" ) );
	_IniLoader( g_gm_test_sc , delBool , TEXT( "InGameTestSettings" ) , TEXT( "TestSC" ) );
	_IniLoader( g_gm_test_mr , delBool , TEXT( "InGameTestSettings" ) , TEXT( "TestMR" ) );
	_IniLoader( g_inventory_test, delBool, TEXT("InGameTestSettings"), TEXT("TestInventory"));
	


	FString url;
	if ( FParse::Value( FCommandLine::Get(), TEXT( "url=" ), url ) )
	{
		g_direct_server_url = url;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	
////////////////////////////////////////////////////////////////////////////////////////////////////
void GP2AppInit()
{
	GP2LOG( "" );

	Gp2SingletonStartup();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	
////////////////////////////////////////////////////////////////////////////////////////////////////
void GP2AppExit()
{
	/// SDK Release
	/// 
	GP2LOG( "" );
}
