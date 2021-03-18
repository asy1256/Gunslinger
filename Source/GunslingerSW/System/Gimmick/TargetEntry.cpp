// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetEntry.h"
#include "Components/BoxComponent.h"

void ATargetEntry::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ATargetEntry::Enter);
}

void ATargetEntry::Enter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Triggered == false)
	{
		if (TargetClass.Get() == OtherActor->GetClass())
		{
			UE_LOG(LogTemp, Warning, TEXT("Overlap actor class %s is same with target class %s"), *(OtherActor->GetName()), *(TargetClass.Get()->GetName()));
			if (Disposable == true)
			{ Triggered = true; }

			OnTriggered.Broadcast();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Overlap actor class %s is dosen't same with target class %s"), *(OtherActor->GetName()), *(TargetClass.Get()->GetName()));
		}
	}

}