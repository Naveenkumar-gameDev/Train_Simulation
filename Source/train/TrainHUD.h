// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Components/SpinBox.h"
#include "TrainCpp.h"
#include "TrainHUD.generated.h"

/**
 * 
 */
UCLASS()
class TRAIN_API UTrainHUD : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	virtual bool Initialize() override;

	UPROPERTY(meta=(BindWidget))
	USlider* speedSlider;

	UPROPERTY(meta = (BindWidget))
	USpinBox* speedSpinBox;

	UFUNCTION() 
	void OnSliderValueChanged(float value);


	UFUNCTION()
	void OnSliderChanged(float Value);

	UFUNCTION()
	void OnSpinBoxChanged(float Value);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATrainCpp* Train;


private:
	bool bUpdatingUI = false;

};
