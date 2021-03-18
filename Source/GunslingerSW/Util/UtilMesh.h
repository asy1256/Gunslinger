////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file	GunslingerSW\Util\UtilMesh.h
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <Components/SkeletalMeshComponent.h>

namespace UtilMesh
{
	// ���̷�Ż �޽��� ����Ѵ�.
	USkeletalMeshComponent* RegisterSkeletalMeshComp( USkeletalMeshComponent* InMeshComponent , const FStringAssetReference& InAssetRef );

	// ���̷�Ż �޽��� ����Ѵ�.
	USkeletalMeshComponent* RegisterSkeletalMeshComp( USkeletalMeshComponent* InMeshComponent , const TCHAR* InSubMeshName );

	// ���̷�Ż �޽��� ����Ѵ�.
	USkeletalMeshComponent* RegisterSkeletalMeshComp( USkeletalMeshComponent* InMeshComponent , USkeletalMesh* InSubMesh );

	// ���̷�Ż �޽��� �����ϳ�.
	void RemoveSkeletalMeshComp( USkeletalMeshComponent* InMeshComp );

	/// CullDistance �� �����޴´�.
	void InheritCullDistance( UPrimitiveComponent* InParentMeshComponent , UPrimitiveComponent* InTargetMeshComponent );

	/// ���̷�Ż �޽��� ����Ƽ�� �����Ѵ�.
	void SetMeshQuality( bool InHigh = false );
}
