#include "TrainHUD.h"

bool UTrainHUD::Initialize()
{
    bool Success = Super::Initialize();

    if (!Success)
        return false;

#pragma region SpeedControl

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
#pragma endregion

#pragma region SignalCotrol

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

    if (heightSpinBox)
    {
        heightSpinBox->OnValueChanged.AddDynamic(this, &UTrainHUD::OnHeightSpinBoxChanged);
        heightSpinBox->SetMinValue(0);
        heightSpinBox->SetMaxValue(maxMoveValue);

        heightSpinBox->SetMinSliderValue(0);
        heightSpinBox->SetMaxSliderValue(maxMoveValue);

        //heightSpinBox->SetMinFractionalDigits(0);
        //heightSpinBox->SetMaxFractionalDigits(0);

        heightSpinBox->SetDelta(1);

        heightSpinBox->SetValue(0);
    }
    if (forBackSpinBox)
    {
        forBackSpinBox->OnValueChanged.AddDynamic(this, &UTrainHUD::OnForBackSpinBoxChanged);
        forBackSpinBox->SetMinValue(0);
        forBackSpinBox->SetMaxValue(maxMoveValue);

        forBackSpinBox->SetMinSliderValue(0);
        forBackSpinBox->SetMaxSliderValue(maxMoveValue);

        //heightSpinBox->SetMinFractionalDigits(0);
        //heightSpinBox->SetMaxFractionalDigits(0);

        forBackSpinBox->SetDelta(1);

        forBackSpinBox->SetValue(0);
    }
    if (offSetSpinBox)
    {
        offSetSpinBox->OnValueChanged.AddDynamic(this, &UTrainHUD::OnOffSetSpinBoxChanged);
        offSetSpinBox->SetMinValue(0);
        offSetSpinBox->SetMaxValue(maxMoveValue);

        offSetSpinBox->SetMinSliderValue(0);
        offSetSpinBox->SetMaxSliderValue(maxMoveValue);

        //heightSpinBox->SetMinFractionalDigits(0);
        //heightSpinBox->SetMaxFractionalDigits(0);

        offSetSpinBox->SetDelta(1);

        offSetSpinBox->SetValue(0);
    }


#pragma endregion

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
    if(currentSignal)
        currentSignal->MoveLeftRight(moveValue * -1);
}

void UTrainHUD::RightBtnClicked()
{
    if (currentSignal)
        currentSignal->MoveLeftRight(moveValue);
}

void UTrainHUD::UpBtnClicked()
{
    if (currentSignal)
        currentSignal->MoveUpDown(moveValue * -1);
}

void UTrainHUD::DownBtnClicked()
{
    if (currentSignal)
        currentSignal->MoveUpDown(moveValue);
}

void UTrainHUD::ForBtnClicked()
{
    if (currentSignal)
        currentSignal->MoveForBack(moveValue * -1);
}

void UTrainHUD::BackBtnClicked()
{
    if (currentSignal)
        currentSignal->MoveForBack(moveValue);
}

void UTrainHUD::OnHeightSpinBoxChanged(float value)
{
    value = FMath::Clamp(value, 0.0f, maxMoveValue);
    if (heightSpinBox && currentSignal)
    {
        FVector newPos = FVector(currentSignal->startPos.X, currentSignal->startPos.Y, currentSignal->startPos.Z + value);
        currentSignal->SetActorLocation(newPos);
        currentSignal->heightValue = value;
    }
}

void UTrainHUD::OnForBackSpinBoxChanged(float value)
{
    value = FMath::Clamp(value, 0.0f, maxMoveValue);
    if (forBackSpinBox && currentSignal)
    {
        FVector newPos = FVector(currentSignal->startPos.X, currentSignal->startPos.Y + value, currentSignal->startPos.Z );
        currentSignal->SetActorLocation(newPos);
        currentSignal->forbackValue = value;
    }
}

void UTrainHUD::OnOffSetSpinBoxChanged(float value)
{
    value = FMath::Clamp(value, 0.0f, maxMoveValue);
    if (offSetSpinBox && currentSignal)
    {
        FVector newPos = FVector(currentSignal->startPos.X + value , currentSignal->startPos.Y , currentSignal->startPos.Z);
        currentSignal->SetActorLocation(newPos);
        currentSignal->OffSetValue = value;
    }
}



#pragma endregion