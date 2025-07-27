// Fill out your copyright notice in the Description page of Project Settings.
#include "Machine_Enemy.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "TimerManager.h"
#include "Components/MeshComponent.h"




// Sets default values
AMachine_Enemy::AMachine_Enemy()
{
	Health_Bar = 20;
	Mesh_1P = GetMesh();
	UE_LOG(LogTemp, Warning, TEXT("%f"), Health_Bar);

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	

	PawnSensingComponent->SetActive(true);
	PawnSensingComponent->bAutoActivate = true;
	PawnSensingComponent->SetPeripheralVisionAngle(90.0f);  // Угол обзора
	PawnSensingComponent->SightRadius = 1900.0f;             // Радиус восприятия по зрению
	PawnSensingComponent->HearingThreshold = 2800.0f;  
	PawnSensingComponent->SetPeripheralVisionAngle(70);


	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);

}

void AMachine_Enemy::Spawn_Niagara() {


	


if (UNiagaraSystem* NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Basic_VFX/Niagara/NS_Basic_2.NS_Basic_2")))
	{

		FVector SpawnLocation = Mesh_1P->GetSocketLocation("SpineSocket");
		//NiagaraComponent->SetAsset(NiagaraEffect);
		//
		NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),                // Мировой контекст
			NiagaraEffect,             // Система частиц
			SpawnLocation,        // Позиция спауна
			FRotator::ZeroRotator      // Ориентация спауна
		);
		NiagaraComponent->SetWorldScale3D(FVector(10.0f));
		NiagaraComponent->ActivateSystem(true);
		NiagaraComponent->SetAutoDestroy(true);
	}
}

// Called when the game starts or when spawned
void AMachine_Enemy::BeginPlay()
{
	Super::BeginPlay();

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = FRotator::ZeroRotator;
	
	TSubclassOf<AWeapon>BPClass = StaticLoadClass(AWeapon::StaticClass(), nullptr, TEXT("/Game/Weapon/MilitaryWeapSilver/Weapons/BP_Pistol_A.BP_Pistol_A_C"));
	if (BPClass) {
		UE_LOG(LogTemp, Warning, TEXT("--------------------------------Sucsess--------------------------------"));
		AWeapon* SpawnedWeapon = GetWorld()->SpawnActor<AWeapon>(BPClass, SpawnLocation, SpawnRotation);
		Pickup_Weapon(SpawnedWeapon);

	}
	else UE_LOG(LogTemp, Warning, TEXT("--------------------------------ERROR--------------------------------"));
	//PawnSensingComponent

	
	

}

void AMachine_Enemy::Destroy_Self() {
	ACoursework_PreCharacter::Destroy_Self();

	FTimerHandle TimeHendler;
	GetWorldTimerManager().SetTimer(
		TimeHendler,
		[this]() {
			Spawn_Niagara();
			SetLifeSpan(1.5f);
		},
		5.0f,
		false
	);
	/*UCourseWork_Save_Data::Kills++;
	UCourseWork_Save_Data::Score+=100;*/

	

	
}




//Dead

