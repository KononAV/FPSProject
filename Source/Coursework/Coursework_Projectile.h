// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coursework_Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class ACoursework_Character;

//-------------------------------------------------------------
UCLASS(config=Game)
class ACoursework_Projectile : public AActor
{
	GENERATED_BODY()
	
public:
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)USphereComponent* Collision_Comp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* Projectile_Movement;


	ACoursework_Projectile();

	/** called when projectile hits something */
	UFUNCTION()void On_Hit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& Hit);

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile) float HP_Rate;

	ACoursework_Character* WeaponOwner;

};
//-------------------------------------------------------------
