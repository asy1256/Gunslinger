// Fill out your copyright notice in the Description page of Project Settings.

#include "GP2BlueprintFunctionLibrary.h"
#include "GunslingerSW.h"



TArray<FString> UGP2BlueprintFunctionLibrary::SortStringArray(const TArray<FString>& StringArray, const bool Reversed)
{
	TArray<FString> Array = StringArray;
	if ( !Reversed )
	{
		Array.Sort([](const FString& A, const FString& B)
		{
			return A < B;
		});
	}
	else
	{
		Array.Sort([](const FString& A, const FString& B)
		{
			return A > B;
		});
	}
	return Array;
}

void UGP2BlueprintFunctionLibrary::SortStringArrayDirectly(UPARAM(ref) TArray<FString>& StringArray, const bool Reversed)
{
	if ( !Reversed )
	{
		StringArray.Sort([](const FString& A, const FString& B)
		{
			return A < B;
		});
	}
	else
	{
		StringArray.Sort([](const FString& A, const FString& B)
		{
			return A > B;
		});
	}
}


TArray<int32> UGP2BlueprintFunctionLibrary::SortIntegerArray(const TArray<int32>& IntegerArray, const bool Reversed)
{
	TArray<int32> Array = IntegerArray;
	if ( !Reversed )
	{
		Array.Sort([](const int32 A, const int32 B)
		{
			return A < B;
		});
	}
	else
	{
		Array.Sort([](const int32 A, const int32 B)
		{
			return A > B;
		});
	}
	return Array;
}

void UGP2BlueprintFunctionLibrary::SortIntegerArrayDirectly(UPARAM(ref) TArray<int32>& IntegerArray, const bool Reversed)
{
	if ( !Reversed )
	{
		IntegerArray.Sort([](const int32 A, const int32 B)
		{
			return A < B;
		});
	}
	else
	{
		IntegerArray.Sort([](const int32 A, const int32 B)
		{
			return A > B;
		});
	}
}


TArray<float> UGP2BlueprintFunctionLibrary::SortFloatArray(const TArray<float>& FloatArray, const bool Reversed)
{
	TArray<float> Array = FloatArray;
	if ( !Reversed )
	{
		Array.Sort([](const float A, const float B)
		{
			return A < B;
		});
	}
	else
	{
		Array.Sort([](const float A, const float B)
		{
			return A > B;
		});
	}
	return Array;
}

void UGP2BlueprintFunctionLibrary::SortFloatArrayDirectly(UPARAM(ref) TArray<float>& FloatArray, const bool Reversed)
{
	if ( !Reversed )
	{
		FloatArray.Sort([](const float A, const float B)
		{
			return A < B;
		});
	}
	else
	{
		FloatArray.Sort([](const float A, const float B)
		{
			return A > B;
		});
	}
}


TArray<uint8> UGP2BlueprintFunctionLibrary::SortByteArray(const TArray<uint8>& ByteArray, const bool Reversed)
{
	TArray<uint8> Array = ByteArray;
	if ( !Reversed )
	{
		Array.Sort([](const uint8 A, const uint8 B)
		{
			return A < B;
		});
	}
	else
	{
		Array.Sort([](const uint8 A, const uint8 B)
		{
			return A > B;
		});
	}
	return Array;
}

void UGP2BlueprintFunctionLibrary::SortByteArrayDirectly(UPARAM(ref) TArray<uint8>& ByteArray, const bool Reversed)
{
	if ( !Reversed )
	{
		ByteArray.Sort([](const uint8 A, const uint8 B)
		{
			return A < B;
		});
	}
	else
	{
		ByteArray.Sort([](const uint8 A, const uint8 B)
		{
			return A > B;
		});
	}
}


TArray<FDateTime> UGP2BlueprintFunctionLibrary::SortDateTimeArray(const TArray<FDateTime>& DateTimeArray, const bool Reversed)
{
	TArray<FDateTime> Array = DateTimeArray;
	if ( !Reversed )
	{
		Array.Sort([](const FDateTime& A, const FDateTime& B)
		{
			return A < B;
		});
	}
	else
	{
		Array.Sort([](const FDateTime& A, const FDateTime& B)
		{
			return A > B;
		});
	}
	return Array;
}

