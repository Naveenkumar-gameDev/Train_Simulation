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

    if (offBTN)
        offBTN->OnClicked.AddDynamic(this, &UTrainHUD::OnOffBtnClicked);
    if (redBTN)
        redBTN->OnClicked.AddDynamic(this, &UTrainHUD::OnRedBtnClicked);
    if (greenBTN)
        greenBTN->OnClicked.AddDynamic(this, &UTrainHUD::OnGreenBtnClicked);

    if (resetParaBTN)
        resetParaBTN->OnClicked.AddDynamic(this, &UTrainHUD::OnRestParaBtnClicked);

    if (signalComboBox)
        signalComboBox->OnSelectionChanged.AddDynamic(this, &UTrainHUD::OnSignalSelected);
        

    if (heightSpinBox)
    {
        heightSpinBox->OnValueChanged.AddDynamic(this, &UTrainHUD::OnHeightSpinBoxChanged);
        heightSpinBox->SetMinValue(minStepValue);
        heightSpinBox->SetMaxValue(maxStepValue);

        heightSpinBox->SetMinSliderValue(minStepValue);
        heightSpinBox->SetMaxSliderValue(maxStepValue);

        //heightSpinBox->SetMinFractionalDigits(0);
        //heightSpinBox->SetMaxFractionalDigits(0);

        heightSpinBox->SetDelta(1);

        heightSpinBox->SetValue(0);
    }
    if (forBackSpinBox)
    {
        forBackSpinBox->OnValueChanged.AddDynamic(this, &UTrainHUD::OnForBackSpinBoxChanged);
        forBackSpinBox->SetMinValue(minStepValue);
        forBackSpinBox->SetMaxValue(maxStepValue);

        forBackSpinBox->SetMinSliderValue(minStepValue);
        forBackSpinBox->SetMaxSliderValue(maxStepValue);

        //heightSpinBox->SetMinFractionalDigits(0);
        //heightSpinBox->SetMaxFractionalDigits(0);

        forBackSpinBox->SetDelta(1);

        forBackSpinBox->SetValue(0);
    }
    if (offSetSpinBox)
    {
        offSetSpinBox->OnValueChanged.AddDynamic(this, &UTrainHUD::OnOffSetSpinBoxChanged);
        offSetSpinBox->SetMinValue(minStepValue);
        offSetSpinBox->SetMaxValue(maxStepValue);

        offSetSpinBox->SetMinSliderValue(minStepValue);
        offSetSpinBox->SetMaxSliderValue(maxStepValue);

        //heightSpinBox->SetMinFractionalDigits(0);
        //heightSpinBox->SetMaxFractionalDigits(0);

        offSetSpinBox->SetDelta(1);

        offSetSpinBox->SetValue(0);
    }


#pragma endregion

    return true;
}

void UTrainHUD::NativeTick(const FGeometry& myGeometry, float InDelta)
{
    UpdateSignalDistance();

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
    if (!currentSignal || !offSetSpinBox) return;
    currentSignal->MoveLeftRight((stepValue*100) * -1);

    offSetSpinBox->SetValue(currentSignal->OffSetValue / 100);
}

void UTrainHUD::RightBtnClicked()
{
    if (!currentSignal || !offSetSpinBox) return;
    currentSignal->MoveLeftRight((stepValue * 100));

    offSetSpinBox->SetValue(currentSignal->OffSetValue / 100);
}

void UTrainHUD::UpBtnClicked()
{
    if (!currentSignal || !heightSpinBox) return;
    currentSignal->MoveUpDown((stepValue * 100) * -1);

    heightSpinBox->SetValue(currentSignal->heightValue / 100);
}

void UTrainHUD::DownBtnClicked()
{
    if (!currentSignal || !heightSpinBox) return;
        currentSignal->MoveUpDown((stepValue * 100));

        heightSpinBox->SetValue(currentSignal->heightValue / 100);
}

void UTrainHUD::ForBtnClicked()
{
    if (!currentSignal || !forBackSpinBox) return;
    currentSignal->MoveForBack((stepValue * 100) * -1);

    forBackSpinBox->SetValue(currentSignal->forbackValue / 100);
}

void UTrainHUD::BackBtnClicked()
{
    if (!currentSignal || !forBackSpinBox) return;
    currentSignal->MoveForBack((stepValue * 100));

    forBackSpinBox->SetValue(currentSignal->forbackValue / 100);
}

void UTrainHUD::OnHeightSpinBoxChanged(float value)
{
    value = FMath::Clamp(value, minStepValue, maxStepValue);
    value *= 100;
    if (heightSpinBox && currentSignal)
    {
        FVector newPos = FVector(currentSignal->GetActorLocation().X, currentSignal->GetActorLocation().Y, currentSignal->startPos.Z + value);
        currentSignal->SetActorLocation(newPos);
        currentSignal->heightValue = value;
    }
}

