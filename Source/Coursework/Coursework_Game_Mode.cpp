// Copyright Epic Games, Inc. All Rights Reserved.

#include "Coursework_Game_Mode.h"
#include "Coursework_Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/GameInstance.h"
#include "CourseWork_Save_Data.h"
#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"


ACoursework_Game_Mode::ACoursework_Game_Mode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	;
	UE_LOG(LogTemp, Warning, TEXT("GameMOD_________________________"));
	/*UCourseWork_Save_Data::Ser_PlayerCount();
	UCourseWork_Save_Data::Set_Kills()*/;

}
void ACoursework_Game_Mode::Creat_Second_Player()
{
	FString error;
	ULocalPlayer* NewPlayer =GetGameInstance()->CreateLocalPlayer(5, error, true);
	DefaultMappingContextRef = TSoftObjectPtr<UInputMappingContext>(FSoftObjectPath(TEXT("/Game/FirstPerson/Input/IMC_Default.IMC_Default")));
	
	UInputMappingContext* LoadedContext = DefaultMappingContextRef.LoadSynchronous();
	NewPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->AddMappingContext(LoadedContext,0);


}