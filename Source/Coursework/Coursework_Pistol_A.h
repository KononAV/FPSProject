// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AWeapon.h"
#include "Components/MeshComponent.h"
#include "Coursework_Pistol_A.generated.h"

class USkeletalMeshComponent;

UCLASS()
class COURSEWORK_API ACoursework_Pistol_A : public AWeapon
{
	GENERATED_BODY()
public:
	ACoursework_Pistol_A();
	bool Valid;

	int Bullet_Store;
	virtual float Get_HP_Rate() const override { return 8; };



protected:

	virtual void BeginPlay();



};