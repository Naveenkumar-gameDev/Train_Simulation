// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
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

	UFUNCTION()
	void OnSliderValueChanged(float value);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATrainCpp* Train;

};
