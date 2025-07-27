#pragma once

//#include "Coursework_Character.h"
//#include "Machine_Enemy.h"
#include "Coursework_Projectile.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"

#include "AWeapon.generated.h"



class ACoursework_Character;
class AMachine_Enemy;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class COURSEWORK_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();

	void Attach(USkeletalMeshComponent* arms_mesh);
	void Detach();

	TArray<FString> Valid_Weapons;

	virtual float Get_HP_Rate()const { return 0; };

	UFUNCTION(BlueprintCallable, Category = "Weapon")virtual int Get_Bullet_Count()const { return Current_Bullet; };
	UFUNCTION(BlueprintCallable, Category = "Weapon")virtual void Set_Bullet_Count() { Current_Bullet = Max_Bullet; };
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")virtual int Get_Bullet_Store()const { return Current_Store; };
	UFUNCTION(BlueprintCallable, Category = "Weapon")virtual void Set_Bullet_Store(int count) { Current_Store += count; };

	 const int Max_Bullet = 12;
	 const int Max_Store = 4;
	 ACoursework_Character* CurrentOwner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)int Current_Bullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)int Current_Store;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh) USkeletalMeshComponent* MeshInd;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI") UWidgetComponent* Mark;

	UFUNCTION(BlueprintCallable) virtual UWidget* Get_Mark_BP_Char()const {
		return Mark->GetWidget();
	}

	

	UFUNCTION(BlueprintCallable, Category = "Weapon") void Fire(ACharacter* actor);  // Выстрелить снарядом

	UPROPERTY(EditDefaultsOnly, Category = Projectile) TSubclassOf<class ACoursework_Projectile> Projectile_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) USoundBase* Fire_Sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimMontage* Fire_Animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) FVector Muzzle_Offset;  // Смещение дула пушки от позиции персонажа



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh) USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh) USkeletalMeshComponent* Perent_Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)USphereComponent* Sphere;



private:
	


};
//------------------------------------------------------------------------------------------------------------
//stalker