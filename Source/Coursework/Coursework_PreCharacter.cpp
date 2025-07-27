// Fill out your copyright notice in the Description page of Project Settings.


#include "Coursework_PreCharacter.h"


// Sets default values
ACoursework_PreCharacter::ACoursework_PreCharacter()
{
	InitialLifeSpan = 0.0f;

}

// Called when the game starts or when spawned
void ACoursework_PreCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACoursework_PreCharacter::Destroy_Self() 
{
	//
	if (Dead && GetMesh() && GetMesh()->GetAnimInstance())
	{
		if (USkeletalMeshComponent* SkeletalMesh = Mesh_1P)
		{
			
			SkeletalMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);

			if (Dead)
			{
				// Устанавливаем и проигрываем анимацию
				SkeletalMesh->SetAnimation(Dead);
				SkeletalMesh->Play(true); 
				
				UE_LOG(LogTemp, Warning, TEXT("--------------------------------Anim Played--------------------------------"));
			}
		}
	}
	else {
		

		UE_LOG(LogTemp, Warning, TEXT("--------------------------------ERROR--------------------------------"));
	}
	if (Get_Current_Weapon()) {
		Get_Current_Weapon()->Detach();
	}

}

void ACoursework_PreCharacter::Pickup_Weapon(AWeapon* weapon) {
	Set_Current_Weapon(weapon);
	Get_Current_Weapon()->Attach(Mesh_1P);
	
}
