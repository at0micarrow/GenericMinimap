#include "ACGenericMinimap.h"

#include "AssetTypeCategories.h"
#include "GenericMinimapManager.h"
#include "GenericMinimapSubsystem.h"
#include "GenericMinimapMarker.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"


UACGenericMinimap::UACGenericMinimap()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UACGenericMinimap::BeginPlay()
{
	Super::BeginPlay();
	if (!IsManagerInstancePresent())
	{
		UE_LOG(LogTemp, Warning, TEXT("No instance of GenericMinimapManager found in the level. Minimap component will be inactive."));
		return;
	}
	// Bind the destruction function to handle cleanup
	if (GetOwner())
	{
		{
			GetOwner()->OnDestroyed.AddDynamic(this, &UACGenericMinimap::HandleCharacterDestruction);
		}
	}
}

void UACGenericMinimap::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Clean up marker if it exists
	if (MinimapSubsystem && PlayerMarkerInstance)
	{
		MinimapSubsystem->UnregisterMinimapActor(PlayerMarkerInstance, TeamID);
	}

	Super::EndPlay(EndPlayReason);
}

void UACGenericMinimap::HandleCharacterDestruction(AActor* Owner)
{
	if (MinimapSubsystem && PlayerMarkerInstance)
	{
		MinimapSubsystem->UnregisterMinimapActor(PlayerMarkerInstance, TeamID);
	}
}

bool UACGenericMinimap::IsManagerInstancePresent()
{
	UWorld* World = GetWorld();
	if (!World) return false;

	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(World, AGenericMinimapManager::StaticClass(), FoundManagers);
	MinimapSubsystem = World->GetSubsystem<UGenericMinimapSubsystem>();

	// Return true if at least one instance exists
	return FoundManagers.Num() > 0;
}

void UACGenericMinimap::SpawnAndRegisterMarker(int32 NewTeamID)
{
	if (!IsManagerInstancePresent())
	{
		UE_LOG(LogTemp, Warning, TEXT("No instance of GenericMinimapManager found in the level. Minimap component will be inactive."));
		return;
	}
	// Existing spawn and register logic
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();

		PlayerMarkerInstance = World->SpawnActor<AGenericMinimapMarker>(AGenericMinimapMarker::StaticClass(), SpawnParams);
		if (PlayerMarkerInstance)
		{
			TeamID = NewTeamID;
			//MinimapMarker->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
			PlayerMarkerInstance->K2_AttachToActor(GetOwner(),NAME_None,EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,EAttachmentRule::KeepWorld, false);
			// Register the new marker in the subsystem
			MinimapSubsystem = World->GetSubsystem<UGenericMinimapSubsystem>();
			if (MinimapSubsystem)
			{
				MinimapSubsystem->RegisterMinimapActor(PlayerMarkerInstance, TeamID);
			}
		}
	}
}

void UACGenericMinimap::SetTeamID(int32 NewTeamID)
{
	if (TeamID != NewTeamID && PlayerMarkerInstance)
	{
		if (UWorld* World = GetWorld())
		{
			if (MinimapSubsystem)
			{
				// Unregister from the old team
				MinimapSubsystem->UnregisterMinimapActor(PlayerMarkerInstance, TeamID);
				// Update the team ID and register the marker in the new team
				TeamID = NewTeamID;
				MinimapSubsystem->RegisterMinimapActor(PlayerMarkerInstance, TeamID);
			}
		}
	}
}
