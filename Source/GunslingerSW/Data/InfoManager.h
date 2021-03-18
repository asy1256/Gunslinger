// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP2DataStructTypes.h"
#include "InfoManager.generated.h"


// typedef TMap< int , class UDataTable* > TDataTableMap;


class UDataTable;


UCLASS(Blueprintable, BlueprintType)
class GUNSLINGERSW_API UInfoManager : public UObject
{
	GENERATED_BODY()

public:
	UInfoManager()
	{
	}



public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Info Manager" )
	TMap< EGWInfoType , class UDataTable* > DataTableMap; /// 




public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
		class UDataTable* PlayerInfoTable;             /// FGWPlayerInfo

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
		class UDataTable* PVPPlayerInfoTable;          /// pvp character db


	/// 
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* ConstInfoTable;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" ) 
	class UDataTable* CharacterExpInfoTable;       /// FGWCharacterExpInfo

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* CharacterInfoTable;          /// FGWCharacterInfo

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* ProxyCharacterInfoTable;     /// FGWProxyCharacter

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* ProxyCameraSettingTable;     /// FGWProxyCameraSetting - inven...proxycamerasettings

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* CharacterCameraInfoTable;    /// FGWCharacterCameraInfo

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* AnimationListInfoTable;      /// FGWAnimationListInfo

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* NpcInfoTable;                /// FGWNpcInfo









	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* LobbyWidgetInfoTable;        ///
		

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* FacialDataTable;             ///

	


	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
		class UDataTable* StageInfoTable;




	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* CostumeInfoTable;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* CostumeTable;                ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* PVPPresetCharacterInfoTable; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* PresetTable;                 ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* VirtualCharacterTable;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* CharacterPartsTable;         ///





	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* CharacterExInfoTable;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* PCInfoTable;                 ///




	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* ChatColorTable;              ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* TeamInfoTable;               ///




	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* VoiceInfoTable;              ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* VoiceLipSyncTableTable;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* LipSyncVisemesTable;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* CommonInfoTable;             ///

            ///




	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* QuestInfoTable;              ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* SequenceInfoTable;           ///





	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* KeyboardCorlorArrayTable;    ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* KeyIconTable;                ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* KeyMappingInfoTable;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* ShortKeyInfoTable;           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* InputKeyInfoTable;           ///





	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* GP2ItemInfoTable;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* QuestItemInfoTable;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* DropItemInfoTable;           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* InstantItemInfoTable;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* ItemBoxInfoTable;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* ItemOptionInfoTable;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* ItemOptionGroupInfoTable;    ///



	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* RewardDataTable;             ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* BuildingDestroyDataTable;    ///



	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* Monster_EQS_InfoTable;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* MonsterSkillInfoTable;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* MonsterStateInfoTable;       ///

	

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* ProjectileInfoTable;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* SkillInfoTable;              ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* SkillActorInfoTable;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* SkillEffectInfoTable;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* StatusEffectInfoTable;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* UltraSkillInfoTable;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* StatusEffectsInfoTable;      ///

   
												   
												   ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* StreamLevelInfoTable;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* LoadLevelTable;              ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* StageLoadingInfoTable;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* WorldInfoTable;              ///







	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* TutorialPageInfoTable;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* TutorialInfoTable;           ///


	




	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* WeaponInfoTable;             ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* AttachWeaponInfoTable;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* WeaponSkillInfoTable;        ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* DefaultWeaponTable;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* WeaponLinkExTable;           ///



	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
		class UDataTable* CharacterNameTable;          ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
		class UDataTable* CharacterSubTitleTable;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
		class UDataTable* PlayerSubTitleTable;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
		class UDataTable* SubTitleTable;               ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
		class UDataTable* SubTitleSoundTable;          ///



	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* BadwordInfoTable;            ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* StringInfoTable;             ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
	class UDataTable* ServerErrorCodeTable;        ///


	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Gp2 Info Tables" )
		class UDataTable* ResolutionDataTable;         ///



public:


