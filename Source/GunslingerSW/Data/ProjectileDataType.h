// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillDataType.h"
#include "GP2EnumTypes.h"
#include "ProjectileDataType.generated.h"


USTRUCT(BlueprintType)
struct FGWPivotRotate
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PivotRotate")
	FRotator RotateRate; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PivotRotate")
	FVector  Pivot;      ///
};




USTRUCT(BlueprintType)
struct FGWProjectileInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGWProjectileInfo()
	:
	Duration           ( 3.0f                            ) ,
	MaxHP              ( 0.0f                            ) ,
	DamageRate         ( 1.0f                            ) ,
	DoFullDamage       ( false                           ) ,
	InitialSpeed       ( 1000.0f                         ) ,
	MaxSpeed           ( 1000.0f                         ) ,
	ArroundSearch      ( false                           ) ,
	SearchRadius       ( 500.0f                          ) ,
	SearchInterval     ( 0.1f                            ) ,
	SearchTarget       ( EGWSearchTarget::None             ) ,
	SearchAndAction    ( EGWSearchAndAction::None          ) ,
	HomingDelayTime    ( 0.5f                            ) ,
	HomingTime         ( 0.0f                            ),
	HomingAcceleration ( 0.0f                            ),
	ExplosionRadius    ( 0.f                             ) ,
	SelfExplosion      ( true                            ) ,
	HitAction          ( EGWProjectileHitAction::Explosion ) ,
	Bouncines          ( 0.6f                            ) ,
	GravityValue       ( 0.f                             )                           
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                Duration;           ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                MaxHP;              ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                DamageRate;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	bool                 DoFullDamage;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                InitialSpeed;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                MaxSpeed;           ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
		struct FGWPivotRotate         RotateMovement;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	bool                 ArroundSearch;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                SearchRadius;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                SearchInterval;     ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	EGWSearchTarget        SearchTarget;       ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	EGWSearchAndAction     SearchAndAction;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                HomingDelayTime;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                HomingTime;         ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                HomingAcceleration; ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                ExplosionRadius;    ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	bool                 SelfExplosion;      ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	EGWProjectileHitAction HitAction;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                Bouncines;          ///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct|Projectile Info")
	float                GravityValue;       ///

};