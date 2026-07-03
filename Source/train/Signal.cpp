// Fill out your copyright notice in the Description page of Project Settings.


#include "Signal.h"

// Sets default values
ASignal::ASignal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create DefaultSceneRoot
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = SceneRoot;

	greenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GreenMesh"));
	greenMesh->SetupAttachment(SceneRoot);

	redMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RedMesh"));
	redMesh->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void ASignal::BeginPlay()
{
	Super::BeginPlay();
	
	startPos = GetActorLocation();
}

// Called every frame
void ASignal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASignal::MoveLeftRight(float value)
{
	FVector newPos = FVector(GetActorLocation().X + value, GetActorLocation().Y, GetActorLocation().Z);
	SetActorLocation(newPos);

	OffSetValue += value;
}

void ASignal::MoveUpDown(float value)
{
	FVector newPos = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + value);
	SetActorLocation(newPos);

	heightValue += value;
}

void ASignal::MoveForBack(float value)
{
	FVector newPos = FVector(GetActorLocation().X , GetActorLocation().Y + value, GetActorLocation().Z);
	SetActorLocation(newPos);

	forbackValue += value;
}


