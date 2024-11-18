#include "GenericMinimapSubsystem.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GenericMinimapManager.h" // Include the header for the manager
#include "Kismet/GameplayStatics.h"


void UGenericMinimapSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	TeamMarkers.Empty();
	CachedMinimapManager = nullptr; // Initialize the cached manager to null
}

void UGenericMinimapSubsystem::Deinitialize()
{
	TeamMarkers.Empty();
	CachedMinimapManager = nullptr; // Clear the cached manager on deinitialization
	Super::Deinitialize();
}

void UGenericMinimapSubsystem::Tick(float DeltaTime)
{
	// Update logic for each team if necessary
}

TStatId UGenericMinimapSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UGenericMinimapSubsystem, STATGROUP_Tickables);
}

void UGenericMinimapSubsystem::RegisterMinimapActor(AGenericMinimapMarker* NewMarker, int32 TeamID)
{
	if (!TeamMarkers.Contains(TeamID))
	{
		// Initialize the array for this team if it doesn't exist
		TeamMarkers.Add(TeamID, TArray<AGenericMinimapMarker*>());
	}

	// Check if the actor is already in the team array to avoid duplicates
	if (!TeamMarkers[TeamID].Contains(NewMarker))
	{
		TeamMarkers[TeamID].Add(NewMarker);

		// Broadcast the delegate to notify listeners in Blueprint
		OnTeamMarkerAdded.Broadcast(NewMarker, TeamID);
	}
}

void UGenericMinimapSubsystem::UnregisterMinimapActor(AGenericMinimapMarker* MarkerToRemove, int32 TeamID)
{
	if (TArray<AGenericMinimapMarker*>* TeamArray = TeamMarkers.Find(TeamID))
	{
		TeamArray->Remove(MarkerToRemove);
		// Broadcast the delegate to notify listeners in Blueprint
		OnTeamMarkerRemoved.Broadcast(MarkerToRemove, TeamID);
	}
}

TArray<AGenericMinimapMarker*> UGenericMinimapSubsystem::GetTeamMarkers(int32 TeamID)
{
	if (TArray<AGenericMinimapMarker*>* FoundMarkers = TeamMarkers.Find(TeamID))
	{
		FoundMarkers->RemoveAll([](AActor* Marker) {
			return !IsValid(Marker);
		});
		return *FoundMarkers;
	}
	return TArray<AGenericMinimapMarker*>();  // Return empty array if no team found
}

int32 UGenericMinimapSubsystem::GetTeamCount() const
{
	// Return the number of unique team entries in TeamMarkers
	return TeamMarkers.Num();
}

AGenericMinimapManager* UGenericMinimapSubsystem::GetMinimapManager()
{
	if (!CachedMinimapManager)
	{
		// Find all actors of type AGenericMinimapManager in the world
		TArray<AActor*> FoundManagers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGenericMinimapManager::StaticClass(), FoundManagers);

		// If we found at least one manager, cache the first one
		if (FoundManagers.Num() > 0)
		{
			CachedMinimapManager = Cast<AGenericMinimapManager>(FoundManagers[0]);
		}

		// If no valid manager was found, log a warning
		if (!CachedMinimapManager)
		{
			UE_LOG(LogTemp, Warning, TEXT("No GenericMinimapManager instance found in the level!"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No GenericMinimapManager instance found in the level!"));
		}
	}

	// Return the cached manager if valid
	return CachedMinimapManager;
}

FVector2D UGenericMinimapSubsystem::GetPlayableAreaSize()
{
	AGenericMinimapManager* MinimapManager = GetMinimapManager();
	if (MinimapManager && MinimapManager->PlayableAreaPlane)
	{
		// Multiply by 100 to convert the size from meters to centimeters
		return FVector2D(MinimapManager->PlayableArenaSize * 100.0f, MinimapManager->PlayableArenaSize * 100.0f);
	}
	// Return zero if no valid playable area found
	return FVector2D(0.0f, 0.0f);
}

FVector2D UGenericMinimapSubsystem::GetPlayableAreaLocation()
{
	AGenericMinimapManager* MinimapManager = GetMinimapManager();
	if (MinimapManager && MinimapManager->PlayableAreaPlane)
	{
		FVector Location = MinimapManager->PlayableAreaPlane->GetComponentLocation();
		return FVector2D(Location.X, Location.Y);
	}

	return FVector2D::ZeroVector;
}