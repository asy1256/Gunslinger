// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/UserDefinedStruct.h"
#include "PaperSprite.h"
#include "Data/InfoManager.h"
#include "GP2BlueprintFunctionLibrary.generated.h"


/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FDelegateCompareObjects, UObject*, ObjectA, UObject*, ObjectB, bool&, Result);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FDelegateCompareStructs, UUserDefinedStruct*, StructA, UUserDefinedStruct*, StructB, bool&, Result);

UCLASS()
class GUNSLINGERSW_API UGP2BlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	/**
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintPure, Category = "T3|Array", Meta = (DisplayName = "Sort (String Array) (Copy)"))
	static TArray<FString> SortStringArray(const TArray<FString>& StringArray, const bool Reversed = false);

	/**
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintCallable, Category = "T3|Array", Meta = (DisplayName = "Sort (String Array)"))
	static void SortStringArrayDirectly(UPARAM(ref) TArray<FString>& StringArray, const bool Reversed = false);


	/**
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintPure, Category = "T3|Array", Meta = (DisplayName = "Sort (Integer Array) (Copy)"))
	static TArray<int32> SortIntegerArray(const TArray<int32>& IntegerArray, const bool Reversed = false);

	/**
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintCallable, Category = "T3|Array", Meta = (DisplayName = "Sort (Integer Array)"))
	static void SortIntegerArrayDirectly(UPARAM(ref) TArray<int32>& IntegerArray, const bool Reversed = false);


	/**
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintPure, Category = "T3|Array", Meta = (DisplayName = "Sort (Float Array) (Copy)"))
	static TArray<float> SortFloatArray(const TArray<float>& FloatArray, const bool Reversed = false);

	/**
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintCallable, Category = "T3|Array", Meta = (DisplayName = "Sort (Float Array)"))
	static void SortFloatArrayDirectly(UPARAM(ref) TArray<float>& FloatArray, const bool Reversed = false);


	/**
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintPure, Category = "T3|Array", Meta = (DisplayName = "Sort (Byte Array) (Copy)"))
	static TArray<uint8> SortByteArray(const TArray<uint8>& ByteArray, const bool Reversed = false);

	/**
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintCallable, Category = "T3|Array", Meta = (DisplayName = "Sort (Byte Array)"))
	static void SortByteArrayDirectly(UPARAM(ref) TArray<uint8>& ByteArray, const bool Reversed = false);


	/**
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintPure, Category = "T3|Array", Meta = (DisplayName = "Sort (DateTime Array) (Copy)"))
	static TArray<FDateTime> SortDateTimeArray(const TArray<FDateTime>& DateTimeArray, const bool Reversed = false);

	/**
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintCallable, Category = "T3|Array", Meta = (DisplayName = "Sort (DateTime Array)"))
	static void SortDateTimeArrayDirectly(UPARAM(ref) TArray<FDateTime>& DateTimeArray, const bool Reversed = false);


	/**
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintPure, Category = "T3|Array", Meta = (DisplayName = "Sort (Timespan Array) (Copy)"))
	static TArray<FTimespan> SortTimespanArray(const TArray<FTimespan>& TimespanArray, const bool Reversed = false);

	/**
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintCallable, Category = "T3|Array", Meta = (DisplayName = "Sort (Timespan Array)"))
	static void SortTimespanArrayDirectly(UPARAM(ref) TArray<FTimespan>& TimespanArray, const bool Reversed = false);

	/*
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintPure, Category = "T3|Array", Meta = (DisplayName = "Sort (Object Array) (Copy)"))
	static TArray<UObject*> SortObjectArray(const TArray<UObject*>& ObjectArray, FDelegateCompareObjects Comparator, const bool Reversed = false);

	UFUNCTION(BlueprintCallable, Category = "T3|Array", Meta = (DisplayName = "Sort (Object Array)"))
	static void SortObjectArrayDirectly(UPARAM(ref) TArray<UObject*>& ObjectArray, FDelegateCompareObjects Comparator, const bool Reversed);

	/*
	* Sorts a copy of the given array.
	*/
	UFUNCTION(BlueprintPure, Category = "T3|Array", Meta = (DisplayName = "Sort (Struct Array) (Copy)"))
	static TArray<UUserDefinedStruct*> SortStructArray(const TArray<UUserDefinedStruct*>& StructArray, FDelegateCompareStructs Comparator, const bool Reversed = false);

	UFUNCTION(BlueprintCallable, Category = "T3|Array", Meta = (DisplayName = "Sort (Struct Array)"))
	static void SortStructArrayDirectly(UPARAM(ref) TArray<UUserDefinedStruct*>& StructArray, FDelegateCompareStructs Comparator, const bool Reversed);


	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Source Size", Keywords = "Source Texture Sprite"), Category = Custom) //Here you can change the keywords, name and category
	static FVector2D GetSourceSize(UPaperSprite* sprite);


public:
	UFUNCTION( BlueprintPure , Category = "DataManager" , Meta = ( DisplayName = "GetDataManager" ) )
	static UInfoManager* GetInfoManager();



public:
	UFUNCTION( BlueprintPure , Category = "InGameSetting" )
	static const FString &  GetCountryType();

	UFUNCTION( BlueprintPure , Category = "InGameSetting" )
	static const FString &  GetVersion();

	UFUNCTION( BlueprintPure , Category = "InGameSetting" )
	static int GetSRev();

	UFUNCTION( BlueprintPure , Category = "InGameSetting" )
	static int GetCRev();

	UFUNCTION( BlueprintPure , Category = "InGameSetting" )
	static const FString GetCurrentVersion();

	UFUNCTION(BlueprintPure, Category = "InGameSetting", meta = (ShortTooltip = "31 : PC / 32 : PS4"))
	static int GetPlatformType();

	UFUNCTION(BlueprintPure, Category = "InGameSetting", meta = (ShortTooltip = "1 : Hanbit / 2 : Bridge"))
	static int GetAuthType();

	UFUNCTION( BlueprintPure , Category = "InGameSetting" )
	static bool IsDedicateServer();

	UFUNCTION( BlueprintPure , Category = "InGameSetting" )
	static bool IsQA();

	UFUNCTION(BlueprintPure, Category = "InGameSetting")
	static bool IsFlexMatchTest();


	UFUNCTION(BlueprintPure, Category = "InGameTestSettings", meta = (ShortTooltip = "1 : Male / 2 : Female"))
	static int GetGenderType();

	UFUNCTION(BlueprintPure, Category = "InGameTestSettings", meta = (ShortTooltip = "1 : Striker / 2 : ..."))
	static int GetClassType();

	UFUNCTION(BlueprintPure, Category = "InGameTestSettings", meta = (ShortTooltip = "101 : Tohru ..."))
	static int GetPvpCharacterInfoId();

	UFUNCTION( BlueprintPure , Category = "InGameTestSettings" )
	static bool IsSkipTutorial();

	UFUNCTION( BlueprintPure , Category = "InGameTestSettings" )
	static bool IsSkipWeb();

	UFUNCTION( BlueprintPure , Category = "InGameTestSettings" )
	static bool IsGM_SelectCharacterTest();

	UFUNCTION( BlueprintPure , Category = "InGameTestSettings" )
	static bool IsGM_MatchRoomTest();

	UFUNCTION(BlueprintPure, Category = "InGameTestSettings")
	static bool IsInventoryTest();


public:
	UFUNCTION( BlueprintPure , Category = "T3|Util" )
	static UTexture2D * LoadTexture2D( const FString& Path );

};
