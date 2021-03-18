// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../Data/CharacterDataType.h"
#include "GP2PCInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGP2PCInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GUNSLINGERSW_API IGP2PCInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|Logitech" )
	void Logitech_Light( const FString& Name ); /// 

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|Logitech" )
	void Logitech_AniPlay( const FString& Name ); /// 

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|Logitech" )
	void Logitech_Shutdown(); ///


	//-------------------------------------------------------------------------
	//	캐릭터 선택창
	//-------------------------------------------------------------------------
		
	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|SelectCharacter" )
	void SetCharacterSlotInfo( const struct FGWCharacterSlot& SlotInfo );

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|SelectCharacter" )
	void SetSelectCharacter( bool Force, int SlotIndex );

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|SelectCharacter" )
	void SetCharacterSlotAction( int SlotIndex );

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|SelectCharacter" )
	void SetChangePreset( int InfoId , int index );

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|SelectCharacter" )
	void SetChangeCostume( int InfoId );
	
	/*
	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|SelectCharacter" )
	void SetChangeCharacterParts( EParts Parts , int InfoId );

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|SelectCharacter" )
	void SetChangeCharacter( int InfoId );

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|SelectCharacter" )
	void SetCreateCharacter( int CharacterInfoId, FString Name, int HairInfoId, int FaceInoId, int BodyInfoId );

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|SelectCharacter" )
	void UpdateNicknameState( bool Success );

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "GP2PlayerController|SelectCharacter" )
	void SetCheckNickname( FString Name );
	*/




};