void UTrainHUD::OnForBackSpinBoxChanged(float value)
{
    value = FMath::Clamp(value, minStepValue, maxStepValue);
    value *= 100;
    if (forBackSpinBox && currentSignal)
    {
        FVector newPos = FVector(currentSignal->GetActorLocation().X, currentSignal->startPos.Y + value, currentSignal->GetActorLocation().Z );
        currentSignal->SetActorLocation(newPos);
        currentSignal->forbackValue = value;
    }
}

void UTrainHUD::OnOffSetSpinBoxChanged(float value)
{
    value = FMath::Clamp(value, minStepValue, maxStepValue);
    value *= 100;
    if (offSetSpinBox && currentSignal)
    {
        FVector newPos = FVector(currentSignal->startPos.X + value , currentSignal->GetActorLocation().Y , currentSignal->GetActorLocation().Z);
        currentSignal->SetActorLocation(newPos);
        currentSignal->OffSetValue = value;
    }
}

void UTrainHUD::OnOffBtnClicked()
{
    if (!currentSignal) return;

    currentSignal->SetActiveAllLights(false);

    redLightImage->SetVisibility(ESlateVisibility::Hidden);
    greenLightImage->SetVisibility(ESlateVisibility::Hidden);

    lightSelectedImage->SetRenderTranslation(FVector2D(0, 0));
    //lightSelectedImage->SetColorAndOpacity(FLinearColor(0.014f, 0.533f, 0.651f, 1.0f));

    currentSignal->currentAspect = ESignalAspect::Off;
}

void UTrainHUD::OnRedBtnClicked()
{
    if (!currentSignal) return;

    currentSignal->SetAciveRedLight(true);
    currentSignal->SetAciveGreenLight(false);

    redLightImage->SetVisibility(ESlateVisibility::Visible);
    greenLightImage->SetVisibility(ESlateVisibility::Hidden);

    lightSelectedImage->SetRenderTranslation(FVector2D(58.5f, 0));
    //lightSelectedImage->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));

    currentSignal->currentAspect = ESignalAspect::Red;
}

void UTrainHUD::OnGreenBtnClicked()
{
    if (!currentSignal) return;

    currentSignal->SetAciveRedLight(false);
    currentSignal->SetAciveGreenLight(true);

    redLightImage->SetVisibility(ESlateVisibility::Hidden);
    greenLightImage->SetVisibility(ESlateVisibility::Visible);

    lightSelectedImage->SetRenderTranslation(FVector2D(117, 0));
    //lightSelectedImage->SetColorAndOpacity(FLinearColor::Green);

    currentSignal->currentAspect = ESignalAspect::Green;
}

void UTrainHUD::OnRestParaBtnClicked()
{
    if (!currentSignal) return;

    OnOffBtnClicked();

    offSetSpinBox->SetValue(0);
    heightSpinBox->SetValue(0);
    forBackSpinBox->SetValue(0);

    OnOffSetSpinBoxChanged(0);
    OnHeightSpinBoxChanged(0);
    OnForBackSpinBoxChanged(0);

}

void UTrainHUD::OnSignalSelected(FString SelectedItem, ESelectInfo::Type SelectedType)
{
    for (ASignal* signal : Train->SignalArray)
    {
        if (signal->ID == SelectedItem)
        {
            currentSignal = signal;
            break;
        }
    }

    offSetSpinBox->SetValue(currentSignal->OffSetValue/100);
    heightSpinBox->SetValue(currentSignal->heightValue / 100);
    forBackSpinBox->SetValue(currentSignal->forbackValue / 100);

    switch (currentSignal->currentAspect)
    {
    case ESignalAspect::Off:
        OnOffBtnClicked();
        break;
    case ESignalAspect::Red:
        OnRedBtnClicked();
        break;
    case ESignalAspect::Green:
        OnGreenBtnClicked();
        break;
    }
}

#pragma endregion

#pragma region Speed Distance


void UTrainHUD::UpdateSignalDistance()
{
    if (!currentSignal || !Train) return;
    FVector A = Train->GetActorLocation();
    FVector B = currentSignal->GetActorLocation();

    float distance = (A.Y - B.Y) / 100;

    distanceTXT->SetText(FText::AsNumber(FMath::Abs(distance)));


    float SpeedMS = Train->speed * 0.447f;

    if (SpeedMS > KINDA_SMALL_NUMBER)
    {
        float Time = distance / SpeedMS;
        readingTXT->SetText(FText::AsNumber(Time));
    }
    else
    {
        readingTXT->SetText(FText::FromString(TEXT("--")));
    }
}

#pragma endregion