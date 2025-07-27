// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AWeapon.h"
#include "Components/MeshComponent.h"
#include "Coursework_Sniper_A.generated.h"

class USkeletalMeshComponent;

UCLASS()
class COURSEWORK_API ACoursework_Sniper_A : public AWeapon
{
	GENERATED_BODY()
public:
	ACoursework_Sniper_A();
	bool Valid;
	virtual float Get_HP_Rate() const override { return 15; };


protected:

	virtual void BeginPlay();


	
};
