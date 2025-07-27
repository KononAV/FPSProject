// Fill out your copyright notice in the Description page of Project Settings.


#include "Coursework_MenuWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"

void UCoursework_MenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	Texts={ FB_Text,SB_Text,TB_Text };
	Buttons={ First_Button,Second_Button,Third_Button };
	Button_Text = 
	{ 
		FText::FromString(TEXT("Start")),
		FText::FromString(TEXT("Option")),
		FText::FromString(TEXT("Exit")) 
	};

	//////Delegates
	FScriptDelegate Start_Delegate;
	Start_Delegate.BindUFunction(this, FName("Start"));
	FScriptDelegate Option_Delegate;
	Option_Delegate.BindUFunction(this, FName("Option"));
	FScriptDelegate Exit_Delegate;
	Exit_Delegate.BindUFunction(this, FName("Exit"));
	/////////////////

	Button_Delegates = {
		Start_Delegate,
		Option_Delegate,
		Exit_Delegate
	};

	Root_Canvas = NewObject<UCanvasPanel>(this);

	
	WidgetTree->RootWidget = Root_Canvas;

	
	//Root_Canvas = NewObject<UCanvasPanel>(this);
	if (Root_Canvas) {
		if (Texts.Num() == Buttons.Num()) {

			for (int i = 0; i < Texts.Num(); i++) {

				Buttons[i] = NewObject<UButton>(this);
				Texts[i] = NewObject<UTextBlock>(this);
				Texts[i]->SetText(Button_Text[i]);
				UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(Buttons[i]->Slot);
				if (ButtonSlot)
				{
					// Устанавливаем позицию и размер кнопки
					ButtonSlot->SetPosition(FVector2D(100.f, 100.f + i * 60.f)); // Позиция кнопки на экране
					ButtonSlot->SetSize(FVector2D(200.f, 50.f)); // Размер кнопки

					// Добавляем кнопку в CanvasPanel
					Root_Canvas->AddChild(Buttons[i]);
				}
				
				
				Buttons[i]->OnClicked.Add(Button_Delegates[i]);

				UCanvasPanelSlot* TextSlot = Cast<UCanvasPanelSlot>(Texts[i]->Slot);
				if (TextSlot)
				{
					TextSlot->SetPosition(FVector2D(110.f, 110.f + i * 60.f)); // Позиция текста (рядом с кнопкой)
					TextSlot->SetSize(FVector2D(180.f, 30.f)); // Размер текста

					// Добавляем текст в CanvasPanel
					Root_Canvas->AddChild(Texts[i]);
				}

				
				
			}
		}
	}
	//Buttons[0]->OnClicked.Add
	
}
void UCoursework_MenuWidget::Start()
{
	
	/*if (TargetLevel.IsValid())
	{
		FString LevelName = TargetLevel.GetAssetName();
		UGameplayStatics::OpenLevel(WorldContextObject, FName(*LevelName));
	}
	else if (TargetLevel.ToSoftObjectPath().IsValid())
	{
		FString LevelName = TargetLevel.ToSoftObjectPath().GetAssetName();
		UGameplayStatics::OpenLevel(WorldContextObject, FName(*LevelName));
	}*/
	

}
void UCoursework_MenuWidget::Option( )
{
		UE_LOG(LogTemp, Warning, TEXT("Button Clicked"));
	

}
void UCoursework_MenuWidget::Exit( )
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
	

}