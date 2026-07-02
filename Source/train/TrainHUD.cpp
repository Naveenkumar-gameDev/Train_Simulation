// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainHUD.h"

bool UTrainHUD::Initialize()
{
    bool Success = Super::Initialize();

    if (!Success)
        return false;

    if (speedSlider)
    {
        speedSlider->OnValueChanged.AddDynamic(this,
            &UTrainHUD::OnSliderValueChanged);
    }

    return true;
}

void UTrainHUD::OnSliderValueChanged(float value)
{

    if (Train)
    {
        // Slider range: 0-1
        // Convert to 0-2000

        float Speed = value * 2000.0f;

        Train->SetSpeed(Speed);
    }
}