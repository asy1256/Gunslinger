// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../Data/GP2DataStructTypes.h"
#include "FacialComp.generated.h"



UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUNSLINGERSW_API UFacialComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFacialComp();


private:
	USkeletalMeshComponent* Mesh;          /// 타겟메쉬
	struct FGWFacialInfo      FacialInfo;    /// 페이셜 애니 정보
	float                   FacialTerm;    /// 업데이트 주기
	float                   TickStart;     ///
	int                     LipArrayCount; /// 립 애니 개수



public:
	/// 타겟메쉬를 설정한다.
	UFUNCTION( BlueprintCallable , Category = "Character|Facial Compoment" )
	void SetMesh( USkeletalMeshComponent* _Mesh ) { Mesh = _Mesh; }

	/// 페이셜 애니 정보를 설정한다.
	UFUNCTION( BlueprintCallable , Category = "Character|Facial Compoment" )
	void SetFacialInfo( const struct FGWFacialInfo& _FacialInfo ) { FacialInfo = _FacialInfo; }

	/// 업데이트 주기를 설정한다.
	UFUNCTION( BlueprintCallable , Category = "Character|Facial Compoment" )
	void SetFacialTerm( float _FacialTerm ) { FacialTerm = _FacialTerm; }

	///을 설정한다.
	UFUNCTION( BlueprintCallable , Category = "Character|Facial Compoment" )
	void SetTickStart( float _TickStart ) { TickStart = _TickStart; }

	/// 립 애니 개수를 설정한다.
	UFUNCTION( BlueprintCallable , Category = "Character|Facial Compoment" )
	void SetLipArrayCount( int _LipArrayCount ) { LipArrayCount = _LipArrayCount; }

	/// 타겟메쉬를 반환한다.
	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "Character|Facial Compoment" )
	USkeletalMeshComponent* GetMesh() const { return Mesh; }

	/// 페이셜 애니 정보를 반환한다.
	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "Character|Facial Compoment" )
	const struct FGWFacialInfo& GetFacialInfo() const { return FacialInfo; }

	/// 업데이트 주기를 반환한다.
	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "Character|Facial Compoment" )
	float GetFacialTerm() const { return FacialTerm; }

	///을 반환한다.
	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "Character|Facial Compoment" )
	float GetTickStart() const { return TickStart; }

	/// 립 애니 개수를 반환한다.
	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "Character|Facial Compoment" )
	int GetLipArrayCount() const { return LipArrayCount; }



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	////UFUNCTION( BlueprintCallable )
	//void N_FaceEmotion();

	////UFUNCTION( BlueprintCallable )
	//float N_GetCurveValue( FInterpCurveFloat& Curve );

	////UFUNCTION( BlueprintCallable )
	//void N_SetFacial( FString Key );
		
};
