// Fill out your copyright notice in the Description page of Project Settings.

#include "MessagePopup.h"
#include "GunslingerSW.h"

#include <TextBlock.h>

/// ������
UMessagePopup::UMessagePopup( const FObjectInitializer& ObjectInitializer )
:
Super( ObjectInitializer )
{
}

/// �Ҹ���
void UMessagePopup::BeginDestroy()
{
	Super::BeginDestroy();
}

void UMessagePopup::SetResultCode( int InResultCodeId )
{
}