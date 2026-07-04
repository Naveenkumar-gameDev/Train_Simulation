// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Signal.generated.h"

UCLASS()
class TRAIN_API ASignal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASignal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Base;

public:

	UPROPERTY(EditAnywhere)
	float heightValue;

	UPROPERTY(EditAnywhere)
	float forbackValue;

	UPROPERTY(EditAnywhere)
	float OffSetValue;

	FVector startPos;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void MoveLeftRight(float value);

	UFUNCTION()
	void MoveUpDown(float value);

	UFUNCTION()
	void MoveForBack(float value);

	UFUNCTION(BlueprintNativeEvent, Category = "SignalLight")
	void SetActiveAllLights(bool value);

	UFUNCTION(BlueprintNativeEvent, Category = "SignalLight")
	void SetAciveRedLight(bool value);

	UFUNCTION(BlueprintNativeEvent, Category = "SignalLight")
	void SetAciveGreenLight(bool value);
};
