#include "GenericMinimapMarker.h"

AGenericMinimapMarker::AGenericMinimapMarker()
{
	PrimaryActorTick.bCanEverTick = true;
	bAlwaysRelevant = true;

	// Initialize and assign the root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->SetupAttachment(RootComponent);
}

void AGenericMinimapMarker::BeginPlay()
{
	Super::BeginPlay();
}

void AGenericMinimapMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


