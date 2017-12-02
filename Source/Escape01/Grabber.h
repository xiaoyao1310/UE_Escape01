// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h" //DrawDebugLine();
#include "PhysicsEngine/PhysicsHandleComponent.h" //PhysicsHandleCompenent
#include "Components/InputComponent.h" //InputComponent
#include "Components/PrimitiveComponent.h" 

#include "Grabber.generated.h" // should always be the last #include 


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE01_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Ray-cast and grab what's in reach
	void Grab();

	// Release what is grabbing
	void Release();

	// Find attched handle
	void FindPhysicsHandleComponent();

	//Setup attached input component
	void SetupInptComponent();
	
	// Get reach Line Start
	FVector GetReachLineStart();

	// Get reach Line End
	FVector GetReachLineEnd();

	// Return hit of first obstacle in reach
	FHitResult GetFirstPhysicsBodyInReach();

};