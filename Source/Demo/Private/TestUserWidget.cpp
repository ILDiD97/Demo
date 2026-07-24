// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUserWidget.h"

#include "GameFramework/GameUserSettings.h"

void UTestUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (StartButton)
		StartButton->OnClicked.AddDynamic(this, &UTestUserWidget::OnStartedClicked);
	
	if (SettingsButton)
		SettingsButton->OnClicked.AddDynamic(this, &UTestUserWidget::OnSettingClicked);
	
	if (ApplyButton)
		ApplyButton->OnClicked.AddDynamic(this, & UTestUserWidget::OnApplyButton);
	
	if (VSyncCheckBox)
		VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &UTestUserWidget::OnVSyncCheckBox);

	if (ResolutionCombo)
		ResolutionCombo->OnSelectionChanged.AddDynamic(this, &UTestUserWidget::OnResolutionBoxChanged);

	ResolutionCombo->ClearOptions();
	ResolutionCombo->AddOption("1280x720");
	ResolutionCombo->AddOption("1920x1080");
	ResolutionCombo->AddOption("2560x1440");
}

void UTestUserWidget::OnStartedClicked()
{
	MenuSwitcher->SetActiveWidgetIndex(0);
}

void UTestUserWidget::OnSettingClicked()
{
	MenuSwitcher->SetActiveWidgetIndex(1);
}

void UTestUserWidget::OnApplyButton()
{
	UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
	Settings->ApplySettings(false);
	Settings->SaveSettings();
}

void UTestUserWidget::OnVSyncCheckBox(bool bIsChecked)
{
	UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
	Settings->SetVSyncEnabled(bIsChecked);
	Settings->ApplySettings(true);
}

void UTestUserWidget::OnResolutionBoxChanged(
	FString SelectedItem, 
	ESelectInfo::Type SelectionType)
{
	FString WidthStr, HeightStr;
	
	if (SelectedItem.Split("x", &WidthStr, &HeightStr))
	{
		int32 PendingWidth, PendingHeight;
		PendingWidth = FCString::Atoi(*WidthStr);
		PendingHeight = FCString::Atoi(*HeightStr);
		
		UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
		Settings->SetScreenResolution(FIntPoint(PendingWidth, PendingHeight));
		Settings->ApplySettings(true);
	}
}
