#include "MonsterPool.h"
#include "Engine/DataTable.h"
#include "./Actor/CharacterMonster.h"
#include "./GameMode/GP2GMBase.h"
#include "./Controller/MonCtrlBase.h"

AMonsterPool::AMonsterPool()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMonsterPool::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto gm = GetWorld()->GetAuthGameMode();
	AGP2GMBase* Gwgm = Cast<AGP2GMBase>(gm);

	if (Gwgm != nullptr)
	{
		Gwgm->SetMonsterPool(this);
	}
}

bool AMonsterPool::SpawnMonster(const FName tablename, const FTransform transform, ACharacterMonster*& monster, bool& reuse)
{
	if (HasAuthority() == false)
	{
		return false;
	}

	FGWMonPoolData& pool = PoolMap.FindOrAdd(tablename);

	if (pool.MonPool.Num() == 0)
	{
		if (MonsterTable == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Spanwdata table is missing"));
			return false;
		}

		FGWMonSpawnData* data = MonsterTable->FindRow<FGWMonSpawnData>(tablename, "Find MonsterSpawnData");
		if (data == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Named row is not exists"));
			return false;
		}

		pool.SpawnData = *data;
	}

	ACharacterMonster* mon = FindRestingMonster(pool);
	if (mon == nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		mon = GetWorld()->SpawnActor<ACharacterMonster>(pool.SpawnData.Class, transform, param);
		pool.MonPool.Add(mon);
		mon->SetData(pool.SpawnData.MonData);

		mon->SpawnDefaultController();
		AMonCtrlBase* aicon = Cast<AMonCtrlBase>(mon->Controller);
		if (aicon != nullptr)
		{
			aicon->SetSightData(pool.SpawnData.SightConfig);
			aicon->BTAsset = pool.SpawnData.BtAsset;
		}
		else
		{ UE_LOG(LogTemp, Warning, TEXT("Controller fail to cast 'AMonCtrlBase'")); }
		reuse = false;
	}
	else
	{
		mon->ReDeployMTC(transform);
		reuse = true;
	}
	monster = mon;
	mon->Activate();

	return true;
}

ACharacterMonster* AMonsterPool::FindRestingMonster(FGWMonPoolData& pooldata)
{
	ACharacterMonster* restingmon = nullptr;

	for (ACharacterMonster* mon : pooldata.MonPool)
	{
		if (mon->IsAwake() == false)
		{
			restingmon = mon;
			break;
		}
	}

	return restingmon;
}