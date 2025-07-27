#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Coursework_Character.h"
#include "Coursework_PickUpComponent.generated.h"

//------------------------------------------------------------------------------------------------------------
// ќбъ€вление делегата, вызываемого, когда кто-то подберЄт этот предмет.
// ѕерсонаж, подбирающий этот объект, будет передан как параметр уведомлени€.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Pick_Up, ACoursework_Character*, PickUpCharacter);
//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COURSEWORK_API UCoursework_PickUpComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UCoursework_PickUpComponent();

	UPROPERTY(BlueprintAssignable, Category = "Interaction") FOn_Pick_Up On_Pick_Up;  // ƒелегат, на который может подписатьс€ кто угодно, чтобы получать это событие

protected:
	virtual void BeginPlay() override;

	/** Code for when something overlaps this component */
	UFUNCTION() void On_Sphere_Begin_Overlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_comp, int other_body_index, bool from_sweep, const FHitResult& sweep_result);
};
//------------------------------------------------------------------------------------------------------------
