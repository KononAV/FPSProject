#include "Coursework_Projectile.h"
#include "Coursework_PreCharacter.h"
#include "Coursework_Character.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

//-------------------------------------------------------------
ACoursework_Projectile::ACoursework_Projectile() 
{
	// Use a sphere as a simple collision representation
	Collision_Comp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	Collision_Comp->InitSphereRadius(1.16f);
	Collision_Comp->BodyInstance.SetCollisionProfileName("Projectile");
	Collision_Comp->OnComponentHit.AddDynamic(this, &ACoursework_Projectile::On_Hit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	Collision_Comp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Collision_Comp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = Collision_Comp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	Projectile_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	Projectile_Movement->UpdatedComponent = Collision_Comp;
	Projectile_Movement->InitialSpeed = 6000.f;
	Projectile_Movement->MaxSpeed = 6000.f;
	Projectile_Movement->bRotationFollowsVelocity = true;
	Projectile_Movement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}
//-------------------------------------------------------------

void ACoursework_Projectile::On_Hit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& Hit)
{

	if (ACoursework_PreCharacter* character = Cast<ACoursework_PreCharacter>(other_actor))
	{
		
		
			character->Health_Bar -= HP_Rate;
			UE_LOG(LogTemp, Warning, TEXT("%f"), character->Health_Bar);

			UE_LOG(LogTemp, Warning, TEXT("--------------------------------Sucsess HIT--------------------------------"));
	
			if (character->Health_Bar <= 0&& !character->Is_Dead) {
				
				
				character->Destroy_Self(); 
				character->Is_Dead = true;
				
				if(WeaponOwner!=nullptr)
				WeaponOwner->Saved_Data->Kills++;
			}
	}

	// Only add impulse and destroy projectile if we hit a physics
	if ((other_actor != 0) && (other_actor != this) && (other_comp != 0) && other_comp->IsSimulatingPhysics())
	{
		
		other_comp->AddImpulseAtLocation(GetVelocity() * 1000.0f, GetActorLocation());

		
	}
	Destroy();
}
//-------------------------------------------------------------
//mesh_1p