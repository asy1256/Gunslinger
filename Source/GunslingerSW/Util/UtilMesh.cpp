////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file	GunslingerSW\Util\UtilMesh.h
////////////////////////////////////////////////////////////////////////////////////////////////////

//#pragma once

#include "UtilMesh.h"
#include "GunslingerSW.h"

namespace UtilMesh
{

	USkeletalMeshComponent* RegisterSkeletalMeshComp( USkeletalMeshComponent* InMeshComponent , const FStringAssetReference& InAssetRef )
	{
		if ( !InAssetRef.IsValid() )
			return nullptr;

		return RegisterSkeletalMeshComp( InMeshComponent , *InAssetRef.ToString() );
	}

	USkeletalMeshComponent* RegisterSkeletalMeshComp( USkeletalMeshComponent* InMeshComponent , const TCHAR* InSubMeshName )
	{
		USkeletalMesh* newMesh = LoadObject< USkeletalMesh >( nullptr , InSubMeshName , nullptr , LOAD_None , nullptr );
		if ( newMesh )
			RegisterSkeletalMeshComp( InMeshComponent , newMesh );

		
		return nullptr;
	}

	USkeletalMeshComponent* RegisterSkeletalMeshComp( USkeletalMeshComponent* InMeshComponent , USkeletalMesh* InSubMesh )
	{
		USkeletalMeshComponent* newMesh = NewObject< USkeletalMeshComponent >();
		newMesh->SetMasterPoseComponent( InMeshComponent );
		newMesh->SetSkeletalMesh( InSubMesh );
		newMesh->UpdateMasterBoneMap();
		newMesh->AttachToComponent( InMeshComponent , FAttachmentTransformRules::KeepRelativeTransform );
		newMesh->RegisterComponentWithWorld( InMeshComponent->GetWorld() );

		return newMesh;
	}

	void RemoveSkeletalMeshComp( USkeletalMeshComponent* InMeshComp )
	{
		if ( InMeshComp )
		{
			InMeshComp->DetachFromComponent( FDetachmentTransformRules::KeepRelativeTransform );
			InMeshComp->UnregisterComponent();
			InMeshComp->DestroyComponent( true );

			InMeshComp = nullptr;
		}
	}

	void InheritCullDistance( UPrimitiveComponent* InParentMeshComponent , UPrimitiveComponent* InTargetMeshComponent )
	{
		if ( !InParentMeshComponent || !InTargetMeshComponent )
			return;

		InTargetMeshComponent->SetCachedMaxDrawDistance( InParentMeshComponent->LDMaxDrawDistance );
		InTargetMeshComponent->SetCullDistance( InParentMeshComponent->LDMaxDrawDistance );
		InTargetMeshComponent->bAllowCullDistanceVolume = InParentMeshComponent->bAllowCullDistanceVolume;
	}

	void SetMeshQuality( bool InHigh /*= false */ )
	{
		if ( InHigh )
		{
		}
		else
		{
		}
	}

}
