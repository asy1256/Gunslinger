////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file	GunslingerSW\Util\UtilMesh.h
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace UtilString
{
	/// �ʸ� �Ͻú��� ������ ���ڿ��� ��ȯ�Ѵ�.
	FString SecondsToText( uint64 InSec, bool InUseZeroSec = false, bool InSkipSec = false );

	/// �ʸ� �ð������� ���ڿ��� ��ȯ�Ѵ�.
	FString SecondsToClockString( uint64 InSec , bool InShowHour );

	/// ����ʸ� ������������ ��ȯ�Ѵ�. ( %d , %d , %d , %d )
	FString PastTimeSecondsToString( uint64 createTime , bool InSkipSec );

	/// �����ʸ� ������������ ��ȯ�Ѵ�. ( %d , %d , %d , %d )
	FString RemainTimeSecondsToString( uint64 endTime );

	/// ������ ũ�⺸�� ���� ���Ӹ��� ��ȯ �� ��ȯ�Ѵ�. 
	FString ClippingString( const FString& InString , FString* OutReplaceString );
}
