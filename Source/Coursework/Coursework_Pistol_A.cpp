
#include "Coursework_Pistol_A.h"


ACoursework_Pistol_A::ACoursework_Pistol_A()
{
	Valid = false;
	

	
	///Game/Weapon/MilitaryWeapSilver/Weapons/Meshes/Pistols_A
}

void ACoursework_Pistol_A::BeginPlay() {
	Super::BeginPlay();
	Mesh = FindComponentByClass<USkeletalMeshComponent>();

	Mesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/Weapon/MilitaryWeapSilver/Weapons/Meshes/Pistols_A")));
	if (Mesh) {
		Valid_Weapons.AddUnique("/Game/Weapon/MilitaryWeapSilver/Weapons/Meshes/Pistols_A");
		Valid = true;

	}


}


