// Fill out your copyright notice in the Description page of Project Settings.

#include "MessagePopup.h"
#include "GunslingerSW.h"

#include <TextBlock.h>

/// 持失切
UMessagePopup::UMessagePopup( const FObjectInitializer& ObjectInitializer )
:
Super( ObjectInitializer )
{
}

/// 社瑚切
void UMessagePopup::BeginDestroy()
{
	Super::BeginDestroy();
}

void UMessagePopup::SetResultCode( int InResultCodeId )
{
}