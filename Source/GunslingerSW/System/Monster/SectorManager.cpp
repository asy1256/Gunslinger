#include "SectorManager.h"
#include "TimerManager.h"
#include "./GameMode/GP2GMBase.h"
#include "./MonsterPool.h"
#include "./MonSpawnPoint.h"
#include "./Actor/CharacterMonster.h"
#include "./GameState/GWGameState.h"

ASectorManager::ASectorManager()
	: MonCount(0), TotalWave(0), CurrentWave(0), WaveDelay(0.f), LoopEnable(false)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASectorManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	int32 curcount = 0;
	for (auto spawnpoint : SpawnPoints)
	{
		curcount = spawnpoint->GetWaveCount();
		if (curcount > TotalWave)
		{
			TotalWave = curcount;
		}
	}
}

void ASectorManager::StartSpawning()
{
	if (WaveDelay != 0)
	{
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASectorManager::NextWaveCheck, WaveDelay, true);
	}
	else
	{
		SpawnMonster();
	}
}

void ASectorManager::NextWaveCheck()
{
	if (CurrentWave >= TotalWave)
	{
		if (LoopEnable == false)
		{
			SpawnComplete();
			return;
		}

		CurrentWave = 0;
	}

	SpawnMonster();
}

void ASectorManager::SpawnMonster()
{
	auto gm = GetWorld()->GetAuthGameMode();
	AGP2GMBase* GWgm = Cast<AGP2GMBase>(gm);
	if (GWgm == nullptr)
	{
		// TODO : Write some log that object doesn't exist
		return;
	}

	AMonsterPool* const pool = GWgm->GetMonsterPool();
	if (pool == nullptr)
	{
		// TODO : Write some log that object doesn't exist
		return;
	}

	const FName* rowname = nullptr;
	bool result = false;
	ACharacterMonster* monref = nullptr;
	bool reuse = false;
	for (auto spawnpoint : SpawnPoints)
	{
		result = spawnpoint->GetSpawnName(CurrentWave, rowname);

		if (result == true)
		{
			result = pool->SpawnMonster(*rowname, spawnpoint->GetActorTransform(), monref, reuse);
			if (result == true)
			{
				monref->GetDeactivateDelegate().AddUObject(this, &ASectorManager::DecreaseMonsterCount);
				MonCount++;
			}
		}
	}

	CurrentWave++;
}

void ASectorManager::DecreaseMonsterCount(ACharacterMonster* deactivatemon)
{
	// NOTE : 델리게이트에 바인딩된 함수를 왜 여기서 지우는지 다시 생각해봐야 할거 같습니다.
	deactivatemon->GetDeactivateDelegate().RemoveAll(this);
	MonCount--;
	// GameState로 변경된 몬스터 수 전달
	auto gs = GetWorld()->GetGameState();
	if (gs != nullptr)
	{
		auto gwgs = Cast<AGWGameState>(gs);
		gwgs->SetMonsterCount(MonCount);
	}
	UE_LOG(LogTemp, Warning, TEXT("Left monster count : %d"), MonCount);
	if (MonCount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Wave Compelte"));
		NextWaveCheck();
	}
}

void ASectorManager::SpawnComplete()
{
	if (WaveDelay != 0)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}

	OnWaveComplete.Broadcast();
	OnWaveComplete.Clear();
}