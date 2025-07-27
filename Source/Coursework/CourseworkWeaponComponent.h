#pragma once

#include "Coursework_Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "CourseworkWeaponComponent.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COURSEWORK_API UCourseworkWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UCourseworkWeaponComponent();

	UFUNCTION(BlueprintCallable, Category = "Weapon") void AttachWeapon(ACoursework_Character* TargetCharacter);  // Приаттачить пушку к персонажу
	UFUNCTION(BlueprintCallable, Category = "Weapon") void Fire();  // Выстрелить снарядом

	UPROPERTY(EditDefaultsOnly, Category = Projectile) TSubclassOf<class ACoursework_Projectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimMontage* FireAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) FVector MuzzleOffset;  // Смещение дула пушки от позиции персонажа

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputMappingContext* FireMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* FireAction;

protected:
	virtual void EndPlay(const EEndPlayReason::Type end_play_reason) override;

private:
	ACoursework_Character* Character;  // Персонаж, который держит это оружие
};
//------------------------------------------------------------------------------------------------------------
