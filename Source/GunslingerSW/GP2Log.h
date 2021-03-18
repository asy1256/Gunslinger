////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file	GunslingerSW\G2Log.h
///
/// @brief	Declares the log class
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

DECLARE_LOG_CATEGORY_EXTERN( GP2Log , Log , All )

#if PLATFORM_WINDOWS
#define GP2_FUNC_NAME TEXT( __FUNCTION__ ) TEXT( "()" )
#elif PLATFORM_PS4
#define GP2_FUNC_NAME 
#else
#define GP2_FUNC_NAME __FUNCTION__
#endif 


#if UE_BUILD_SHIPPING

	#define _GP2LOG( Category, Prefix, Format, ... ) {}
                                                    
	#define GP2LOG( Format, ... )                    {}
	#define GP2LOG_WARN( Format, ... )               {}
	#define GP2LOG_ERROR( Format, ... )              {}
                                                    
	#define GP2LOG_SCREEN( Format, ... )             {}

#else

	#define _GP2LOG( Category, Prefix, Format, ... )                          \
	{                                                                         \
		FString _output = FString::Printf( TEXT( "%s : " ) , GP2_FUNC_NAME ); \
		_output += FString::Printf( Format , ##__VA_ARGS__ );                 \
		UE_LOG( Category , Log , TEXT( "%s %s" ) , Prefix , *_output );       \
	}                                                                         \

	#define GP2LOG( Format, ... )       {                                 _GP2LOG( GP2Log, TEXT("") , TEXT(Format), ##__VA_ARGS__ );                     }
	#define GP2LOG_WARN( Format, ... )  { SET_WARN_COLOR( COLOR_YELLOW ); _GP2LOG( GP2Log, TEXT("") , TEXT(Format), ##__VA_ARGS__ ); CLEAR_WARN_COLOR(); }
	#define GP2LOG_ERROR( Format, ... ) { SET_WARN_COLOR( COLOR_RED );    _GP2LOG( GP2Log, TEXT("") , TEXT(Format), ##__VA_ARGS__ ); CLEAR_WARN_COLOR(); }

	#define GP2LOG_SCREEN( Format, ... )                                         \
	{                                                                            \
		FString _output = FString::Printf( TEXT( "%s : "), GP2_FUNC_NAME );      \
		_output += FString::Printf( TEXT( Format ), ##__VA_ARGS__ );             \
		UE_LOG( GP2Log, Log, TEXT( "%s"), *_output );                             \
		GEngine->AddOnScreenDebugMessage( -1 , 7.0f , FColor(0,0,0,0) , _output ); \
	}                                                                            \

#endif