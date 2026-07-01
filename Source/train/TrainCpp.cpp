// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainCpp.h"
#include "Kismet/GameplayStatics.h"

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
	
}

// Called every frame
void ATrainCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Track)
	{
		UE_LOG(LogTemp, Display, TEXT("Error"));
		return;
	}

	//Move Train
	currentLocation += speed * DeltaTime;

	FVector location = Track->GetLocationAtDistanceAlongSpline(currentLocation, ESplineCoordinateSpace::World);

	FRotator rotation = Track->GetRotationAtDistanceAlongSpline(currentLocation, ESplineCoordinateSpace::World);

	SetActorLocation(location);
	SetActorRotation(rotation);
}

// Called to bind functionality to input
void ATrainCpp::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

