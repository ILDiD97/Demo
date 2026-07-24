// Fill out your copyright notice in the Description page of Project Settings.


#include "LessonUserWidget.h"

#include "GameFramework/GameUserSettings.h"


void ULessonUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (StartButton)
		StartButton->OnClicked.AddDynamic(this, &ULessonUserWidget::OnStartClicked);

	if (SettingsButton)
		SettingsButton->OnClicked.AddDynamic(this, &ULessonUserWidget::OnSettingsClicked);

	if (ApplyButton)
		ApplyButton->OnClicked.AddDynamic(this, &ULessonUserWidget::OnApplySettingsClicked);

	if (VSyncCheckBox)
		VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &ULessonUserWidget::OnVSyncChanged);

	if (ResolutionCombo)
		ResolutionCombo->OnSelectionChanged.AddDynamic(this, &ULessonUserWidget::OnResolutionChanged);

	// Popolare la combo risoluzioni
	ResolutionCombo->ClearOptions();
	ResolutionCombo->AddOption("1280x720");
	ResolutionCombo->AddOption("1920x1080");
	ResolutionCombo->AddOption("2560x1440");
}

void ULessonUserWidget::OnStartClicked()
{
	MenuSwitcher->SetActiveWidgetIndex(0);
}

void ULessonUserWidget::OnSettingsClicked()
{
	MenuSwitcher->SetActiveWidgetIndex(1);
}

void ULessonUserWidget::OnApplySettingsClicked()
{
	UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();

	FString Selected = ResolutionCombo->GetSelectedOption();
	FString Left, Right;
	Selected.Split("x", &Left, &Right);

	int32 Width = FCString::Atoi(*Left);
	int32 Height = FCString::Atoi(*Right);

	Settings->SetScreenResolution(FIntPoint(Width, Height));
	Settings->ApplySettings(false);
	Settings->SaveSettings();
}

void ULessonUserWidget::OnVSyncChanged(bool bIsChecked)
{
	UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
	Settings->SetVSyncEnabled(bIsChecked);
	Settings->ApplySettings(false);
	Settings->SaveSettings();
}

void ULessonUserWidget::OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	// Esempio: SelectedItem = "1920x1080"
	FString WidthStr, HeightStr;

	// Divide la stringa in due parti
	if (SelectedItem.Split("x", &WidthStr, &HeightStr))
	{
		// Converte in interi
		PendingWidth  = FCString::Atoi(*WidthStr);
		PendingHeight = FCString::Atoi(*HeightStr);

		UE_LOG(LogTemp, Warning, TEXT("Risoluzione selezionata: %dx%d"),
			   PendingWidth, PendingHeight);
		UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
		Settings->SetScreenResolution(FIntPoint(PendingWidth, PendingHeight));
		Settings->ApplySettings(false);
		Settings->SaveSettings();
	}
}
