#include "TrainHUD.h"

bool UTrainHUD::Initialize()
{
    bool Success = Super::Initialize();

    if (!Success)
        return false;

    if (speedSlider)
    {
        speedSlider->OnValueChanged.AddDynamic(
            this,
            &UTrainHUD::OnSliderChanged);

        speedSlider->SetValue(0.f);
    }

    if (speedSpinBox)
    {
        speedSpinBox->OnValueChanged.AddDynamic(
            this,
            &UTrainHUD::OnSpeedSpinBoxChanged);

        speedSpinBox->SetMinValue(0);
        speedSpinBox->SetMaxValue(maxTrainSpeed);

        speedSpinBox->SetMinSliderValue(0);
        speedSpinBox->SetMaxSliderValue(maxTrainSpeed);

        speedSpinBox->SetMinFractionalDigits(0);
        speedSpinBox->SetMaxFractionalDigits(0);

        speedSpinBox->SetDelta(1);

        speedSpinBox->SetValue(0);
    }

    if (leftBTN)
        leftBTN->OnClicked.AddDynamic(this, &UTrainHUD::LeftBtnClicked);
    if (rightBTN)
        rightBTN->OnClicked.AddDynamic(this, &UTrainHUD::RightBtnClicked);
    if (upBTN)
        upBTN->OnClicked.AddDynamic(this, &UTrainHUD::UpBtnClicked);
    if (downBTN)
        downBTN->OnClicked.AddDynamic(this, &UTrainHUD::DownBtnClicked);
    if (forBTN)
        forBTN->OnClicked.AddDynamic(this, &UTrainHUD::ForBtnClicked);
    if (backBTN)
        backBTN->OnClicked.AddDynamic(this, &UTrainHUD::BackBtnClicked);

    return true;
}
#pragma region SpeedControl
void UTrainHUD::OnSliderChanged(float Value)
{
    if (bUpdatingUI)
        return;

    bUpdatingUI = true;

    float Speed = Value * maxTrainSpeed;

    if (speedSpinBox)
    {
        speedSpinBox->SetValue(FMath::RoundToInt(Speed));
    }

    if (Train)
    {
        Train->SetSpeed(Speed);
    }

    bUpdatingUI = false;
}

void UTrainHUD::OnSpeedSpinBoxChanged(float Value)
{
    if (bUpdatingUI)
        return;

    bUpdatingUI = true;

    Value = FMath::Clamp(Value, 0.f, maxTrainSpeed);

    if (speedSlider)
    {
        speedSlider->SetValue(Value / maxTrainSpeed);
    }

    if (Train)
    {
        Train->SetSpeed(Value);
    }

    bUpdatingUI = false;
}
#pragma endregion

#pragma region Signal Control


void UTrainHUD::LeftBtnClicked()
{
    currentSignal->MoveLeftRight(moveValue * -1);
}

void UTrainHUD::RightBtnClicked()
{
    currentSignal->MoveLeftRight(moveValue);
}

void UTrainHUD::UpBtnClicked()
{
    currentSignal->MoveUpDown(moveValue * -1);
}

void UTrainHUD::DownBtnClicked()
{
    currentSignal->MoveUpDown(moveValue);
}

void UTrainHUD::ForBtnClicked()
{
    currentSignal->MoveForBack(moveValue * -1);
}

void UTrainHUD::BackBtnClicked()
{
    currentSignal->MoveForBack(moveValue);
}

void UTrainHUD::OnHeightSpinBoxChanged()
{
    /*if (heightSpinBox)
    {
        FVector 
        currentSignal->SetActorLocation()
    }*/
}

#pragma endregion