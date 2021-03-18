// Fill out your copyright notice in the Description page of Project Settings.

#include "InfoManager.h"



//bool UInfoManager::UInfoManager::GetLocalStringInfo(FLocalStringInfo& OutInfo, const FString& InString)
//{
//	if (CharacterInfoTable)
//	{
//		FST_LocalStringInfo* TableInfo = CharacterInfoTable->FindRow<FST_LocalStringInfo>(FName(*InString), FString(""));
//		if (TableInfo)
//		{
//			OutInfo = *TableInfo;
//			return true;
//		}
//	}
//	return false;
//}


bool UInfoManager::GetAnimationListInfo( const FString& Key , FGWAnimationListInfo& OutInfo )
{
	if (AnimationListInfoTable)
	{
		FGWAnimationListInfo* Info = AnimationListInfoTable->FindRow<FGWAnimationListInfo>( FName( *Key ) , FString( "" ) );
		if ( Info )
		{
			OutInfo = *Info;
			return true;
		}
	}

	return false;
}