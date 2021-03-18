#include "MonSpawnPoint.h"

#if WITH_EDITOR
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Actor/CharacterMonster.h"
#endif

// Sets default values
AMonSpawnPoint::AMonSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
#if WITH_EDITOR
	USceneComponent* root = CreateOptionalDefaultSubobject<USceneComponent>("Root");
	RootComponent = root;

	PreviewMesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("MonsterMesh"));
	if (PreviewMesh)
	{
		PreviewMesh->AlwaysLoadOnClient = true;
		PreviewMesh->AlwaysLoadOnServer = true;
		PreviewMesh->bOwnerNoSee = false;
		PreviewMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
		PreviewMesh->SetHiddenInGame(true);
		PreviewMesh->bAffectDynamicIndirectLighting = true;
		PreviewMesh->SetupAttachment(RootComponent);
		PreviewMesh->SetGenerateOverlapEvents(false);
		PreviewMesh->SetCanEverAffectNavigation(false);
	}
#endif
}

const bool AMonSpawnPoint::GetSpawnName(const int32& wavecount IN, const FName*& name OUT)
{
	name = nullptr;
	if (wavecount >= SpawnList.Num())
	{ return false; }

	if (SpawnList[wavecount] < 0)
	{ return false; }

	name = &RowNames[SpawnList[wavecount]];
	return true;
}

#if WITH_EDITOR
void AMonSpawnPoint::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	auto PropertyThatChanged = PropertyChangedEvent.MemberProperty;
	if (PropertyThatChanged && SpawnTable)
	{
		// NOTE : 에디터가 죽어버려서 임시제외
		//if (PropertyThatChanged->GetFName() == GET_MEMBER_NAME_CHECKED(AMonSpawnPoint, RowNames))
		//{
		//	if (RowNames.Num() <= 0)
		//	{ PreviewIndex = 0;	}
		//	else
		//	{ SetPreviewMesh(); }
		//
		//	return;
		//}

		if (PropertyThatChanged->GetFName() == GET_MEMBER_NAME_CHECKED(AMonSpawnPoint, PreviewIndex))
		{
			SetPreviewMesh();
		}
	}
}

void AMonSpawnPoint::SetPreviewMesh()
{
	USkeletalMesh* mesh = nullptr;
	if (PreviewIndex < RowNames.Num())
	{
		auto rowdata = SpawnTable->FindRow<FGWMonSpawnData>(RowNames[PreviewIndex], "Find Monster Mesh");
		if (rowdata != nullptr)
		{
			auto meshcomp = rowdata->Class.GetDefaultObject()->GetMesh();
			mesh = meshcomp->SkeletalMesh;
			PreviewMesh->SetRelativeTransform(meshcomp->GetRelativeTransform());
		}
	}

	PreviewMesh->SetSkeletalMesh(mesh);
}
#endif