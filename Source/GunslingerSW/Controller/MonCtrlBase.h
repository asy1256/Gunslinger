#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "./Data/MonsterDataType.h"
#include "Perception/AIPerceptionTypes.h"
#include "MonCtrlBase.generated.h"

class UAISenseConfig_Sight;
class UBehaviorTree;
class ACharacterPC;

/**
 * 
 */
UCLASS()
class GUNSLINGERSW_API AMonCtrlBase : public AAIController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void Activate();

	UFUNCTION(BlueprintCallable)
		void Deactivate();

	void SetSightData(const FGWSightData& data);

protected:
	UFUNCTION()
		virtual void PerceptionTargetUpdated(AActor* actor, FAIStimulus stimulus);

	UFUNCTION(BlueprintNativeEvent)
		void ActivateProcess();
	virtual void ActivateProcess_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void DeactivateProcess();
	virtual void DeactivateProcess_Implementation();

private:
	void ActivatePerceptionSystem();
	void AddSightConfig();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	UAISenseConfig_Sight*									SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBehaviorTree*											BTAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ACharacterPC*>									EnemyList;
};