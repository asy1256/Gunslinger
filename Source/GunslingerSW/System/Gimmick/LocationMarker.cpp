#include "LocationMarker.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/PlayerController.h"

ALocationMarker::ALocationMarker()
	: VisibleFlag(false), Plcon(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	Widget = CreateDefaultSubobject<UWidgetComponent>(FName("WidgetComp"));
	if (RootComponent)
	{ Widget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); }
}

void ALocationMarker::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{ PrimaryActorTick.bCanEverTick = false; }
	else
	{
		Widget->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
		Plcon = GetWorld()->GetFirstPlayerController();
	}
}

void ALocationMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalDistance();
}

void ALocationMarker::ToggleVisible_Implementation()
{
	if (Widget->GetUserWidgetObject() == nullptr /*|| HasAuthority()*/)
	{ return; }

	if (VisibleFlag)
	{ Widget->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden); }
	else
	{ Widget->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible); }

	VisibleFlag = !VisibleFlag;
}

void ALocationMarker::CalDistance()
{
	if (Plcon)
	{
		AActor* plch = Plcon->GetPawn();
		if (plch)
		{ Distance = GetDistanceTo(plch); }
	}
}