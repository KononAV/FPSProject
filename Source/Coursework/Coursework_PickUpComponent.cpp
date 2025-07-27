#include "Coursework_PickUpComponent.h"

//------------------------------------------------------------------------------------------------------------
UCoursework_PickUpComponent::UCoursework_PickUpComponent()
{
	SphereRadius = 32.0f;  // Радиус сферы коллизий
}
//------------------------------------------------------------------------------------------------------------
void UCoursework_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UCoursework_PickUpComponent::On_Sphere_Begin_Overlap);  // Регистрируем событие пересечения (Overlap Event)
}
//------------------------------------------------------------------------------------------------------------
void UCoursework_PickUpComponent::On_Sphere_Begin_Overlap(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_comp, int other_body_index, bool from_sweep, const FHitResult &sweep_result)
{
	// Если пересеклись с персонажем от первого лица
	ACoursework_Character *character = Cast<ACoursework_Character>(other_actor);

	if (character != 0)
	{
		On_Pick_Up.Broadcast(character);  // Уведомить о том, что актора подбирают
		OnComponentBeginOverlap.RemoveAll(this);  // Снимаем регистрацию с события пересечения (Overlap Event), чтобы оно больше не триггерилось
	}
}//rifle
//------------------------------------------------------------------------------------------------------------
