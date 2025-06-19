// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StartLocation = FVector::ZeroVector;
	EventCount = 0;
	TotalDistance = 0.0f;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	Move();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AMyActor::Step()
{
	int32 StepX = FMath::RandRange(0, 1);
	int32 StepY = FMath::RandRange(0, 1);

	return FVector(StepX, StepY, 0);
}

float AMyActor::CalculateDistance(const FVector& Start, const FVector& End)
{
	float dx = Start.X - End.X;
	float dy = Start.Y - End.Y;
	return FMath::Sqrt(dx * dx + dy * dy);
}

bool AMyActor::CreateEvent()
{
	int32 RandomValue = FMath::RandRange(1, 100);
	return RandomValue <= 50; // 50% chance to create an event
}

void AMyActor::Move()
{
	FVector CurrentLocation = StartLocation;

	for (int32 i = 0; i < 10; ++i)
	{
		FVector StepVector = Step();
		FVector NextLocation = CurrentLocation + StepVector;

		float Distance = CalculateDistance(CurrentLocation, NextLocation);
		TotalDistance += Distance;

		bool bEventOccurred = CreateEvent();
		if (bEventOccurred)
		{
			EventCount++;
		}

		UE_LOG(LogTemp, Warning, TEXT("Step %d: From (%f, %f) to (%f, %f), Distance: %f, Event: %s"),
			i + 1,
			CurrentLocation.X, CurrentLocation.Y,
			NextLocation.X, NextLocation.Y,
			Distance,
			bEventOccurred ? TEXT("YES") : TEXT("NO")
		);

		CurrentLocation = NextLocation;
	}

	UE_LOG(LogTemp, Warning, TEXT("Total Distance Moved: %f"), TotalDistance);
	UE_LOG(LogTemp, Warning, TEXT("Total Events Triggered: %d"), EventCount);
}