	/*
	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetEXPInfoTable( FString& Key , FGWCharacterExpInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetStatInfoTable( FString& Key ,  FStatInfoTable& OutInfo );               ///

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetCharacterInfoTable( FString& Key , FGWCharacterInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetProxyCharacterTable( FString& Key , FGWProxyCharacter& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetProxyCameraSettingTable( FString& Key , FGWProxyCameraSetting& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetLobbyWidgetInfoTable( FString& Key , FGWLobbyWidgetInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetCameraSettingTable( FString& Key , FGWCameraSetting& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetCameraSettingsTable( FString& Key , FGWCameraSettings& OutInfo );

	*/
	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetAnimationListInfo( const FString& Key , FGWAnimationListInfo& OutInfo );

	/*
	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetFacialDataTable( FString& Key , FGWFacialData& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetNPCInfoTable( FString& Key , FGWNPCInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetCostumeInfoTable( FString& Key , FGWCostumeInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetCostumeTable( FString& Key , FGWCostume& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetPVPPresetCharacterInfoTable( FString& Key , FGWPVPPresetCharacterInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetPresetTable( FString& Key , FGWPreset& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetVirtualCharacterTable( FString& Key , FGWVirtualCharacter& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetCharacterPartsTable( FString& Key , FGWCharacterParts& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetCharacterExInfoTable( FString& Key , FGWCharacterExInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetPCInfoTable( FString& Key , FGWPCInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetChatColorTable( FString& Key , FGWChatColor& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetTeamInfoTable( FString& Key , FGWTeamInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetVoiceInfoTable( FString& Key , FGWVoiceInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetVoiceLipSyncTableTable( FString& Key , FGWVoiceLipSyncTable& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetLipSyncVisemesTable( FString& Key , FGWLipSyncVisemes& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetCommonInfoTable( FString& Key , FGWCommonInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetConstTable( FString& Key , FGWConst& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetQuestInfoTable( FString& Key , FGWQuestInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetSequenceInfoTable( FString& Key , FGWSequenceInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetActorStatTypeInfoTable( FString& Key , FGWActorStatTypeInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetKeyboardCorlorArrayTable( FString& Key , FGWKeyboardCorlorArray& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetKeyIconTable( FString& Key , FGWKeyIcon& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetKeyMappingInfoTable( FString& Key , FGWKeyMappingInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetShortKeyInfoTable( FString& Key , FGWShortKeyInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetInputKeyInfoTable( FString& Key , FGWInputKeyInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetGP2ItemInfoTable( FString& Key , FGWGP2ItemInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetQuestItemInfoTable( FString& Key , FGWQuestItemInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetDropItemInfoTable( FString& Key , FGWDropItemInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetInstantItemInfoTable( FString& Key , FGWInstantItemInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetItemBoxInfoTable( FString& Key , FGWItemBoxInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetItemOptionInfoTable( FString& Key , FGWItemOptionInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetItemOptionGroupInfoTable( FString& Key , FGWItemOptionGroupInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetRewardDataTable( FString& Key , FGWRewardData& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetBuildingDestroyDataTable( FString& Key , FGWBuildingDestroyData& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetMonster_EQS_InfoTable( FString& Key , FGWMonster_EQS_Info& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetMonsterSkillInfoTable( FString& Key , FGWMonsterSkillInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetMonsterStateInfoTable( FString& Key , FGWMonsterStateInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetPlayerInfoTable( FString& Key , FGWPlayerInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetPVPPlayerInfoTable( FString& Key , FGWPVPPlayerInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetProjectileInfoTable( FString& Key , FGWProjectileInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetSkillInfoTable( FString& Key , FGWSt& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetSkillActorInfoTable( FString& Key , FGWSkillActorInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetSkillEffectInfoTable( FString& Key , FGWSkillEffectInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetStatusEffectInfoTable( FString& Key , FGWStatusEffectInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetUltraSkillInfoTable( FString& Key , FGWUltraSkillInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetStatusEffectsInfoTable( FString& Key , FGWStatusEffectsInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetStageInfoTable( FString& Key , FGWStageInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetStreamLevelInfoTable( FString& Key , FGWStreamLevelInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetLoadLevelTable( FString& Key , FGWLoadLevel& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetStageLoadingInfoTable( FString& Key , FGWStageLoadingInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetWorldInfoTable( FString& Key , FGWWorldInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetTutorialPageInfoTable( FString& Key , FGWTutorialPageInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetTutorialInfoTable( FString& Key , FGWTutorialInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetMapInfoTable( FString& Key , FGWMapInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetCharacterNameTable( FString& Key , FGWCharacterName& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetCharacterSubTitleTable( FString& Key , FGWCharacterSubTitle& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetPlayerSubTitleTable( FString& Key , FGWPlayerSubTitle& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetSubTitleTable( FString& Key , FGWSubTitle& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetSubTitleSoundTable( FString& Key , FGWSubTitleSound& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetResolutionDataTable( FString& Key , FGWResolutionData& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetWeaponInfoTable( FString& Key , FGWWeaponInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetAttachWeaponInfoTable( FString& Key , FGWAttachWeaponInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetWeaponSkillInfoTable( FString& Key , FGWWeaponSkillInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetDefaultWeaponTable( FString& Key , FGWDefaultWeapon& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetWeaponLinkExTable( FString& Key , FGWWeaponLinkEx& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetBadwordInfoTable( FString& Key , FGWBadwordInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetStringInfoTable( FString& Key , FGWStringInfo& OutInfo );

	UFUNCTION( BlueprintPure , Category = "Gp2 Info Tables" )
	bool GetServerErrorCodeTable( FString& Key , FGWServerErrorCode& OutInfo );
*/

