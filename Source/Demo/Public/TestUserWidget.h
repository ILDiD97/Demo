// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/WidgetSwitcher.h"
#include "Types/SlateEnums.h"
#include "TestUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UTestUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	UFUNCTION()
	void OnStartedClicked();
	
	UFUNCTION()
	void OnSettingClicked();
	
	UFUNCTION()
	void OnApplyButton();
	
	UFUNCTION()
	void OnVSyncCheckBox(bool bIsChecked);
	
	UFUNCTION()
	void OnResolutionBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ApplyButton;
	
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ResolutionCombo;
	
	UPROPERTY(meta = (BindWidget))
	UCheckBox* VSyncCheckBox;
	
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;
};
