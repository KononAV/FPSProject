#pragma once

#include "CoreMinimal.h"

#include "MyAnimClass.generated.h"


class ACoursework_Character;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class COURSEWORK_API UMyAnimClass : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMyAnimClass();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rifle") bool HasRifle;  // Переменная для AnimBP для переключения на другой набор анимаций


};