void UGP2BlueprintFunctionLibrary::SortDateTimeArrayDirectly(UPARAM(ref) TArray<FDateTime>& DateTimeArray, const bool Reversed)
{
	if ( !Reversed )
	{
		DateTimeArray.Sort([](const FDateTime& A, const FDateTime& B)
		{
			return A < B;
		});
	}
	else
	{
		DateTimeArray.Sort([](const FDateTime& A, const FDateTime& B)
		{
			return A > B;
		});
	}
}


TArray<FTimespan> UGP2BlueprintFunctionLibrary::SortTimespanArray(const TArray<FTimespan>& TimespanArray, const bool Reversed)
{
	TArray<FTimespan> Array = TimespanArray;
	if ( !Reversed )
	{
		Array.Sort([](const FTimespan& A, const FTimespan& B)
		{
			return A < B;
		});
	}
	else
	{
		Array.Sort([](const FTimespan& A, const FTimespan& B)
		{
			return A > B;
		});
	}
	return Array;
}

void UGP2BlueprintFunctionLibrary::SortTimespanArrayDirectly(UPARAM(ref) TArray<FTimespan>& TimespanArray, const bool Reversed)
{
	if ( !Reversed )
	{
		TimespanArray.Sort([](const FTimespan& A, const FTimespan& B)
		{
			return A < B;
		});
	}
	else
	{
		TimespanArray.Sort([](const FTimespan& A, const FTimespan& B)
		{
			return A > B;
		});
	}
}




/*
Object Sort
*/
TArray<UObject*> UGP2BlueprintFunctionLibrary::SortObjectArray(const TArray<UObject*>& ObjectArray, FDelegateCompareObjects Comparator, const bool Reversed)
{
	TArray<UObject*> Array = ObjectArray;
	if ( !Reversed )
	{
		Array.Sort([Comparator](UObject& A, UObject& B)
		{
			bool Result = false;
			Comparator.Execute(&A, &B, Result);
			return Result;
		});
	}
	else
	{
		Array.Sort([Comparator](UObject& A, UObject& B)
		{
			bool Result = false;
			Comparator.Execute(&A, &B, Result);
			return !Result;
		});
	}
	return Array;
}


void UGP2BlueprintFunctionLibrary::SortObjectArrayDirectly(UPARAM(ref) TArray<UObject*>& ObjectArray, FDelegateCompareObjects Comparator, const bool Reversed)
{
	if ( !Reversed )
	{
		ObjectArray.Sort([Comparator](UObject& A, UObject& B)
		{
			bool Result = false;
			Comparator.Execute(&A, &B, Result);
			return Result;
		});
	}
	else
	{
		ObjectArray.Sort([Comparator](UObject& A, UObject& B)
		{
			bool Result = false;
			Comparator.Execute(&A, &B, Result);
			return !Result;
		});
	}
}


/*
Struct Sort
*/
TArray<UUserDefinedStruct*> UGP2BlueprintFunctionLibrary::SortStructArray(const TArray<UUserDefinedStruct*>& StructArray, FDelegateCompareStructs Comparator, const bool Reversed)
{
	TArray<UUserDefinedStruct*> Array = StructArray;
	if ( !Reversed )
	{
		Array.Sort([Comparator](UUserDefinedStruct& A, UUserDefinedStruct& B)
		{
			bool Result = false;
			Comparator.Execute(&A, &B, Result);
			return Result;
		});
	}
	else
	{
		Array.Sort([Comparator](UUserDefinedStruct& A, UUserDefinedStruct& B)
		{
			bool Result = false;
			Comparator.Execute(&A, &B, Result);
			return !Result;
		});
	}
	return Array;
}


void UGP2BlueprintFunctionLibrary::SortStructArrayDirectly(UPARAM(ref) TArray<UUserDefinedStruct*>& StructArray, FDelegateCompareStructs Comparator, const bool Reversed)
{
	if ( !Reversed )
	{
		StructArray.Sort([Comparator](UUserDefinedStruct& A, UUserDefinedStruct& B)
		{
			bool Result = false;
			Comparator.Execute(&A, &B, Result);
			return Result;
		});
	}
	else
	{
		StructArray.Sort([Comparator](UUserDefinedStruct& A, UUserDefinedStruct& B)
		{
			bool Result = false;
			Comparator.Execute(&A, &B, Result);
			return !Result;
		});
	}
}


