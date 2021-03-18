#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimSequence.h"
#include "Animation/BlendSpace.h"
#include "Animation/AimOffsetBlendSpace.h"
#include "Animation/AnimMontage.h"
#include "GP2EnumTypes.h"
#include "Engine/DataTable.h"
#include "UIDataType.generated.h"


/// Decrypted File

USTRUCT( BlueprintType )
struct FGWCharacterName : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	FName CharacterName; ///
};


USTRUCT( BlueprintType )
struct FGWCharacterSubTitle : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	class UDataTable* SubTitleInfoTable;   ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	class UDataTable* SubTitleStringTable; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	class UDataTable* SubTitleSoundTable;  ///
};

USTRUCT( BlueprintType )
struct FGWPlayerSubTitle : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	FName MapName;           ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	FName TriggerName;       ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	FName SubTitleName;      ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	FName SoundName;         ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	float NextSubTitleDelay; ///
};

USTRUCT( BlueprintType )
struct FGWSubTitle : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	FText ko_KR; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	FText en_US; ///

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	FText ja_JP; ///
};

USTRUCT( BlueprintType )
struct FGWSubTitleSound : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "" )
	class USoundCue* SoundResource; ///
};

USTRUCT( BlueprintType )
struct FGWPlayRecordData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "ID that used to get Character Information"))
	int InfoID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MatchCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WinningCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalKill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalHeal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumHeal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "time base size == minute"))
	int PlayTime;
};