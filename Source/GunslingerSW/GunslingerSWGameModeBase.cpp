// Fill out your copyright notice in the Description page of Project Settings.

#include "GunslingerSWGameModeBase.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
//
//AGunslingerSWGameModeBase::AGunslingerSWGameModeBase()
//{
//	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonBP/Blueprints/myThirdPerson"));
//
//	//if (PlayerPawnBPClass.Class != NULL)
//	//{
//	//	DefaultPawnClass = PlayerPawnBPClass.Class;
//	//}
//}
//
//void AGunslingerSWGameModeBase::PostLogin(APlayerController* NewPlayer)
//{
//	FTransform startPos;
//
//	for (TActorIterator<APlayerStart> ActorItr(GetWorld()); ActorItr; ++ActorItr)
//	{
//		startPos = ActorItr->GetTransform();
//		break;
//	}
//
//	UE_LOG(LogTemp, Log, TEXT("### AGunslingerSWGameModeBase::PostLogin ###"));
//
//	//static ConstructorHelpers::FObjectFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter"));
//
//	//if (PlayerPawnBPClass.Object != NULL)
//	//{
//	//	UE_LOG(LogTemp, Log, TEXT("### ThirdPersonSpawn ###"));
//
//	//	//auto myChar = (GetWorld()->SpawnActor(PlayerPawnBPClass.Object));
//	//	//PlayerPawnBPClass.Object
//	//	//myChar->SetActorTransform(startPos);
//	//	PlayerPawnBPClass.Object->SetActorTransform(startPos);
//	//	NewPlayer->Possess(PlayerPawnBPClass.Object);
//	//	
//	//	//DefaultPawnClass = PlayerPawnBPClass.Class;
//	//}
//
//	AGameModeBase::PostLogin(NewPlayer);
//}