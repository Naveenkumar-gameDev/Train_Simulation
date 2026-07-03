#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Components/SpinBox.h"
#include "Components/Button.h"
#include "TrainCpp.h"
#include "Signal.h"
#include "TrainHUD.generated.h"

UCLASS()
class TRAIN_API UTrainHUD : public UUserWidget
{
    GENERATED_BODY()

#pragma region SpeedControl
protected:

    virtual bool Initialize() override;

    UPROPERTY(meta = (BindWidget))
    USlider* speedSlider;

    UPROPERTY(meta = (BindWidget))
    USpinBox* speedSpinBox;

    UFUNCTION()
    void OnSliderChanged(float Value);

    UFUNCTION()
    void OnSpeedSpinBoxChanged(float Value);

public:

    UPROPERTY(BlueprintReadWrite)
    ATrainCpp* Train;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float maxTrainSpeed = 80.0f;

private:

    bool bUpdatingUI = false;

#pragma endregion

#pragma region Signal control
protected:

    UPROPERTY(EditAnywhere)
    float moveValue;

    UPROPERTY(EditAnywhere)
    float maxMoveValue;

    UPROPERTY(meta=(BindWidget))
    UButton* leftBTN;

    UPROPERTY(meta = (BindWidget))
    UButton* rightBTN;

    UPROPERTY(meta = (BindWidget))
    UButton* upBTN;

    UPROPERTY(meta = (BindWidget))
    UButton* downBTN;

    UPROPERTY(meta = (BindWidget))
    UButton* forBTN;

    UPROPERTY(meta = (BindWidget))
    UButton* backBTN;

    UPROPERTY(meta = (BindWidget))
    USpinBox* heightSpinBox;

    UPROPERTY(meta = (BindWidget))
    USpinBox* forBackSpinBox;

    UPROPERTY(meta = (BindWidget))
    USpinBox* offSetSpinBox;

    UFUNCTION()
    void LeftBtnClicked();
    UFUNCTION()
    void RightBtnClicked();
    UFUNCTION()
    void UpBtnClicked();
    UFUNCTION()
    void DownBtnClicked();
    UFUNCTION()
    void ForBtnClicked();
    UFUNCTION()
    void BackBtnClicked();

    UFUNCTION()
    void OnHeightSpinBoxChanged(float value);

    UFUNCTION()
    void OnForBackSpinBoxChanged(float value);

    UFUNCTION()
    void OnOffSetSpinBoxChanged(float value);

public:
    UPROPERTY(BlueprintReadWrite)
    ASignal* currentSignal;

#pragma endregion
};