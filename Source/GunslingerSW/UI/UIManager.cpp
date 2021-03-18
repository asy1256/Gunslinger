// Fill out your copyright notice in the Description page of Project Settings.

#include "UIManager.h"
#include "GunslingerSW.h"
#include <SWidget.h>


UUIManager::UUIManager()
	:
	bInitialized( false )
{
	ShowUiList.clear();
}

void UUIManager::BeginDestroy()
{
	Super::BeginDestroy();
}

void UUIManager::ShowUI( UUserWidget* InUI , int32 InZOrder )
{
	if ( !InUI )
		return;


	if ( !InUI->GetParent() )
		ShowUiList.insert( InUI );

	InUI->AddToViewport();

}

/// 모든 UI를 화면에 표시한다.
void UUIManager::ShowAll()
{
	for ( UUserWidget* widget : ShowUiList )
	{
		widget->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
	}
}

/// 모든 UI를 숨긴다.
void UUIManager::HideAllUI()
{
	for ( UUserWidget* widget : ShowUiList )
	{
		widget->SetVisibility( ESlateVisibility::Collapsed );
	}
}

UUserWidget* UUIManager::CreateUI( TSubclassOf< UUserWidget > InUserWidgetClass )
{
	if ( !bInitialized )
		return nullptr;

	UBlueprint* widget_blueprint = Cast< UBlueprint >( InUserWidgetClass->ClassGeneratedBy );
	if ( !widget_blueprint )
		return nullptr;

	UClass* key_class = Cast< UClass >( widget_blueprint->ParentClass );
	if ( !key_class )
		return nullptr;

	/// 중복
	/*
	FUiMap::iterator it = ManagedList.find( key_class );
	if ( it != ManagedList.end() && !it->second.empty() )
	{
		UUserWidget* ui = *it->second.begin();
		if ( ui && ui->IsValidLowLevel() )
		{
			ui->AddToRoot();
			return ui;
		}
		it->second.erase( ui );
	}
	*/
	
	UUserWidget* ui = CreateWidget< UUserWidget >( GetGameInstPtr() , InUserWidgetClass );
	if ( ui )
	{
		/// 참조할 수 없는 외부기호 ㅡㅡ;
		// TSharedRef< SWidget > slate_widget = ui->TakeWidget();
		// slate_widget->SlatePrepass();
		ManagedList[ key_class ].insert( ui );

		return ui;
	}
	

	return nullptr;
}

UUserWidget* UUIManager::ShowUI( TSubclassOf< UUserWidget > InUserWidgetClass )
{
	UUserWidget* UI = CreateUI( InUserWidgetClass );
	if ( !UI ) return nullptr;

	ShowUI( UI );

	return UI;
}

void UUIManager::CloseUI( UUserWidget* InUI )
{
	if ( !InUI || !InUI->IsValidLowLevel() )
		return;

	FUiSet::iterator it = ShowUiList.find( InUI );
	if ( it != ShowUiList.end() )
		ShowUiList.erase( it );

	InUI->RemoveFromViewport();
}

void UUIManager::RemoveUI( UUserWidget* InUI )
{
	if ( !InUI )
		return;

	if ( InUI->IsValidLowLevel() )
	{
		InUI->RemoveFromRoot();
		InUI->RemoveFromParent();
	}	
}


