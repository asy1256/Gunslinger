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
	USkeletalMeshComponent* Mesh;          /// Ÿ�ٸ޽�
	struct FGWFacialInfo      FacialInfo;    /// ���̼� �ִ� ����
	float                   FacialTerm;    /// ������Ʈ �ֱ�
	float                   TickStart;     ///
	int                     LipArrayCount; /// �� �ִ� ����



public:
	/// Ÿ�ٸ޽��� �����Ѵ�.
	UFUNCTION( BlueprintCallable , Category = "Character|Facial Compoment" )
	void SetMesh( USkeletalMeshComponent* _Mesh ) { Mesh = _Mesh; }

	/// ���̼� �ִ� ������ �����Ѵ�.
	UFUNCTION( BlueprintCallable , Category = "Character|Facial Compoment" )
	void SetFacialInfo( const struct FGWFacialInfo& _FacialInfo ) { FacialInfo = _FacialInfo; }

	/// ������Ʈ �ֱ⸦ �����Ѵ�.
	UFUNCTION( BlueprintCallable , Category = "Character|Facial Compoment" )
	void SetFacialTerm( float _FacialTerm ) { FacialTerm = _FacialTerm; }

	///�� �����Ѵ�.
	UFUNCTION( BlueprintCallable , Category = "Character|Facial Compoment" )
	void SetTickStart( float _TickStart ) { TickStart = _TickStart; }

	/// �� �ִ� ������ �����Ѵ�.
	UFUNCTION( BlueprintCallable , Category = "Character|Facial Compoment" )
	void SetLipArrayCount( int _LipArrayCount ) { LipArrayCount = _LipArrayCount; }

	/// Ÿ�ٸ޽��� ��ȯ�Ѵ�.
	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "Character|Facial Compoment" )
	USkeletalMeshComponent* GetMesh() const { return Mesh; }

	/// ���̼� �ִ� ������ ��ȯ�Ѵ�.
	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "Character|Facial Compoment" )
	const struct FGWFacialInfo& GetFacialInfo() const { return FacialInfo; }

	/// ������Ʈ �ֱ⸦ ��ȯ�Ѵ�.
	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "Character|Facial Compoment" )
	float GetFacialTerm() const { return FacialTerm; }

	///�� ��ȯ�Ѵ�.
	UFUNCTION( BlueprintCallable , BlueprintPure , Category = "Character|Facial Compoment" )
	float GetTickStart() const { return TickStart; }

	/// �� �ִ� ������ ��ȯ�Ѵ�.
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
