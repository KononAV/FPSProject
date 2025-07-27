#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Coursework_MenuWidget.generated.h"

UCLASS()
class COURSEWORK_API UCoursework_MenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// Канвас
	UPROPERTY(meta = (BindWidget)) UCanvasPanel* Root_Canvas; // Канвас
	UPROPERTY(EditAnywhere, Category = "Level") TSoftObjectPtr<UWorld> TargetLevel;
	UPROPERTY(EditAnywhere, Category = "Level") UObject* WorldContextObject;

	// Привязанные кнопки
	UPROPERTY(meta = (BindWidget)) UButton* First_Button;
	UPROPERTY(meta = (BindWidget)) UButton* Second_Button;
	UPROPERTY(meta = (BindWidget)) UButton* Third_Button;

	// Привязанные текстовые блоки
	UPROPERTY(meta = (BindWidget)) UTextBlock* FB_Text;
	UPROPERTY(meta = (BindWidget)) UTextBlock* SB_Text;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TB_Text;


	UFUNCTION(BlueprintCallable)void Start( );
	UFUNCTION(BlueprintCallable)void Option( );

	UFUNCTION(BlueprintCallable)void Exit( );


	// Массивы для кнопок и текстов
	TArray<UTextBlock*> Texts;
	TArray<UButton*> Buttons;
	TArray<FText> Button_Text;

	TArray<FScriptDelegate> Button_Delegates;
};
