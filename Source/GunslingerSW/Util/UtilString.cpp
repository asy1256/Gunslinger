////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file	GunslingerSW\Util\UtilString.h
////////////////////////////////////////////////////////////////////////////////////////////////////

//#pragma once

#include "UtilString.h"
#include "GunslingerSW.h"

namespace UtilString
{
	/// �ʸ� 'd�� h�� m�� s��' ������ ���ڿ��� ��ȯ�Ѵ�.
	FString SecondsToText( uint64 InSec , bool InUseZeroSec , bool InSkipSec )
	{
		int64 d = InSec / 86400; if ( d ) InSec -= ( d * 86400 );
		int64 h = InSec / 3600;  if ( h ) InSec -= ( h * 3600  );
		int64 m = InSec / 60;    if ( m ) InSec -= ( m * 60    );
		int64 s = InSec % 60;    

		FString ret;

		if ( d )
		{
			if ( !ret.IsEmpty() ) ret += " ";
			ret += FString::FromInt( d );
			ret += "Day";
		}

		if ( h )
		{
			if ( !ret.IsEmpty() ) ret += " ";
			ret += FString::FromInt( h );
			ret += "Hour";
		}

		if ( m )
		{
			if ( !ret.IsEmpty() ) ret += " ";
			ret += FString::FromInt( m );
			ret += "Minute";
		}

		if ( !InSkipSec && ( InUseZeroSec || s ) )
		{
			if ( !ret.IsEmpty() ) ret += " ";
			ret += FString::FromInt( s );
			ret += "Second";
		}

		return ret;
	}

	/// �ʸ� �ð������� ���ڿ��� ��ȯ�Ѵ�.( hh:mm:ss )
	FString SecondsToClockString( uint64 InSec , bool InShowHour )
	{
		// int64 d = InSec / 86400; if ( d ) InSec -= ( d * 86400 );
		int64 h = InSec / 3600;  if ( h ) InSec -= ( h * 3600 );
		int64 m = InSec / 60;    if ( m ) InSec -= ( m * 60 );
		int64 s = InSec % 60;

		FString ret;

		if( InShowHour )
			ret = FString::Printf( TEXT( "%02d:%02d:%02d" ) , h , m , s );
		else
			ret = FString::Printf( TEXT( "%02d:%02d" ) , m , s );

		return ret;
	}

	/// ����ʸ� ������������ ��ȯ�Ѵ�. ( %d , %d , %d , %d )
	FString PastTimeSecondsToString( uint64 InCreateTime , bool InSkipSec )
	{
		int64 seconds = 0 - InCreateTime;

		int64 d = seconds / 86400; if ( d ) seconds -= ( d * 86400 );
		int64 h = seconds / 3600;  if ( h ) seconds -= ( h * 3600 );
		int64 m = seconds / 60;    if ( m ) seconds -= ( m * 60 );
		int64 s = seconds % 60;

		FString ret;

		if( d )
		{
			ret  = FString::FromInt( d );
			ret += "Day";
			return ret;
		}

		if ( h )
		{
			ret  = FString::FromInt( h );
			ret += "Hour";
			return ret;
		}

		if ( m )
		{
			ret  = FString::FromInt( m );
			ret += "Minute";
			return ret;
		}

		if( InSkipSec )
		{
			return "Time Minutes Less";
		}
		else 
		{
			ret  = FString::FromInt( s );
			ret += "Second";
			return ret;
		}

		return "";
	}

	/// ����ʸ� ������������ ��ȯ�Ѵ�. ( %d , %d , %d , %d )
	FString RemainTimeSecondsToString( uint64 InEndTime , bool InSkipSec )
	{
		int64 seconds = InEndTime - 0;

		int64 d = seconds / 86400; if ( d ) seconds -= ( d * 86400 );
		int64 h = seconds / 3600;  if ( h ) seconds -= ( h * 3600 );
		int64 m = seconds / 60;    if ( m ) seconds -= ( m * 60 );
		int64 s = seconds % 60;

		FString ret;

		if ( d )
		{
			ret += FString::FromInt( d );
			ret += "";
			return ret;
		}

		if ( h )
		{
			ret += FString::FromInt( h );
			ret += "";
			return ret;
		}

		if ( m )
		{
			ret += FString::FromInt( m );
			ret += "";
			return ret;
		}

		if( InSkipSec )
		{
		}
		else 
		{
			ret += FString::FromInt( s );
			ret += "";
			return ret;
		}

		return "";
	}

	/// ������ ũ�⺸�� ���� ���Ӹ��� ��ȯ �� ��ȯ�Ѵ�. 
	FString ClippingString( const FString& InString , int32 InSize )
	{
		FString TargetString;

		int32 Size = InString.Len();
		if ( Size > InSize )
		{
			int32 ClippingSize = Size - InSize;
			TargetString = InString.LeftChop( ClippingSize );
			TargetString += "...";
		}
		else
		{
			TargetString = InString;
		}

		return TargetString;
	}	
}
