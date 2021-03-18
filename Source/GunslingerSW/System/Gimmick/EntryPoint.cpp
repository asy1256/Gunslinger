// Fill out your copyright notice in the Description page of Project Settings.

#include "EntryPoint.h"
#include "Components/BoxComponent.h"

// Sets default values
AEntryPoint::AEntryPoint()
	: Disposable(false) , Triggered(false)
{
	PrimaryActorTick.bCanEverTick = false;

	auto root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = root;
	Box = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	Box->AttachToComponent(root, FAttachmentTransformRules::KeepRelativeTransform);
}
