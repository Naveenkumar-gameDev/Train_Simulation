// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainCpp.h"
#include "Kismet/GameplayStatics.h"
#include "TrainHUD.h"
// Sets default values
ATrainCpp::ATrainCpp()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrainCpp::BeginPlay()
{
	Super::BeginPlay();
	
	UTrainHUD* TrainHUD = CreateWidget<UTrainHUD>(this, TrainHUDClass);

	if (TrainHUD)
	{
		TrainHUD->AddToViewport();
		TrainHUD->Train = this;
	}
}

// Called every frame
void ATrainCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Track) return;
	
	//Move Train
	currentLocation += (speed * mphValue) * DeltaTime;

	FVector Location = Track->GetLocationAtDistanceAlongSpline(
		currentLocation,
		ESplineCoordinateSpace::World);

	FRotator TargetRotation = Track->GetRotationAtDistanceAlongSpline(
		currentLocation,
		ESplineCoordinateSpace::World);

	FRotator Rotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 0.5f);

	SetActorLocation(Location);
	SetActorRotation(Rotation);
}

// Called to bind functionality to input
void ATrainCpp::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATrainCpp::SetSpeed(float value) 
{
	speed = value;
}

