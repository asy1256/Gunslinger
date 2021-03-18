#include "DetectorBase.h"

ADetectorBase::ADetectorBase()
{
	PrimaryActorTick.bCanEverTick = true;
	auto root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = root;
	CollisionFlag = false;
}