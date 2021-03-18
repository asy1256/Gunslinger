// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/Gimmick/DetectorBase.h"
#include "ShapeDetector.generated.h"

class UShapeComponent;

UCLASS()
class GUNSLINGERSW_API AShapeDetector : public ADetectorBase
{
	GENERATED_BODY()
	
public:
	AShapeDetector();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	void CollisionToggle();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void Enter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void Exit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	UShapeComponent*								TriggerShape;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	UShapeComponent*								PrevShape;
#endif
};
