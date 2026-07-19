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
        heightSpinBox->SetMinValue(minHeightStepValue);
        heightSpinBox->SetMaxValue(maxHeightStepValue);

        heightSpinBox->SetMinSliderValue(minHeightStepValue);
        heightSpinBox->SetMaxSliderValue(maxHeightStepValue);

        heightSpinBox->SetMinFractionalDigits(0);
        heightSpinBox->SetMaxFractionalDigits(2);

        heightSpinBox->SetDelta(1);

        heightSpinBox->SetValue(3.30);
    }
    if (forBackSpinBox)
    {
        forBackSpinBox->OnValueChanged.AddDynamic(this, &UTrainHUD::OnForBackSpinBoxChanged);
        forBackSpinBox->SetMinValue(minForStepValue);
        forBackSpinBox->SetMaxValue(maxForStepValue);

        forBackSpinBox->SetMinSliderValue(minForStepValue);
        forBackSpinBox->SetMaxSliderValue(maxForStepValue);

        forBackSpinBox->SetMinFractionalDigits(0);
        forBackSpinBox->SetMaxFractionalDigits(2);

        forBackSpinBox->SetDelta(1);

        forBackSpinBox->SetValue(0);
    }
    if (offSetSpinBox)
    {
        offSetSpinBox->OnValueChanged.AddDynamic(this, &UTrainHUD::OnOffSetSpinBoxChanged);
        offSetSpinBox->SetMinValue(minOffSetStepValue);
        offSetSpinBox->SetMaxValue(maxOffSetStepValue);

        offSetSpinBox->SetMinSliderValue(minOffSetStepValue);
        offSetSpinBox->SetMaxSliderValue(maxOffSetStepValue);

        offSetSpinBox->SetMinFractionalDigits(0);
        offSetSpinBox->SetMaxFractionalDigits(2);

        offSetSpinBox->SetDelta(1);

        offSetSpinBox->SetValue(2.12);
    }


#pragma endregion

#pragma region Vegetation

    if (vegOnOff1_BTN)
        vegOnOff1_BTN->OnClicked.AddDynamic(this, &UTrainHUD::OnVeg1OnOFfBtnClicked);

    if (vegOnOff2_BTN)
        vegOnOff2_BTN->OnClicked.AddDynamic(this, &UTrainHUD::OnVeg2OnOFfBtnClicked);

    if (vegOnOff3_BTN)
        vegOnOff3_BTN->OnClicked.AddDynamic(this, &UTrainHUD::OnVeg3OnOFfBtnClicked);

#pragma endregion

#pragma region  Speed Distance
    if (distanceSpinBox)
    {
        distanceSpinBox->OnValueChanged.AddDynamic(
            this,
            &UTrainHUD::OnDistanceChanged
        );

        distanceSpinBox->SetMinValue(0.0f);
        distanceSpinBox->SetMaxValue(900.0f);

        distanceSpinBox->SetMinSliderValue(0.0f);
        distanceSpinBox->SetMaxSliderValue(900.0f);

        distanceSpinBox->SetMinFractionalDigits(0);
        distanceSpinBox->SetMaxFractionalDigits(0);

        distanceSpinBox->SetDelta(1.0f);
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

void UTrainHUD::OnHeightSpinBoxChanged(float Value)
{
    if (!currentSignal ||
        !currentSignal->diff ||
        !currentSignal->lightMeshRef)
        return;

    Value = FMath::Clamp(
        Value,
        minHeightStepValue,
        maxHeightStepValue
    );

    float DesiredHeightCM = Value * 100.0f;

    float CurrentHeightCM =
        currentSignal->lightMeshRef->GetComponentLocation().Z -
        currentSignal->diff->GetActorLocation().Z;

    // How much the signal needs to move
    float Difference = DesiredHeightCM - CurrentHeightCM;

    FVector NewLocation = currentSignal->GetActorLocation();

    NewLocation.Z += Difference;

    currentSignal->SetActorLocation(NewLocation);

    currentSignal->heightValue = DesiredHeightCM;
}

void UTrainHUD::OnForBackSpinBoxChanged(float value)
{
    value = FMath::Clamp(value, minForStepValue, maxForStepValue);
    value *= 100;
    if (forBackSpinBox && currentSignal)
    {
        FVector newPos = FVector(currentSignal->GetActorLocation().X, currentSignal->startPos.Y + value, currentSignal->GetActorLocation().Z );
        currentSignal->SetActorLocation(newPos);
        currentSignal->forbackValue = value;
    }
}
void UTrainHUD::OnOffSetSpinBoxChanged(float Value)
{
    if (!currentSignal || !currentSignal->diff)
        return;

    Value = FMath::Clamp(
        Value,
        minOffSetStepValue,
        maxOffSetStepValue
    );

    float OffsetCM = Value * 100.0f;

    FVector NewLocation = currentSignal->GetActorLocation();

    NewLocation.X =
        currentSignal->diff->GetActorLocation().X +
        (OffsetCM * currentSignal->OffsetDirection);

    currentSignal->SetActorLocation(NewLocation);

    currentSignal->OffSetValue = OffsetCM;
}

//void UTrainHUD::OnOffSetSpinBoxChanged(float value)
//{
//    if (!currentSignal || !currentSignal->diff)
//        return;
//
//    value = FMath::Clamp(
//        value,
//        minOffSetStepValue,
//        maxOffSetStepValue
//    );
//
//    // Convert meters to centimeters
//    float OffsetInCM = value * 100.0f;
//
//    FVector NewPos = currentSignal->GetActorLocation();
//
//    float DiffX = currentSignal->diff->GetActorLocation().X;
//
//    // Signal position required to maintain entered offset
//    NewPos.X = DiffX - OffsetInCM;
//
//    currentSignal->SetActorLocation(NewPos);
//
//    currentSignal->OffSetValue = OffsetInCM;
//}
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

    //currentSignal->SetAciveGreenLight(false);
    currentSignal->SetAciveRedLight(true);

    redLightImage->SetVisibility(ESlateVisibility::Visible);
    greenLightImage->SetVisibility(ESlateVisibility::Hidden);

    lightSelectedImage->SetRenderTranslation(FVector2D(58.5f, 0));
    //lightSelectedImage->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));

    currentSignal->currentAspect = ESignalAspect::Red;
}

