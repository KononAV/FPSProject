// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AWeapon.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "CourseWork_Save_Data.h"
#include "Coursework_PreCharacter.generated.h"

class USkeletalMeshComponent;

UCLASS()
class COURSEWORK_API ACoursework_PreCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACoursework_PreCharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float Health_Bar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh) USkeletalMeshComponent* Mesh_1P;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) AWeapon* Current_Weapon;
	UFUNCTION(BlueprintCallable) virtual AWeapon* Get_Current_Weapon()const { return 0; };
	UFUNCTION(BlueprintCallable) virtual void Set_Current_Weapon(AWeapon* v) {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)UAnimMontage* Dead;
	

	bool Is_Dead = false;


	virtual void Destroy_Self();
	virtual void Pickup_Weapon(AWeapon* weapon);

protected:
	virtual void BeginPlay();



};
