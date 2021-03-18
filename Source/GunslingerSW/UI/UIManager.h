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
	bool bInitialized; /// 초기화가 유무

	FUiSet ShowUiList;		/// 뷰포트에 추가된 UI 목록

	FUiMap ManagedList;		/// 관리중인 UI 목록( 중복으로 사용하는 UI-Template 처리 )


public:
	UUIManager();

	/// 
	virtual void BeginDestroy() override;

	/// 
	void SetHUD( AHUD* hud ) {}

	///
	AHUD* GetHUD() const { return nullptr; }


	/// UI를 생성한다.
	template< typename Type >
	Type* CreateUI( FString InBpClassPath );

	/// UI를 화면에 띄운다.( 없으면 생성한다. )
	template< typename Type >
	Type* ShowUI( FString InBpClassPath );

	/// 생성된 UI 를 화면에 띄운다.
	void ShowUI( UUserWidget* InUI , int32 InZOrder = 0 );

	/// 모든 UI 를 화면에 출력한다.
	void ShowAll();

	/// 모든 UI 를 감춘다.
	void HideAllUI();


public:
	// UI 를 생성한다.
	UFUNCTION( BlueprintCallable , Category = "UI" )
		UUserWidget* CreateUI( TSubclassOf< UUserWidget > InUserWidgetClass );

	// UI를 화면에 띄운다.( 없으면 생성 )
	UFUNCTION( BlueprintCallable, Category = "UI" )
	UUserWidget* ShowUI( TSubclassOf< UUserWidget > InUserWidgetClass );

	// UI 를 닫는다.
	UFUNCTION( BlueprintCallable , Category = "UI" )
	void CloseUI( UUserWidget* InUI );

	// UI 를 제거한다.
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