void UTrainHUD::OnGreenBtnClicked()
{
    if (!currentSignal) return;

    //currentSignal->SetAciveRedLight(false);
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

    offSetSpinBox->SetValue(2.12);
    heightSpinBox->SetValue(3.3);
    forBackSpinBox->SetValue(0);

    OnOffSetSpinBoxChanged(2.12);
    OnHeightSpinBoxChanged(3.3);
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
    if (!currentSignal || !Train || !distanceSpinBox)
        return;

    FVector TrainLocation = Train->GetActorLocation();
    FVector SignalLocation = currentSignal->GetActorLocation();

    float Distance = FMath::Abs(
        (TrainLocation.Y - SignalLocation.Y) / 100.0f
    );

    Distance = FMath::Clamp(Distance, 0.0f, 900.0f);

    bUpdatingUI = true;

    distanceSpinBox->SetValue(
        FMath::RoundToInt(Distance)
    );

    bUpdatingUI = false;
}

void UTrainHUD::OnDistanceChanged(float Value)
{
    if (bUpdatingUI)
        return;

    if (!currentSignal || !Train || !Train->Track)
        return;

    Value = FMath::Clamp(Value, 0.0f, 900.0f);

    // Convert entered meters to Unreal centimeters
    float DistanceInCM = Value * 100.0f;

    // Find signal's distance from the start of the spline
    float SignalSplineDistance =
        Train->Track->GetDistanceAlongSplineAtLocation(
            currentSignal->GetActorLocation(),
            ESplineCoordinateSpace::World
        );

    // Place train requested distance BEFORE signal
    float NewTrainDistance = SignalSplineDistance - DistanceInCM;

    // Prevent going before start of spline
    NewTrainDistance = FMath::Max(0.0f, NewTrainDistance);

    // This is enough because Tick() uses currentLocation
    Train->currentLocation = NewTrainDistance;
    FRotator TargetRotation = Train->Track->GetRotationAtDistanceAlongSpline(
        Train->currentLocation,
        ESplineCoordinateSpace::World);

    Train->SetActorRotation(TargetRotation);
    // Stop train after snapping
    Train->SetSpeed(0.0f);

    UE_LOG(LogTemp, Warning,
        TEXT("Signal: %f | Input: %f | Train: %f"),
        SignalSplineDistance,
        DistanceInCM,
        NewTrainDistance
    );
}
#pragma endregion

#pragma region Vegetation
void UTrainHUD::OnVeg1OnOFfBtnClicked()
{
    if (!Veg1HISM) return;
    if (isVeg1On)
    {
        Veg1HISM->SetVisibility(false);
        vegOnOff1_BTN->SetBackgroundColor(FLinearColor::Black);
        vegBar1_Image->SetRenderTranslation(FVector2D(-49.0f, 0.0f));
        isVeg1On = false;
    }
    else
    {
        Veg1HISM->SetVisibility(true);
        vegOnOff1_BTN->SetBackgroundColor(FLinearColor(0.0f, 1.0f, 1.0f));
        vegBar1_Image->SetRenderTranslation(FVector2D(49.0f, 0.0f));
        isVeg1On = true;
    }
}

void UTrainHUD::OnVeg2OnOFfBtnClicked()
{
    if (!Veg2HISM) return;
    if (isVeg2On)
    {
        Veg2HISM->SetVisibility(false);
        vegOnOff2_BTN->SetBackgroundColor(FLinearColor::Black);
        vegBar2_Image->SetRenderTranslation(FVector2D(-49.0f, 0.0f));
        isVeg2On = false;
    }
    else
    {
        Veg2HISM->SetVisibility(true);
        vegOnOff2_BTN->SetBackgroundColor(FLinearColor(0.0f, 1.0f, 1.0f));
        vegBar2_Image->SetRenderTranslation(FVector2D(49.0f, 0.0f));
        isVeg2On = true;
    }
}

void UTrainHUD::OnVeg3OnOFfBtnClicked()
{
    if (!Veg3HISM) return;
    if (isVeg3On)
    {
        Veg3HISM->SetVisibility(false);
        vegOnOff3_BTN->SetBackgroundColor(FLinearColor::Black);
        vegBar3_Image->SetRenderTranslation(FVector2D(-49.0f, 0.0f));
        isVeg3On = false;
    }
    else
    {
        Veg3HISM->SetVisibility(true);
        vegOnOff3_BTN->SetBackgroundColor(FLinearColor(0.0f, 1.0f, 1.0f));
        vegBar3_Image->SetRenderTranslation(FVector2D(49.0f, 0.0f));
        isVeg3On = true;
    }
}
#pragma endregion