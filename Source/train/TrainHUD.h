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
    void OnSpinBoxChanged(float Value);

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

public:
    UPROPERTY(BlueprintReadWrite)
    ASignal* currentSignal;

#pragma endregion
};