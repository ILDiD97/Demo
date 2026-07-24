// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/WidgetSwitcher.h"
#include "Types/SlateEnums.h"
#include "LessonUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ULessonUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnSettingsClicked();

	UFUNCTION()
	void OnApplySettingsClicked();

	UFUNCTION()
	void OnVSyncChanged(bool bIsChecked);
	
	UFUNCTION()
	void OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	// BindWidget
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ApplyButton;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* VSyncCheckBox;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ResolutionCombo;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;
	
	int32 PendingWidth;
	
	int32 PendingHeight;
};
