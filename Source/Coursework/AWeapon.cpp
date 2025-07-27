
#include "AWeapon.h"

//------------------------------------------------------------------------------------------------------------
AWeapon::AWeapon()
{
	Muzzle_Offset = FVector(100.0f, 0.0f, 10.0f);
	
	// ¬ конструкторе:
	//MeshComponent->SetSimulatePhysics(true);
	Current_Bullet = Max_Bullet;
	Current_Store = Max_Store;
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon_Mesh_C"));
	Mesh->SetupAttachment(RootComponent);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Weapon_Sphere_C"));
	Sphere->SetupAttachment(Mesh);

	
	//Mesh_1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));


	Mark = CreateDefaultSubobject<UWidgetComponent>(TEXT("WeaponWidget"));
	Mark->SetupAttachment(Mesh);


	Mark->SetDrawSize(FVector2D(500, 500));
	Mark->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}




//------------------------------------------------------------------------------------------------------------
void AWeapon::Attach(USkeletalMeshComponent* arms_mesh)
{
	USceneComponent* root_component = GetRootComponent();

	if (UPrimitiveComponent* prim_component = Cast<UPrimitiveComponent>(root_component))
	{
		prim_component->SetSimulatePhysics(false);
		
		prim_component->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
		//Sphere = GetComponentByClass<USphereComponent>();
		
	}

	// јттачим оружие к персонажу
	FAttachmentTransformRules attachment_rules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(arms_mesh, attachment_rules, FName(TEXT("GripPoint")));

	Mark->SetWidgetClass(LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/WB_Weapon.WB_Weapon_C")));

	if (Sphere) {
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
		UE_LOG(LogTemp, Warning, TEXT("----------------Shpere Collision--------------------"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("----------------ERROR Shpere Collision---------------"));
	}
}
//------------------------------------------------------------------------------------------------------------
void AWeapon::Detach()
{
	USceneComponent* root_component = GetRootComponent();
	

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	if (UPrimitiveComponent* prim_component = Cast<UPrimitiveComponent>(root_component))
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		prim_component->SetSimulatePhysics(true);
		prim_component->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);

		
			Mark->SetWidgetClass(nullptr);

		//prim_component->OnComponentHit.AddDynamic(this, &AWeapon::OnHit);
		
	}
		
	
	
}
//------------------------------------------------------------------------------------------------------------


void AWeapon::Fire(ACharacter* actor)
{
	
	if (Current_Bullet > 0) {

		// ѕытаемс€ выстрелить снар€дом
		if (Projectile_Class != 0)
		{
			if (UWorld* world = GetWorld())
			{
				FRotator spawn_rotation;

				if (APlayerController* player_controller = Cast<APlayerController>(actor->GetController())) {
					spawn_rotation = player_controller->PlayerCameraManager->GetCameraRotation();
				}
				else {
					spawn_rotation = actor->GetViewRotation();
					Current_Bullet += 1;
				}
				FVector spawn_location = GetActorLocation() + spawn_rotation.RotateVector(Muzzle_Offset);


				// “.к. Muzzle_Offset представлен в пространстве камеры, его надо перевести в мировое пространство прежде, чем смещать от позиции персонажа дл€ того, чтобы получить итоговую позицию дула


				// ”станавливаем обработку столкновени€ при спавне
				FActorSpawnParameters actor_spawn_params;
				actor_spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				

				ACoursework_Projectile* pr = world->SpawnActor<ACoursework_Projectile>(Projectile_Class, spawn_location, spawn_rotation, actor_spawn_params);  // —павним снар€д на дуле

				pr->HP_Rate = Get_HP_Rate();
				pr->WeaponOwner = CurrentOwner;
				Current_Bullet -= 1;
			}
		};


		if (Fire_Sound != 0)
			UGameplayStatics::PlaySoundAtLocation(this, Fire_Sound, GetActorLocation());  // ѕытаемс€ проиграть звук выстрела, если он указан
	}
	
}
//------------------------------------------------------------------------------------------------------------

