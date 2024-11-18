#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericMinimapManager.generated.h"

UCLASS()
class GENERICMINIMAP_API AGenericMinimapManager : public AActor
{
	GENERATED_BODY()

public:
	AGenericMinimapManager();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Billboard component as the root, to help locate this manager in the editor
	UPROPERTY(VisibleAnywhere, Category = "Minimap")
	UBillboardComponent* Billboard;

	// Plane to represent playable area
	UPROPERTY(VisibleAnywhere, Category = "Minimap")
	UStaticMeshComponent* PlayableAreaPlane;

	// Material for the plane
	UPROPERTY(EditAnywhere, Category = "Minimap")
	UMaterialInterface* PlaneMaterial;

	// Size of the plane to represent the playable area
	UPROPERTY(EditAnywhere, Category = "Minimap", meta = (ClampMin = "1.0", UIMin = "1.0"))
	float PlayableArenaSize;
};



