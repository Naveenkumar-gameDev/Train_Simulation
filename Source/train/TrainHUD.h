#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Components/SpinBox.h"
#include "TrainCpp.h"
#include "TrainHUD.generated.h"

UCLASS()
class TRAIN_API UTrainHUD : public UUserWidget
{
    GENERATED_BODY()

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
};