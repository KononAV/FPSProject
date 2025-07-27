#include "Coursework_Character.h"
#include "Coursework_Projectile.h"
#include "AWeapon.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/InputDeviceSubsystem.h"



//------------------------------------------------------------------------------------------------------------
ACoursework_Character::ACoursework_Character()
{

	
	Health_Bar = 100;
	UE_LOG(LogTemp, Warning, TEXT("%f"), Health_Bar);
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);  
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::On_Overlap_Begin);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &ThisClass::On_End_Overlap);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.0f, 0.0f, 60.0f));  
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh_1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh_1P->SetOnlyOwnerSee(true);
	Mesh_1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh_1P->bCastDynamicShadow = false;
	Mesh_1P->CastShadow = false;
	//Mesh_1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh_1P->SetRelativeLocation(FVector(-30.0f, 0.0f, -150.0f));

	
	HealthBar_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CharacterWidget"));
	HealthBar_Widget->SetupAttachment(RootComponent);
	HealthBar_Widget->SetDrawSize(FVector2D(500, 500));
	HealthBar_Widget->SetWidgetSpace(EWidgetSpace::World);
	HealthBar_Widget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HealthBar_Widget->SetOnlyOwnerSee(true);
	HealthBar_Widget->SetWidgetClass(LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/WB_HealthBar.WB_HealthBar_C")));
		
	Died_Screen_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CharacterWidget2"));
	Died_Screen_Widget->SetupAttachment(RootComponent);
	Died_Screen_Widget->SetDrawSize(FVector2D(500, 500));
	Died_Screen_Widget->SetWidgetSpace(EWidgetSpace::World);
	Died_Screen_Widget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Died_Screen_Widget->SetOnlyOwnerSee(true);
	Died_Screen_Widget->SetWidgetClass(LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/WB_Death_Screen.WB_Death_Screen_C")));
	

	Mark = CreateDefaultSubobject<UWidgetComponent>(TEXT("WeaponWidget"));
	Mark->SetupAttachment(GetMesh());


	Mark->SetDrawSize(FVector2D(500, 500));
	Mark->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mark->SetWidgetClass(LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/WB_Weapon.WB_Weapon_C")));
	Mark->SetOnlyOwnerSee(true);

}

//------------------------------------------------------------------------------------------------------------
 void ACoursework_Character::BeginPlay(){
	Super::BeginPlay();
	//Died_Screen_Widget->GetWidget()->SetVisibility(ESlateVisibility::Hidden);

	Saved_Data = NewObject<UCourseWork_Save_Data>(this, UCourseWork_Save_Data::StaticClass());
	check(Saved_Data);

	if (Saved_Data == nullptr)UE_LOG(LogTemp, Error, TEXT("___________________________Save == null___________________________________"));
	Saved_Data->PlayerCount++;
	//UE_LOG(LogTemp, Warning, TEXT("%i"), UCourseWork_Save_Data::PlayerCount);

	if (Saved_Data->PlayerCount == 5) {
		Is_GamePad = true;
	}
	else {
		Is_GamePad = false;

	}

DecalInstance = LoadClass<AStaticMeshActor>(nullptr, TEXT("/Game/FBX/ButtonAct_Blueprint.ButtonAct_Blueprint_C"));
	if (DecalInstance) {
		UE_LOG(LogTemp, Warning, TEXT("DECAL LOADED___________________________________________"));
	}
	else 		UE_LOG(LogTemp, Warning, TEXT("DECAL ERROR___________________________________________"));

	Current_Anim = Cast<UMyAnimClass>(Mesh_1P->GetAnimInstance());
	if (APlayerController* player_controller = Cast<APlayerController>(Controller))
	{
		player_controller->SetInputMode(FInputModeGameOnly());
		player_controller->SetShowMouseCursor(false);
		if (UEnhancedInputLocalPlayerSubsystem* input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer()))
			input_subsystem->AddMappingContext(DefaultMappingContext, 0);
		
	}

	//CreateWidget(HealthBar_Widget);


	UUserWidget* Widget_Instance = Cast<UUserWidget>(HealthBar_Widget->GetWidget());
	//Widget_Instance->AddToViewport();
	
	if (DecalInstance) {
		DecalActor = GetWorld()->SpawnActor<AStaticMeshActor>(DecalInstance);
		DecalActor->SetActorHiddenInGame(true);
		if (DecalActor) { 
			UE_LOG(LogTemp, Warning, TEXT("DECAL SPAWNED___________________________________________"));
			TArray<UDecalComponent*> Decals;
			DecalActor->GetComponents<UDecalComponent>(Decals);
			if (Decals.Num() == 2) {
				DecalB = Decals[0];
				DecalQ = Decals[1];
			}

		}

		else {
			UE_LOG(LogTemp, Warning, TEXT("DECAL SPAWNED ERROR___________________________________________"));
		}

	}
	else UE_LOG(LogTemp, Warning, TEXT("DECAL INSTANSE2 ERROR___________________________________________"));
}
	
 void ACoursework_Character::On_Overlap_Begin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
	 int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
 {
	 Check_Inputs();

	 if (otherActor && (otherActor != this) && otherComp) {
		 Interactable_Actors.AddUnique(otherActor);
		 UE_LOG(LogTemp, Warning, TEXT("add to interactable  %s"), *otherActor->GetName());
	 }
	 if (Interactable_Actors.Num() > 0) {
		 Decal_Correction(Interactable_Actors[0]);
		 DecalActor->SetActorHiddenInGame(false);
	 }
	 

 }
 void ACoursework_Character::On_End_Overlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor,
	 UPrimitiveComponent* otherComp, int32 otherBodyIndex)
 {
	 if (otherActor && Interactable_Actors.Contains(otherActor))
	 {
		 Interactable_Actors.Remove(otherActor);
		 UE_LOG(LogTemp, Warning, TEXT("Removed interactable  %s"), *otherActor->GetName());
	 }
	 if (Interactable_Actors.Num() == 0) {
		 DecalActor->SetActorHiddenInGame(true);
	 }
	 else {
		 Decal_Correction(Interactable_Actors[Interactable_Actors.Num() - 1]);
	 }


 }

 void ACoursework_Character::Decal_Correction(AActor* item) {
	 DecalActor->SetActorLocation(item->GetActorLocation() + FVector(0, 0, 100));
	 DecalActor->SetActorRotation(this->GetActorRotation() + FRotator(0, 90, 0));
	 
 }

