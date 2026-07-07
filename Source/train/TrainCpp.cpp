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

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (PC)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
	
	TrainHUD = CreateWidget<UTrainHUD>(GetWorld(), TrainHUDClass);

	if (TrainHUD)
	{
		TrainHUD->AddToViewport();
		TrainHUD->Train = this;
	}

	GetWorld()->GetTimerManager().SetTimer(
		DelayHandle,
		this,
		&ATrainCpp::DelayFinished,
		0.2f,
		false
	);
}

void ATrainCpp::DelayFinished()
{
	AActor* Track_BP = UGameplayStatics::GetActorOfClass(
		GetWorld(),
		TrackClass);

	if (Track_BP)
	{
		Track = Track_BP->FindComponentByClass<USplineComponent>();
	}
	


	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		ASignal::StaticClass(),
		FoundActors
	);

	// Clear previous references
	SignalArray.Empty();

	// Convert AActor* to ASignal*
	for (AActor* Actor : FoundActors)
	{
		if (ASignal* Signal = Cast<ASignal>(Actor))
		{
			SignalArray.Add(Signal);
		}
	}


	/*ASignal* Signal = Cast<ASignal>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ASignal::StaticClass()));*/

	if (TrainHUD)
	{
		for (ASignal* Signal : SignalArray)
		{
			if(Signal->ID==TEXT("SS141"))
				TrainHUD->currentSignal = Signal;
		}
	}
	if (TrainHUD)
	{
		AActor* vegetaion = Cast<AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), VegetationClass));
		TrainHUD->VegHISM=vegetaion->FindComponentByClass<UHierarchicalInstancedStaticMeshComponent>();

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

	FRotator Rotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 5);

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

