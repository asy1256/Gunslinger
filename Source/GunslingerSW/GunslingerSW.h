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
	extern FString g_LobbyServerAddr;    /// �������� �ּ�
	extern int     g_LobbyServerPort;    /// �������� ��Ʈ
	extern FString g_DedicateServerAddr; /// �ӽ�( ���� �������� �ּҸ� �޾ƿ��°ɷ� ���� �ʿ� )
	extern int     g_DedicateServerPort; /// �ӽ�( ���� �������� ��Ʈ�� �޾ƿ��°ɷ� ���� �ʿ� )

	extern bool    g_AutoLogin;          ///
	extern FString g_AutoLoginId;        /// id/pw �����Ұ��
	extern bool    g_LocalMode;          ///
	extern int     g_DefaultCharacter;   /// 

	extern bool    g_bUsingCharacterArray;
	extern TArray<FString> g_DefaultCharacters;

	extern bool    g_SkipTutorial;       /// Ʃ�͸��� ��ŵ
	extern bool    g_SkipAdvent;         /// ���ۿ��� ��ŵ
	extern bool    g_ShowDebug;          /// ����׿� ���� ȭ��ǥ     

	extern FString g_LocalServerAddr;    /// �⺻����  0
	extern int     g_LocalServerPort;    /// �⺻����
	extern bool    g_JsonSecurity;       /// Json ��ȣȭ

	extern FString g_JapanServerAddr;    /// �Ϻ�����  1
	extern int     g_JapanServerPort;    /// �Ϻ�����
	extern bool    g_JsonSecurityJpn;    /// Json ��ȣȭ

	extern FString g_UsaServerAddr;      /// �̱�����  2
	extern int     g_UsaServerPort;      /// �̱�����
	extern bool    g_JsonSecurityUsa;    /// Json ��ȣȭ

	extern FString g_EUServerAddr;       /// EU����   3
	extern int     g_EUServerPort;       /// EU����
	extern bool    g_JsonSecurityEu;     /// Json ��ȣȭ

	extern FString g_No4ServerAddr;      /// EU����  4
	extern int     g_No4ServerPort;      /// EU����
	extern bool    g_JsonSecurityNo4;    /// Json ��ȣȭ

	extern FString g_No5ServerAddr;      /// EU����  5
	extern int     g_No5ServerPort;      /// EU����
	extern bool    g_JsonSecurityNo5;    /// Json ��ȣȭ

	/// g_Version.g_Revision.g_TargetLocal
	/// ex -  v.2020.01.1004.kr
	extern FString g_Country;            /// ��Ű�� ��� ����( kr, jp, en , cn ...)
	extern FString g_Version;            /// ��Ű�� ����
	extern int     g_SourceRevision;	 /// �ҽ� ������ ��ȣ
	extern int     g_ContentRevision;    /// ������ ������ ��ȣ
	extern int     g_BuildCount;         /// ���޿� ī��Ʈ
	extern bool    g_QA;                 /// QA ���� ����

	extern int g_PlatformType;           /// os ���� - win=31 , ps4=32
	extern int g_AuthType;               /// �������� - hanbiton=1, bridge=2

	extern bool g_flexmatch_test;		 /// �÷��� ��ġ ���� �ӽ�


	extern FString g_direct_server_url;  /// url �����Է�

	extern int g_Gender; /// ����
	extern int g_Class; /// Ŭ����
	extern int g_pvp_character_infoId; /// pvp ĳ���� �ε���

	extern bool g_skip_web;  /// ����� ��ŵ
	extern bool g_gm_test_sc; /// ĳ���ͼ���â �׽�Ʈ ���
	extern bool g_gm_test_mr; /// ��Ī�� �׽�Ʈ ���

	extern bool g_inventory_test; /// �κ��丮 �׽�Ʈ

void GP2LoadGlobals();
void GP2AppInit();
void GP2AppExit();
