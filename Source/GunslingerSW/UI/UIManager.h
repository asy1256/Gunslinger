// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "UserWidget.h"

#include <set>
#include <list>
#include <map>
#include "GP2SingletonLibrary.h"

#include "UIManager.generated.h"

/**
*
*/
UCLASS()
class GUNSLINGERSW_API UUIManager
	:
	public UObject
{
	GENERATED_BODY()

private:
	typedef std::set< UUserWidget* > FUiSet;

	typedef std::map< UClass* , FUiSet > FUiMap;


private:
	bool bInitialized; /// �ʱ�ȭ�� ����

	FUiSet ShowUiList;		/// ����Ʈ�� �߰��� UI ���

	FUiMap ManagedList;		/// �������� UI ���( �ߺ����� ����ϴ� UI-Template ó�� )


public:
	UUIManager();

	/// 
	virtual void BeginDestroy() override;

	/// 
	void SetHUD( AHUD* hud ) {}

	///
	AHUD* GetHUD() const { return nullptr; }


	/// UI�� �����Ѵ�.
	template< typename Type >
	Type* CreateUI( FString InBpClassPath );

	/// UI�� ȭ�鿡 ����.( ������ �����Ѵ�. )
	template< typename Type >
	Type* ShowUI( FString InBpClassPath );

	/// ������ UI �� ȭ�鿡 ����.
	void ShowUI( UUserWidget* InUI , int32 InZOrder = 0 );

	/// ��� UI �� ȭ�鿡 ����Ѵ�.
	void ShowAll();

	/// ��� UI �� �����.
	void HideAllUI();


public:
	// UI �� �����Ѵ�.
	UFUNCTION( BlueprintCallable , Category = "UI" )
		UUserWidget* CreateUI( TSubclassOf< UUserWidget > InUserWidgetClass );

	// UI�� ȭ�鿡 ����.( ������ ���� )
	UFUNCTION( BlueprintCallable, Category = "UI" )
	UUserWidget* ShowUI( TSubclassOf< UUserWidget > InUserWidgetClass );

	// UI �� �ݴ´�.
	UFUNCTION( BlueprintCallable , Category = "UI" )
	void CloseUI( UUserWidget* InUI );

	// UI �� �����Ѵ�.
	UFUNCTION( BlueprintCallable , Category = "UI" )
	void RemoveUI( UUserWidget* InUI );
};

template< typename Type >
Type* UUIManager::CreateUI( FString InBpClassPath )
{
	if ( !bInitialized )
		return;

	UClass* LoadedClass = ConstructorHelpersInternal::FindOrLoadClass( InBpClassPath , UUserWidget::StaticClass() );
	if ( !LoadedClass )
	{
		return nullptr;
	}

	UUserWidget* UI = CreateWidget< UUserWidget >( GetGameInstPtr() , LoadedClass );
	if ( !UI )
		return nullptr;

	return Cast< Type >( UI );
}

template< typename Type >
Type* UUIManager::ShowUI( FString InBpClassPath )
{
	Type* UI = CreateUI< Type >( InBpClassPath );
	if ( !UI )
		return nullptr;

	ShowUI( UI );

	return UI;
}
