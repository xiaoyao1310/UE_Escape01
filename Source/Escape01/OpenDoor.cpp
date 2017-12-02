// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Owner = GetOwner();
	if (!PressurePlate)
		UE_LOG(LogTemp, Error, TEXT("PressurePlate of %s is missing!"), *GetOwner()->GetName());
}

void UOpenDoor::OpenDoor()
{
	//Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
	OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	//Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	OnCloseRequest.Broadcast();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (GetTotalActorMassOnPlate() > TriggerMass)
	{
		OpenDoor();
	}
	else
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalActorMassOnPlate()
{
	float TotalMass = 0.f;

	/// Find all actors overlapping 
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate)
		return TotalMass;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	/// Add their masses
	for (auto& Actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping actor: %s"), *(Actor->GetName()));
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}