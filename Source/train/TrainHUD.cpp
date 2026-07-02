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

    if (speedSpinBox)
    {
        speedSpinBox->OnValueChanged.AddDynamic(
            this,
            &UTrainHUD::OnSpinBoxChanged);

        speedSpinBox->SetMinValue(0);
        speedSpinBox->SetMaxValue(80);
        speedSpinBox->SetMinSliderValue(0);
        speedSpinBox->SetMaxSliderValue(80);
        speedSpinBox->SetDelta(1);
        speedSpinBox->SetValue(0);
    }

    return true;
}

void UTrainHUD::OnSliderValueChanged(float value)
{

    if (Train)
    {

        float Speed = value;

        Train->SetSpeed(Speed);
    }
}

void UTrainHUD::OnSliderChanged(float Value)
{
    if (bUpdatingUI)
        return;

    bUpdatingUI = true;

    int32 Speed = FMath::RoundToInt(Value * 80.0f);

    speedSpinBox->SetValue(Speed);

    // Train->SetSpeed(Speed);

    bUpdatingUI = false;
}

void UTrainHUD::OnSpinBoxChanged(float Value)
{
    if (bUpdatingUI)
        return;

    bUpdatingUI = true;

    Value = FMath::Clamp(Value, 0.f, 80.f);

    speedSlider->SetValue(Value / 80.f);

    // Train->SetSpeed(Value);

    bUpdatingUI = false;
}


//void UTrainHUD::OnSpeedTextChanged(const FText& Text)
//{
//    FString Input = Text.ToString();
//
//    FString Result;
//
//    // Keep numbers only
//    for (TCHAR Ch : Input)
//    {
//        if (FChar::IsDigit(Ch))
//        {
//            Result.AppendChar(Ch);
//        }
//    }
//
//    // Maximum 2 digits
//    if (Result.Len() > 2)
//    {
//        Result = Result.Left(2);
//    }
//
//    // Clamp to 80
//    if (!Result.IsEmpty())
//    {
//        int32 Value = FCString::Atoi(*Result);
//
//        Value = FMath::Clamp(Value, 0, 80);
//
//        Result = FString::FromInt(Value);
//
//        speedSlider->SetValue(Value / 80.f);
//    }
//
//    // Prevent recursive updates
//    if (Result != Input)
//    {
//        speedTextBox->SetText(FText::FromString(Result));
//    }
//}
//
//void UTrainHUD::OnSpeedTextCommitted(
//    const FText& Text,
//    ETextCommit::Type CommitMethod)
//{
//    int32 Value = FCString::Atoi(*Text.ToString());
//
//    Value = FMath::Clamp(Value, 0, 80);
//
//    speedTextBox->SetText(FText::AsNumber(Value));
//
//    speedSlider->SetValue(Value / 80.f);
//
//    // Train->SetSpeed(Value);
//}