//------------------------------------------------------------------------------------------------------------
void ACoursework_Character::SetupPlayerInputComponent(UInputComponent* input_component)
{
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(input_component))
	{
		EnhancedInputComponent->BindAction(Action_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(Action_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(Action_Move, ETriggerEvent::Triggered, this, &ACoursework_Character::On_Action_Move);
		EnhancedInputComponent->BindAction(Action_Look, ETriggerEvent::Triggered, this, &ACoursework_Character::On_Action_Look);
		EnhancedInputComponent->BindAction(Action_Fire, ETriggerEvent::Triggered, this, &ACoursework_Character::On_Action_Fire);
		EnhancedInputComponent->BindAction(Action_Use, ETriggerEvent::Triggered, this, &ACoursework_Character::On_Action_Use);
		EnhancedInputComponent->BindAction(Action_Restor, ETriggerEvent::Triggered, this, &ACoursework_Character::On_Action_Restor);
	}
}
//------------------------------------------------------------------------------------------------------------
void ACoursework_Character::On_Action_Move(const FInputActionValue& value)
{
	FVector2D movement_vector = value.Get<FVector2D>();  // Ввод - это Vector2D

	if (Controller != 0)
	{// Добавим движение

		AddMovementInput(GetActorForwardVector(), movement_vector.Y);
		AddMovementInput(GetActorRightVector(), movement_vector.X);
	}
}
//------------------------------------------------------------------------------------------------------------
void ACoursework_Character::On_Action_Look(const FInputActionValue& value)
{
	FVector2D look_axis_vector = value.Get<FVector2D>();  // Ввод - это Vector2D

	if (Controller != 0)
	{// Добавим контроллеру Yaw и Pitch

		AddControllerYawInput(look_axis_vector.X);
		AddControllerPitchInput(look_axis_vector.Y);
	}
}

//------------------------------------------------------------------------------------------------------------
void ACoursework_Character::On_Action_Fire(const FInputActionValue& value)
{

	Check_Inputs();
	

	UE_LOG(LogTemp, Warning, TEXT("--------------------------------FIRE DETECTED--------------------------------"));

	if (Get_Current_Weapon() == 0|| !Current_Anim->HasRifle) {
		return;
	}
	Get_Current_Weapon()->Fire(this);
	if (UAnimInstance* anim_instance = Mesh_1P->GetAnimInstance())
		anim_instance->Montage_Play(Get_Current_Weapon()->Fire_Animation, 1.0f);  // Пытаемся проиграть анимацию, если она указана
	Saved_Data->Score -= 10;
	//UE_LOG(LogTemp, Warning, TEXT("_____________%i______________"), UCourseWork_Save_Data::Score);

}

//------------------------------------------------------------------------------------------------------------
void ACoursework_Character::On_Action_Use(const FInputActionValue& value)
{
	if (Interactable_Actors.Num() == 0) {
		return;
	}

	AActor* item = Distance_Count();


	if (AWeapon* weapon = Cast<AWeapon>(item))
		Pickup_Weapon(weapon);

	if (item->ActorHasTag("pick_up")) {
		if (Current_Anim->HasRifle) {
			if(Get_Current_Weapon()->Current_Store < Get_Current_Weapon()->Max_Store)
			Get_Current_Weapon()->Set_Bullet_Store(1);
			UE_LOG(LogTemp, Warning, TEXT("--------------------------------PICK_UP--%i-----------------------"), Get_Current_Weapon()->Get_Bullet_Store());
			item->Destroy();
		}

		}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("--------------------------------ERROR PICK--------------------------------"));
	}

	
}
//------------------------------------------------------------------------------------------------------------
void ACoursework_Character::On_Action_Restor(const FInputActionValue& value) {

	if (Get_Current_Weapon()!= 0) {
		AWeapon* weapon = Get_Current_Weapon();
		if (weapon->Get_Bullet_Store() != 0) {
			weapon->Set_Bullet_Count();
			weapon->Set_Bullet_Store(-1);
			UE_LOG(LogTemp, Warning, TEXT("--------------------------------TAB DETECTED---%i-----------------------------"), weapon->Get_Bullet_Store());
			Saved_Data->Score -= 10;
		}

	}
	//UE_LOG(LogTemp, Warning, TEXT("--------------------------------TAB DETECTED--------------------------------"));
}

