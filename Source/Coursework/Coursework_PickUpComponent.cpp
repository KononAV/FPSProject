#include "Coursework_PickUpComponent.h"

//------------------------------------------------------------------------------------------------------------
UCoursework_PickUpComponent::UCoursework_PickUpComponent()
{
	SphereRadius = 32.0f;  // ������ ����� ��������
}
//------------------------------------------------------------------------------------------------------------
void UCoursework_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UCoursework_PickUpComponent::On_Sphere_Begin_Overlap);  // ������������ ������� ����������� (Overlap Event)
}
//------------------------------------------------------------------------------------------------------------
void UCoursework_PickUpComponent::On_Sphere_Begin_Overlap(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_comp, int other_body_index, bool from_sweep, const FHitResult &sweep_result)
{
	// ���� ����������� � ���������� �� ������� ����
	ACoursework_Character *character = Cast<ACoursework_Character>(other_actor);

	if (character != 0)
	{
		On_Pick_Up.Broadcast(character);  // ��������� � ���, ��� ������ ���������
		OnComponentBeginOverlap.RemoveAll(this);  // ������� ����������� � ������� ����������� (Overlap Event), ����� ��� ������ �� ������������
	}
}//rifle
//------------------------------------------------------------------------------------------------------------
