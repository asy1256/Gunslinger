////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file	GunslingerSW\Util\UtilMesh.h
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace UtilString
{
	/// 초를 일시분초 형식의 문자열로 반환한다.
	FString SecondsToText( uint64 InSec, bool InUseZeroSec = false, bool InSkipSec = false );

	/// 초를 시간형식의 문자열로 반환한다.
	FString SecondsToClockString( uint64 InSec , bool InShowHour );

	/// 경과초를 간단형식으로 변환한다. ( %d , %d , %d , %d )
	FString PastTimeSecondsToString( uint64 createTime , bool InSkipSec );

	/// 남은초를 간단형식으로 변환한다. ( %d , %d , %d , %d )
	FString RemainTimeSecondsToString( uint64 endTime );

	/// 지정된 크기보다 긴경우 줄임말로 변환 후 반환한다. 
	FString ClippingString( const FString& InString , FString* OutReplaceString );
}
