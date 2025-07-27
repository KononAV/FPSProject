#pragma once

#include "CoreMinimal.h"
#include "Coursework_Projectile.h"
#include "Coursework_PreCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/TimelineComponent.h"

#include "NiagaraFunctionLibrary.h"  
#include "NiagaraComponent.h"
#include "Machine_Enemy.generated.h"



UCLASS(config = Game)
class COURSEWORK_API AMachine_Enemy : public ACoursework_PreCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMachine_Enemy();

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)UPawnSensingComponent* PawnSensingComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)UNiagaraComponent* NiagaraComponent;

	


	AWeapon* Get_Current_Weapon()const override { return Weapon; };
	void Set_Current_Weapon(AWeapon* v) override { Weapon = v; };

	virtual void Destroy_Self() override;

	//static TArray<AWeapon*> Enemy_Weapons;
	void Spawn_Niagara();


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();


private:
	UPROPERTY()UTimelineComponent* FallTimeline;

	AWeapon* Weapon;
};
//Capsule