AActor* ACoursework_Character::Distance_Count() {
	int i;
	double distance, min_distance;
	AActor* item, * curr_item;
	FVector player_pos, item_pos;


	if (Interactable_Actors.Num() == 1)
	{
		item = Interactable_Actors[0];
	}
	else
	{
		player_pos = GetActorLocation();

		for (i = 0; i < Interactable_Actors.Num(); i++)
		{
			curr_item = Interactable_Actors[i];

			item_pos = curr_item->GetActorLocation();

			distance = FVector::Distance(player_pos, item_pos);

			if (i == 0 || distance < min_distance)
			{
				min_distance = distance;
				item = curr_item;
			}
		}

		Interactable_Actors.Remove(item);
		Decal_Correction(item);
	}
	return item;
}
//------------------------------------------------------------------------------------------------------------
void ACoursework_Character::Pickup_Weapon(AWeapon* weapon)
{
	if (weapon == 0)
		return;

	if (Get_Current_Weapon() != 0) {
		Get_Current_Weapon()->Detach();
		
	}
	ACoursework_PreCharacter::Pickup_Weapon(weapon);
	
	Current_Anim->HasRifle = true;  
	DecalActor->SetActorHiddenInGame(true);

	Saved_Data->Score += 20;
	weapon->CurrentOwner = this;

}
//------------------------------------------------------------------------------------------------------------

void ACoursework_Character::Destroy_Self() {

	ACoursework_PreCharacter::Destroy_Self();
	SetLifeSpan(0.0f);
	Current_Anim->HasRifle = false;
	//Died_Screen_Widget->SetWidgetClass(LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/WB_Death_Screen.WB_Death_Screen_C")));


	//UUserWidget* Widget_Instance1 = Cast<UUserWidget>(Died_Screen_Widget->GetWidget());
	//Died_Screen_Widget->GetWidget()->SetVisibility(ESlateVisibility::Visible);
	//Widget_Instance1->AddToPlayerScreen();

	if (APlayerController* player_controller = Cast<APlayerController>(Controller))
	{
		/*player_controller->SetIgnoreMoveInput(true);
		player_controller->SetIgnoreLookInput(true);*/
		DisableInput(player_controller);
		
		player_controller->SetShowMouseCursor(true);

		//player_controller->SetInputMode(FInputModeUIOnly());

	}

	if (UPrimitiveComponent* prim_component = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}



//------------------------------------------------------------------------------------------------------------

void ACoursework_Character::Check_Inputs() {
	

	UInputDeviceSubsystem* InputDeviceSubsystem = GetGameInstance()->GetEngine()->GetEngineSubsystem<UInputDeviceSubsystem>();
		if (InputDeviceSubsystem->GetMostRecentlyUsedHardwareDevice(GetPlatformUserId()).PrimaryDeviceType == EHardwareDevicePrimaryType::Gamepad) {
			Is_GamePad = true;
			UE_LOG(LogTemp, Warning, TEXT("GAMEPAD"));

		}
		else {
			Is_GamePad = false;
			UE_LOG(LogTemp, Warning, TEXT("KEYBOARD"));

		}
		if (Saved_Data->PlayerCount == 5) {
			Is_GamePad = true;
			UE_LOG(LogTemp, Warning, TEXT("GAMEPAD"));
		}
	if(DecalB)
	DecalB->SetVisibility(Is_GamePad);
}