FVector2D UGP2BlueprintFunctionLibrary::GetSourceSize(UPaperSprite* sprite)
{
	FVector2D size(sprite->BakedRenderData[0].X * sprite->GetPixelsPerUnrealUnit(), sprite->BakedRenderData[0].Y * sprite->GetPixelsPerUnrealUnit());
	return size*2.0f;
}


UInfoManager* UGP2BlueprintFunctionLibrary::GetInfoManager()
{
	UInfoManager* InfoManager = nullptr;
	if ( !InfoManager || !( InfoManager->IsValidLowLevel() ) )
	{
		InfoManager = Cast<UInfoManager>( GEngine->GameSingleton );
	}

	if ( !InfoManager ) return nullptr;
	if ( !InfoManager->IsValidLowLevel() ) return nullptr;

	return InfoManager;
}


const FString &  UGP2BlueprintFunctionLibrary::GetCountryType()
{
	return g_Country;
}

const FString &  UGP2BlueprintFunctionLibrary::GetVersion()
{
	return g_Version;
}

int UGP2BlueprintFunctionLibrary::GetSRev()
{
	return g_SourceRevision;
}

int UGP2BlueprintFunctionLibrary::GetCRev()
{
	return g_ContentRevision;
}

const FString UGP2BlueprintFunctionLibrary::GetCurrentVersion()
{
	// g_BuildCount = 1;
	// g_QA = false;
	// return FString::Printf( TEXT( "ver.%s.%05d.%05d.%s" ) , *g_Version , g_SourceRevision , g_ContentRevision , *g_Country );

	if( g_QA )
		return FString::Printf( TEXT("ver.%s.%d.%d(QA)"), *g_Version, g_ContentRevision, g_BuildCount );
	else
		return FString::Printf( TEXT("ver.%s.%d.%d(_QA)"), *g_Version, g_ContentRevision, g_BuildCount );
}

int UGP2BlueprintFunctionLibrary::GetPlatformType()
{
	return g_PlatformType;
}

int UGP2BlueprintFunctionLibrary::GetAuthType()
{
	return g_AuthType;
}

bool UGP2BlueprintFunctionLibrary::IsDedicateServer()
{
#if defined( GP2_SERVER )
	return true;
#else 
	return false;
#endif 
}

bool UGP2BlueprintFunctionLibrary::IsQA()
{
	return g_QA;
}

bool UGP2BlueprintFunctionLibrary::IsFlexMatchTest()
{
	return g_flexmatch_test;
}

int UGP2BlueprintFunctionLibrary::GetGenderType()
{
	return g_Gender;
}

int UGP2BlueprintFunctionLibrary::GetClassType()
{
	return g_Class;
}

int UGP2BlueprintFunctionLibrary::GetPvpCharacterInfoId()
{
	return g_pvp_character_infoId;
}

bool UGP2BlueprintFunctionLibrary::IsSkipTutorial()
{
	return g_SkipTutorial;
}

bool UGP2BlueprintFunctionLibrary::IsSkipWeb()
{
	return g_skip_web;
		
}

bool UGP2BlueprintFunctionLibrary::IsGM_SelectCharacterTest()
{
	return g_gm_test_sc;	
}

bool UGP2BlueprintFunctionLibrary::IsGM_MatchRoomTest()
{
	return g_gm_test_mr;
}

bool UGP2BlueprintFunctionLibrary::IsInventoryTest()
{
	return g_inventory_test;
}



UTexture2D * UGP2BlueprintFunctionLibrary::LoadTexture2D( const FString& Path )
{
	UObject* OutTexture2D = StaticLoadObject( UTexture2D::StaticClass() , NULL , *Path );
	if ( OutTexture2D == nullptr )
		return nullptr;

	return Cast< UTexture2D >( OutTexture2D );
}