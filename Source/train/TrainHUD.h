#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Components/SpinBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ComboBoxString.h"
#include <Components/HierarchicalInstancedStaticMeshComponent.h>
#include "TrainCpp.h"
#include "Signal.h"
#include "TrainHUD.generated.h"

UCLASS()
class TRAIN_API UTrainHUD : public UUserWidget
{
    GENERATED_BODY()

protected:

    virtual bool Initialize() override;

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

#pragma region Speed Control

protected:

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
    float stepValue;

    UPROPERTY(EditAnywhere)
    float minStepValue;

    UPROPERTY(EditAnywhere)
    float maxStepValue;

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

    UPROPERTY(meta=(BindWidget))
    UButton* offBTN;

    UPROPERTY(meta = (BindWidget))
    UButton* redBTN;

    UPROPERTY(meta = (BindWidget))
    UButton* greenBTN;

    UPROPERTY(meta = (BindWidget))
    UImage* redLightImage;

    UPROPERTY(meta=(BindWidget))
    UImage* greenLightImage;

    UPROPERTY(meta = (BindWidget))
    UImage* lightSelectedImage;

    UPROPERTY(meta = (BindWidget))
    UButton* resetParaBTN;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* signalComboBox;

    UPROPERTY(meta= (BindWidget))
    UButton* vegOnOff1_BTN;

    UPROPERTY(meta=(BindWidget))
    UImage* vegBar1_Image;

    UPROPERTY(meta= (BindWidget))
    UButton* vegOnOff2_BTN;

    UPROPERTY(meta=(BindWidget))
    UImage* vegBar2_Image;

    UPROPERTY(meta= (BindWidget))
    UButton* vegOnOff3_BTN;

    UPROPERTY(meta=(BindWidget))
    UImage* vegBar3_Image;

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

    UFUNCTION()
    void OnOffBtnClicked();

    UFUNCTION()
    void OnRedBtnClicked();

    UFUNCTION()
    void OnGreenBtnClicked();

    UFUNCTION()
    void OnRestParaBtnClicked();

    UFUNCTION()
    void OnSignalSelected(FString SelectedItem, ESelectInfo::Type SelectedType);

    UFUNCTION()
    void OnVeg1OnOFfBtnClicked();

    UFUNCTION()
    void OnVeg2OnOFfBtnClicked();

    UFUNCTION()
    void OnVeg3OnOFfBtnClicked();

public:
    UPROPERTY(BlueprintReadWrite)
    ASignal* currentSignal;

    UHierarchicalInstancedStaticMeshComponent* Veg1HISM;

    UPROPERTY(BlueprintReadOnly)
    bool isVeg1On = true;

    UHierarchicalInstancedStaticMeshComponent* Veg2HISM;

    UPROPERTY(BlueprintReadOnly)
    bool isVeg2On = true;

    UHierarchicalInstancedStaticMeshComponent* Veg3HISM;

    UPROPERTY(BlueprintReadOnly)
    bool isVeg3On = true;

#pragma endregion

#pragma region Signal Distance

    UPROPERTY(meta = (BindWidget))
    USpinBox* distanceSpinBox;

    UFUNCTION()
    void OnDistanceChanged(float Value);

    UFUNCTION()
    void UpdateSignalDistance();




#pragma endregion
};