#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InputMappingContext.h"
#include "Coursework_Game_Mode.generated.h"

//-------------------------------------------------------------
UCLASS(minimalapi)
class ACoursework_Game_Mode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACoursework_Game_Mode();

	UFUNCTION(BlueprintCallable, Category = "UTIL")void Creat_Second_Player();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> DefaultMappingContextRef;
};
//-------------------------------------------------------------


