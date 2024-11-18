#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericMinimapMarker.generated.h"

UCLASS()
class GENERICMINIMAP_API AGenericMinimapMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	AGenericMinimapMarker();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};

