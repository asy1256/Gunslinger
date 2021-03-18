// Fill out your copyright notice in the Description page of Project Settings.


#include "FacialComp.h"
#include "Components/SkeletalMeshComponent.h"
#include "Curves/CurveFloat.h"

// Sets default values for this component's properties
UFacialComp::UFacialComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFacialComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFacialComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


//void UFacialComp::N_FaceEmotion()
//{
//	if ( !Mesh )
//		return;
//
//	Mesh->SetMorphTarget( TEXT( "Morph_eyebrow"      ) , N_GetCurveValue( FacialInfo.EyeBrowAnger    ) *  FacialInfo.EyeBrowAngerScale    );
//	Mesh->SetMorphTarget( TEXT( "Morph_chic"         ) , N_GetCurveValue( FacialInfo.SmileMouth      ) *  FacialInfo.SmileMouthScale      );
//	Mesh->SetMorphTarget( TEXT( "Morph_FocusChic"    ) , N_GetCurveValue( FacialInfo.SmlieRightMouth ) *  FacialInfo.SmileRightMouthScale );
//	Mesh->SetMorphTarget( TEXT( "Morph_ugh"          ) , N_GetCurveValue( FacialInfo.AngryFace       ) *  FacialInfo.AngryFaceScale       );
//	Mesh->SetMorphTarget( TEXT( "Morph_ugh_MC"       ) , N_GetCurveValue( FacialInfo.AngryEye        ) *  FacialInfo.AngryEyeScale        );
//	Mesh->SetMorphTarget( TEXT( "Morph_ugh_EyeCL_MC" ) , N_GetCurveValue( FacialInfo.AngryLeftEye    ) *  FacialInfo.AngryLeftEyeScale    );
//}

//float UFacialComp::N_GetCurveValue( FInterpCurveFloat& Curve )
//{
//	float tick = 1.0f;
//
//	if( tick - TickStart > FacialTerm )
//		TickStart = 0.0f;
//
//	if ( ( tick - TickStart ) / FacialTerm < 0 )
//		TickStart = 0.0f;
//
//
////	return Curve.GetFloatValue( FMath::Clamp( ( tick - TickStart ) / FacialTerm , 0.0f , 1.0f ) );
//	return 0.0f;
//}
//
//void UFacialComp::N_SetFacial( FString Key )
//{
//}
