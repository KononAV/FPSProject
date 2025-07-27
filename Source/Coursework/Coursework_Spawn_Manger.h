// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Machine_Enemy.h"
#include "Coursework_Spawn_Manger.generated.h"

UCLASS()
class COURSEWORK_API ACoursework_Spawn_Manger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoursework_Spawn_Manger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();


	void Spawn();

	
	FTimerHandle Current_Timer;

};
