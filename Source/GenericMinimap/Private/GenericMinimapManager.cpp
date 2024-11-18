#include "GenericMinimapManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "UObject/ConstructorHelpers.h"

AGenericMinimapManager::AGenericMinimapManager()
{
	PrimaryActorTick.bCanEverTick = false;
	bAlwaysRelevant =true;

	// Initialize the billboard as the root component
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;
	Billboard->SetHiddenInGame(true); // Only visible in the editor

	// Initialize the plane component and attach it to the billboard
	PlayableAreaPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayableAreaPlane"));
	PlayableAreaPlane->SetupAttachment(Billboard);

	// Set a default plane mesh (can be replaced in the editor)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("/Engine/BasicShapes/Plane"));
	if (PlaneMesh.Succeeded())
	{
		PlayableAreaPlane->SetStaticMesh(PlaneMesh.Object);
		PlayableAreaPlane->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PlayableAreaPlane->SetCastShadow(false);
		PlayableAreaPlane->SetHiddenInGame(true);
	}

	// Default values
	PlayableArenaSize = 1.0f;
}

void AGenericMinimapManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Apply size to the plane by scaling in X and Y
	PlayableAreaPlane->SetWorldScale3D(FVector(PlayableArenaSize, PlayableArenaSize, 1.0f));

	// Apply material to the plane, if specified
	if (PlaneMaterial)
	{
		PlayableAreaPlane->SetMaterial(0, PlaneMaterial);
	}
}
