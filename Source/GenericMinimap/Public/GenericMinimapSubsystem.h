#pragma once

#include "CoreMinimal.h"
#include "GenericMinimapMarker.h"
#include "Subsystems/WorldSubsystem.h"
#include "GenericMinimapSubsystem.generated.h"

class AGenericMinimapManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTeamMarkerAdded, AGenericMinimapMarker*, NewMarker, int32, TeamID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTeamMarkerRemoved, AGenericMinimapMarker*, RemovedMarker, int32, TeamID);

UCLASS()
class GENERICMINIMAP_API UGenericMinimapSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

	// Registers a new marker actor to a specified team
	void RegisterMinimapActor(AGenericMinimapMarker* NewActor, int32 TeamID);

	// Unregisters a marker actor from a specified team
	void UnregisterMinimapActor(AGenericMinimapMarker* ActorToRemove, int32 TeamID);

	// Retrieve all markers for a specified team, Blueprint-callable
	UFUNCTION(BlueprintCallable, Category="Minimap")
	TArray<AGenericMinimapMarker*> GetTeamMarkers(int32 TeamID);

	// Returns the total number of teams
	UFUNCTION(BlueprintCallable, Category = "Minimap")
	int32 GetTeamCount() const;

	// Returns the GenericMinimapManager instance, if available
	UFUNCTION(BlueprintCallable, Category="Minimap")
	AGenericMinimapManager* GetMinimapManager();

	UFUNCTION(BlueprintCallable, Category = "Minimap")
	FVector2D GetPlayableAreaSize();

	UFUNCTION(BlueprintCallable, Category = "Minimap")
	FVector2D GetPlayableAreaLocation();

	// Blueprint-assignable delegate for notifying when a team marker is added
	UPROPERTY(BlueprintAssignable, Category = "Minimap")
	FOnTeamMarkerAdded OnTeamMarkerAdded;

	// Blueprint-assignable delegate for notifying when a team marker is added
	UPROPERTY(BlueprintAssignable, Category = "Minimap")
	FOnTeamMarkerAdded OnTeamMarkerRemoved;

private:
	// Map of team ID to array of team members' markers
	TMap<int32, TArray<AGenericMinimapMarker*>> TeamMarkers;

	UPROPERTY(Transient)
	AGenericMinimapManager* CachedMinimapManager;

};
