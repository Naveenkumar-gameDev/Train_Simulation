// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SplineComponent.h"
#include "TrainCpp.generated.h"

UCLASS()
class TRAIN_API ATrainCpp : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATrainCpp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, Category = "Train")
	USplineComponent* Track;

	UPROPERTY(EditAnywhere)
	float speed;

	float currentLocation=0.0f;

	static constexpr float mphValue= 44.704f;

};
