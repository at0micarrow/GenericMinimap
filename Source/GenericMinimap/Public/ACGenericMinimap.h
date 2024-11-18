#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACGenericMinimap.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GENERICMINIMAP_API UACGenericMinimap : public UActorComponent
{
	GENERATED_BODY()

public:
	UACGenericMinimap();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Checks for an instance of the manager in the level
	bool IsManagerInstancePresent();
private:
	// Function to clean up the marker on character destruction
	UFUNCTION()
	void HandleCharacterDestruction(AActor* Owner);
	// Blueprint-callable function to spawn and register the marker
	UFUNCTION(BlueprintCallable, Category="Minimap")
	void SpawnAndRegisterMarker(int32 NewTeamID);

	// Team ID to which this actor belongs
	UPROPERTY(EditAnywhere, Category="Minimap")
	int32 TeamID = -1; // Default team ID, can be modified per player
	// Subsystem pointer for easier access
	UPROPERTY()
	class UGenericMinimapSubsystem* MinimapSubsystem;
	// Reference to the spawned marker
	UPROPERTY()
	class AGenericMinimapMarker* PlayerMarkerInstance = nullptr;

public:
	// Blueprint-callable function to set the team ID
	UFUNCTION(BlueprintCallable, Category="Minimap")
	void SetTeamID(int32 NewTeamID);
};