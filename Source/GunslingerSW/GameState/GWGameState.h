#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GWGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeMonsterCount, int32, Count);

UCLASS()
class GUNSLINGERSW_API AGWGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetMonsterCount(const int count);

private:
	UFUNCTION(NetMulticast, Reliable)
	void MTC_SetMonsterCount(const int count);
	void MTC_SetMonsterCount_Implementation(const int count);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32					MonsterCount;

	UPROPERTY(BlueprintAssignable)
	FChangeMonsterCount		OnChangeMonsterCount;
};