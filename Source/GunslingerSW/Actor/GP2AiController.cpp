// Fill out your copyright notice in the Description page of Project Settings.

#include "GP2AiController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Engine/DataTable.h"
#include "Actor/CharacterMonster.h"


AGP2AiController::AGP2AiController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	//GetPercptionComponent()->OnPerceptionUpdated.AddDynamic(this, AGP2AiController::OnPawnDetected);
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("sight config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	//GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, AGP2AiController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AGP2AiController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//퍼셉션에서 시각정보가 있으면 가져온다 / By.안성용
	if (PerceptionComponent != nullptr)
	{
		for (auto iter = PerceptionComponent->GetSensesConfigIterator(); iter; iter++)
		{
			auto config = Cast<UAISenseConfig_Sight>(*iter);
			if (config != nullptr)
				SightConfig = config;
		}
	}
}

void AGP2AiController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay - OK"));
}

void AGP2AiController::OnPossess(APawn * pPawn)
{
	Super::OnPossess(pPawn);
	UE_LOG(LogTemp, Warning, TEXT("OnPossess - OK"));
}

void AGP2AiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

FRotator AGP2AiController::GetControlRotation() const
{

	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AGP2AiController::SetNewSightData()
{
	ACharacterMonster* MonsterBP = Cast<ACharacterMonster>(GetPawn());
	if (IsValid(MonsterBP))
	{
		//SightConfig->SightRadius = MonsterBP->AiSightRadius;
		//SightConfig->LoseSightRadius = MonsterBP->AiLoseSightRadius;
		//SightConfig->PeripheralVisionAngleDegrees = MonsterBP->AiSightHalfAnge;
		//SightConfig->SetMaxAge(MonsterBP->AiSightAge);

		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SetNewSightData - Data Refresh Error"));
	}
}

void AGP2AiController::SetSightData(const FGWSightData& data)
{
	if (SightConfig == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Don't have SightConfig")); return;

	SightConfig->SightRadius = data.SightRadius;
	SightConfig->LoseSightRadius = data.LoseRadius;
	SightConfig->PeripheralVisionAngleDegrees = data.SightAngle;
	SightConfig->SetMaxAge(data.MaxAge);
}

void AGP2AiController::OnPawnDetected(TArray<AActor*> DetectedPawns)
{
}
