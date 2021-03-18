#include "ShapeDetector.h"
#include "Components/ShapeComponent.h"

AShapeDetector::AShapeDetector()
{
	PrevShape = nullptr;
}

#if WITH_EDITOR
void AShapeDetector::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	auto ChangedProperty = PropertyChangedEvent.MemberProperty;
	if (ChangedProperty && ChangedProperty->GetFName() == GET_MEMBER_NAME_CHECKED(AShapeDetector, TriggerShape))
	{
		if (PrevShape != nullptr)
		{
			PrevShape->DestroyComponent();
		}
		PrevShape = TriggerShape;

		if (TriggerShape != nullptr)
		{
			TriggerShape->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}
#endif

void AShapeDetector::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerShape && HasAuthority())
	{
		TriggerShape->OnComponentBeginOverlap.AddDynamic(this, &AShapeDetector::Enter);
		TriggerShape->OnComponentEndOverlap.AddDynamic(this, &AShapeDetector::Exit);
	}
}

void AShapeDetector::Enter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OnEnter.IsBound() == true)
	{ OnEnter.Execute(OtherActor); }
}

void AShapeDetector::Exit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OnExit.IsBound() == true)
	{ OnExit.Execute(OtherActor); }
}

void AShapeDetector::CollisionToggle()
{
	if (CollisionFlag)
	{ TriggerShape->SetCollisionEnabled(ECollisionEnabled::NoCollision); }
	else
	{ TriggerShape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); }

	CollisionFlag = !CollisionFlag;
}