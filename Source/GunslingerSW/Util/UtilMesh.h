////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file	GunslingerSW\Util\UtilMesh.h
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <Components/SkeletalMeshComponent.h>

namespace UtilMesh
{
	// 스켈레탈 메쉬를 등록한다.
	USkeletalMeshComponent* RegisterSkeletalMeshComp( USkeletalMeshComponent* InMeshComponent , const FStringAssetReference& InAssetRef );

	// 스켈레탈 메쉬를 등록한다.
	USkeletalMeshComponent* RegisterSkeletalMeshComp( USkeletalMeshComponent* InMeshComponent , const TCHAR* InSubMeshName );

	// 스켈레탈 메쉬를 등록한다.
	USkeletalMeshComponent* RegisterSkeletalMeshComp( USkeletalMeshComponent* InMeshComponent , USkeletalMesh* InSubMesh );

	// 스켈레탈 메쉬를 제거하낟.
	void RemoveSkeletalMeshComp( USkeletalMeshComponent* InMeshComp );

	/// CullDistance 를 물려받는다.
	void InheritCullDistance( UPrimitiveComponent* InParentMeshComponent , UPrimitiveComponent* InTargetMeshComponent );

	/// 스켈레탈 메쉬의 퀄리티를 변경한다.
	void SetMeshQuality( bool InHigh = false );
}
