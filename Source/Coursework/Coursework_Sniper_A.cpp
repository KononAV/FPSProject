
#include "Coursework_Sniper_A.h"


ACoursework_Sniper_A::ACoursework_Sniper_A()
{
	Valid = false;
	


	///Game/Weapon/MilitaryWeapSilver/Weapons/Meshes/Sniper_Rifle_A.Sniper_Rifle_A_C
}
void ACoursework_Sniper_A::BeginPlay() {
	Super::BeginPlay();
	Mesh = FindComponentByClass<USkeletalMeshComponent>();

	Mesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/Weapon/MilitaryWeapSilver/Weapons/Meshes/Sniper_Rifle_A")));
	if (Mesh) {
		Valid_Weapons.AddUnique("/Game/Weapon/MilitaryWeapSilver/Weapons/Meshes/Sniper_Rifle_A");
		Valid = true;

	}
	
	
}


