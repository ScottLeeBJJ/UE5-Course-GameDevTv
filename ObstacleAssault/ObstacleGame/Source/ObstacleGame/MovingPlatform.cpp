#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	//Debug method
	UE_LOG(LogTemp, Display, TEXT("Your message"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move platform forwards
		// Get current location
	FVector CurrentLocation = GetActorLocation();

		// Add vector to that location
	CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;

		// Set the location
	SetActorLocation(CurrentLocation);

	// Send platform back if gone too far
		// Check how far we've moved
	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);

		// Reverse direction of motion if gone too far
	if (DistanceMoved > MoveDistance)
	{
		float OverShoot = DistanceMoved - MoveDistance;
		UE_LOG(LogTemp, Display, TEXT("Platform overshot by %f"), OverShoot);
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}

}
