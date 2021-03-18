// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessagePopup.generated.h"

/**
 * 
 */

UCLASS()
class GUNSLINGERSW_API UMessagePopup : public UUserWidget
{
	GENERATED_BODY()

private:

public:
	/// ������
	UMessagePopup( const FObjectInitializer& ObjectInitializer );

	/// �Ҹ���
	virtual void BeginDestroy() override;

protected:
	UFUNCTION( BlueprintCallable )
	void SetResultCode( int InResultCodeId );
	
	
};
