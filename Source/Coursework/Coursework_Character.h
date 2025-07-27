#pragma once

#include "CoreMinimal.h"
#include "Coursework_PreCharacter.h"
#include "InputAction.h"
#include "Machine_Enemy.h"
#include <EnhancedInputSubsystemInterface.h>
#include "MyAnimClass.h"
#include "Components/DecalComponent.h"
#include "Coursework_Character.generated.h"


class UInputComponent;
class USceneComponent;
class UCameraComponent;
class UWidgetComponent;
class UAnimMontage;
class USoundBase;
class UMyAnimClass;

//------------------------------------------------------------------------------------------------------------
UCLASS(config = Game)
class ACoursework_Character : public ACoursework_PreCharacter
{
	GENERATED_BODY()

public:
	
	ACoursework_Character();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UMyAnimClass* Current_Anim;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) bool Is_GamePad;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Transient)
	UCourseWork_Save_Data* Saved_Data;

	

	 AWeapon* Get_Current_Weapon()const override { return Weapon; };
	 void Set_Current_Weapon(AWeapon* v) override { Weapon = v; };
	 
	 void Destroy_Self()override;


	UPROPERTY(EditAnywhere, Category = "UI") UWidgetComponent* HealthBar_Widget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI") UWidgetComponent* Died_Screen_Widget;
	 



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI") UWidgetComponent* Mark;

	UFUNCTION(BlueprintCallable) virtual UWidget* Get_Mark_BP_Char()const {
		return Mark->GetWidget();
	}


protected:
	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(UInputComponent* input_component);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray<AActor*> Interactable_Actors;  // Предметы, с которыми игрок может взаимодействовать
private:
	void On_Action_Move(const FInputActionValue& value);  // Обработка movement input
	void On_Action_Look(const FInputActionValue& value);  // Обработка looking input
	void On_Action_Fire(const FInputActionValue& value);
	void On_Action_Use(const FInputActionValue& value);
	void On_Action_Restor(const FInputActionValue& value);


	void Pickup_Weapon(AWeapon* weapon);  // Приаттачить пушку к персонажу
	void Check_Inputs();

	UFUNCTION() void On_Overlap_Begin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void On_End_Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Decal_Correction(AActor* item);
	AActor* Distance_Count();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) UCameraComponent* FirstPersonCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* Action_Jump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* Action_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* Action_Look;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* Action_Fire;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* Action_Use;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* Action_Restor;


	
	UPROPERTY(VisibleAnywhere)UDecalComponent* DecalQ;
	UPROPERTY(VisibleAnywhere)UDecalComponent* DecalB;

	UPROPERTY(VisibleAnywhere)UClass* DecalInstance;
	AStaticMeshActor* DecalActor;



	AWeapon* Weapon;



	

};
//------------------------------------------------------------------------------------------------------------HasRifle
