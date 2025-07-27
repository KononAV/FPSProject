// Fill out your copyright notice in the Description page of Project Settings.


#include "Coursework_Spawn_Manger.h"
#include "TimerManager.h"

// Sets default values
ACoursework_Spawn_Manger::ACoursework_Spawn_Manger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoursework_Spawn_Manger::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		Current_Timer,
		this,
		&ACoursework_Spawn_Manger::Spawn,
		15,
		true
		);
	
}

void ACoursework_Spawn_Manger::Spawn() {
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = FRotator::ZeroRotator;

	

	TSubclassOf<AMachine_Enemy>BPClass = StaticLoadClass(AMachine_Enemy::StaticClass(), nullptr, TEXT("/Game/NPC/PB_NPC_Machine.PB_NPC_Machine_C"));
	AMachine_Enemy* enemy = GetWorld()->SpawnActor<AMachine_Enemy>(BPClass, SpawnLocation, SpawnRotation);

	TSubclassOf<AActor>AABP = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/Weapon/MilitaryWeapSilver/Pickups/Pistol_Stor.Pistol_Stor_C"));
	AActor* SpawnAA = GetWorld()->SpawnActor<AActor>(AABP, SpawnLocation, SpawnRotation);

	//AIPerceptionComponent->SetSenseEnabled(UAISense_Sight::StaticClass(), true);
	
	//enemy->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

