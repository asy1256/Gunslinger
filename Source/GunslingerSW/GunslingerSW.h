// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GP2Log.h"

#include "GP2GameInstance.h"
#include "GP2SingletonLibrary.h"


#include <list>
#include <vector>
#include <map>


#pragma warning(disable : 4828)  

/// External Global Variables - DefaultGame.ini

/// NetworkSetting
	extern FString g_LobbyServerAddr;    /// 인증서버 주소
	extern int     g_LobbyServerPort;    /// 인증서버 포트
	extern FString g_DedicateServerAddr; /// 임시( 추후 서버에서 주소를 받아오는걸로 수정 필요 )
	extern int     g_DedicateServerPort; /// 임시( 추후 서버에서 포트를 받아오는걸로 수정 필요 )

	extern bool    g_AutoLogin;          ///
	extern FString g_AutoLoginId;        /// id/pw 동일할경우
	extern bool    g_LocalMode;          ///
	extern int     g_DefaultCharacter;   /// 

	extern bool    g_bUsingCharacterArray;
	extern TArray<FString> g_DefaultCharacters;

	extern bool    g_SkipTutorial;       /// 튜터리얼 스킵
	extern bool    g_SkipAdvent;         /// 시작연출 스킵
	extern bool    g_ShowDebug;          /// 디버그용 방향 화살표     

	extern FString g_LocalServerAddr;    /// 기본서버  0
	extern int     g_LocalServerPort;    /// 기본서버
	extern bool    g_JsonSecurity;       /// Json 암호화

	extern FString g_JapanServerAddr;    /// 일본서버  1
	extern int     g_JapanServerPort;    /// 일본서버
	extern bool    g_JsonSecurityJpn;    /// Json 암호화

	extern FString g_UsaServerAddr;      /// 미국서버  2
	extern int     g_UsaServerPort;      /// 미국서버
	extern bool    g_JsonSecurityUsa;    /// Json 암호화

	extern FString g_EUServerAddr;       /// EU서버   3
	extern int     g_EUServerPort;       /// EU서버
	extern bool    g_JsonSecurityEu;     /// Json 암호화

	extern FString g_No4ServerAddr;      /// EU서버  4
	extern int     g_No4ServerPort;      /// EU서버
	extern bool    g_JsonSecurityNo4;    /// Json 암호화

	extern FString g_No5ServerAddr;      /// EU서버  5
	extern int     g_No5ServerPort;      /// EU서버
	extern bool    g_JsonSecurityNo5;    /// Json 암호화

	/// g_Version.g_Revision.g_TargetLocal
	/// ex -  v.2020.01.1004.kr
	extern FString g_Country;            /// 패키지 대상 로컬( kr, jp, en , cn ...)
	extern FString g_Version;            /// 패키지 버전
	extern int     g_SourceRevision;	 /// 소스 리비전 번호
	extern int     g_ContentRevision;    /// 컨탠츠 리비전 번호
	extern int     g_BuildCount;         /// 전달용 카운트
	extern bool    g_QA;                 /// QA 버전 구분

	extern int g_PlatformType;           /// os 형식 - win=31 , ps4=32
	extern int g_AuthType;               /// 인증형식 - hanbiton=1, bridge=2

	extern bool g_flexmatch_test;		 /// 플랙스 매치 로직 임시


	extern FString g_direct_server_url;  /// url 직접입력

	extern int g_Gender; /// 성별
	extern int g_Class; /// 클래스
	extern int g_pvp_character_infoId; /// pvp 캐릭터 인덱스

	extern bool g_skip_web;  /// 웹통신 스킵
	extern bool g_gm_test_sc; /// 캐릭터선택창 테스트 모드
	extern bool g_gm_test_mr; /// 매칭룸 테스트 모드

	extern bool g_inventory_test; /// 인벤토리 테스트

void GP2LoadGlobals();
void GP2AppInit();
void GP2AppExit();