	//FEXPInfo
	//FStatInfo
	//FCharacterInfo
	//FProxyCharacter
	//FProxyCameraSetting
	//FLobbyWidgetInfo
	//FCameraSetting
	//FCameraSettings
	//FAnimationList
	//FFacialData
	//FNPCInfo
	//FCostumeInfo
	//FCostume
	//FPVPPresetCharacterInfo
	//FPreset
	//FVirtualCharacter
	//FCharacterParts
	//FCharacterExInfo
	//FPCInfo
	//FChatColor
	//FSequenceInfo
	//FActorStatTypeInfo
	//FKeyboardCorlorArray
	//FKeyIcon
	//FKeyMappingInfo
	//FShortKeyInfo
	//FInputKeyInfo
	//FItemInfo
	//FQuestItemInfo
	//FDropItemInfo
	//FInstantItemInfo
	//FItemBoxInfo
	//FItemOptionInfo
	//FItemOptionGroupInfo
	//FRewardData
	//FBuildingDestroyData
	//FMonster_EQS_Info
	//FMonsterSkillInfo
	//FMonsterStateInfo
	//FPlayerInfo
	//FPVPPlayerInfo
	//FProjectileInfo
	//FSkillInfo
	//FSkillActorInfo
	//FSkillEffectInfo
	//FStatusEffectInfo
	//FUltraSkillInfo
	//FStatusEffectsInfo
	//FStageInfo
	//FStreamLevelInfo
	//FLoadLevel
	//FStageLoadingInfo
	//FWorldInfo
	//FTutorialPageInfo
	//FTutorialInfo
	//FMapInfo
	//FCharacterName
	//FCharacterSubTitle
	//FPlayerSubTitle
	//FSubTitle
	//FSubTitleSound
	//FWeaponInfo
	//FAttachWeaponInfo
	//FWeaponSkillInfo
	//FDefaultWeapon
	//FWeaponLinkEx
	//FBadwordInfo
	//FStringInfo
};

                                                                            
   
                                                                            