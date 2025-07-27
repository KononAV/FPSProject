#include "CourseworkWeaponComponent.h"
#include "Coursework.h"
#include "Coursework_Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//------------------------------------------------------------------------------------------------------------
UCourseworkWeaponComponent::UCourseworkWeaponComponent()
{
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);  // �������� �� ��������� �� ��������� �� ����� ������ �������
}
//------------------------------------------------------------------------------------------------------------
void UCourseworkWeaponComponent::AttachWeapon(ACoursework_Character* target_character)
{
	Character = target_character;
	if (Character == 0)
		return;

	// ������� ������ � ���������
	FAttachmentTransformRules attachment_rules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->Mesh_1P, attachment_rules, FName(TEXT("GripPoint")));


	// ������������� ������� ��������
	if (APlayerController* player_controller = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer()))
			input_subsystem->AddMappingContext(FireMappingContext, 1);  // ������������� ��������� �������� � 1, ��� ��� ��� ��������� �������� Jump ��������� Fire ��� ������������� ����� � ���������

		if (UEnhancedInputComponent* enhanced_input_component = Cast<UEnhancedInputComponent>(player_controller->InputComponent))
			enhanced_input_component->BindAction(FireAction, ETriggerEvent::Triggered, this, &UCourseworkWeaponComponent::Fire);
	}
}
//------------------------------------------------------------------------------------------------------------
void UCourseworkWeaponComponent::Fire()
{
	if (Character == 0 || Character->GetController() == 0)
		return;

	// �������� ���������� ��������
	if (ProjectileClass != 0)
	{
		if (UWorld* world = GetWorld())
		{
			APlayerController* player_controller = Cast<APlayerController>(Character->GetController());
			FRotator spawn_rotation = player_controller->PlayerCameraManager->GetCameraRotation();

			// �.�. MuzzleOffset ����������� � ������������ ������, ��� ���� ��������� � ������� ������������ ������, ��� ������� �� ������� ��������� ��� ����, ����� �������� �������� ������� ����
			FVector spawn_location = GetOwner()->GetActorLocation() + spawn_rotation.RotateVector(MuzzleOffset);

			// ������������� ��������� ������������ ��� ������
			FActorSpawnParameters actor_spawn_params;
			actor_spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			world->SpawnActor<ACoursework_Projectile>(ProjectileClass, spawn_location, spawn_rotation, actor_spawn_params);  // ������� ������ �� ����
		}
	}

	if (FireSound != 0)
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());  // �������� ��������� ���� ��������, ���� �� ������

	if (FireAnimation != 0)
	{
		if (UAnimInstance* anim_instance = Character->Mesh_1P->GetAnimInstance())
			anim_instance->Montage_Play(FireAnimation, 1.0f);  // �������� ��������� ��������, ���� ��� �������
	}
}
//------------------------------------------------------------------------------------------------------------
void UCourseworkWeaponComponent::EndPlay(const EEndPlayReason::Type end_play_reason)
{
	if (Character == 0)
		return;

	if (APlayerController* player_controller = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer()))
			input_subsystem->RemoveMappingContext(FireMappingContext);
	}
}
//------------------------------------------------------------------------------------------------------------
