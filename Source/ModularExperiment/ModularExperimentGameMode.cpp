// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModularExperimentGameMode.h"

#include "Generator/Anchor.h"
#include "Generator/Chunk.h"
#include "UObject/ConstructorHelpers.h"

AModularExperimentGameMode::AModularExperimentGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void AModularExperimentGameMode::BeginPlay()
{
	Super::BeginPlay();

    if (auto const World = GetWorld())
    {
        const auto RandomIndex = FMath::RandRange(0, ChunkClasses.Num() - 1);

        // Spawn the starting chunk
        auto NewChunk = World->SpawnActor<AChunk>(ChunkClasses[RandomIndex]);
        TArray<UAnchor*> Anchors = NewChunk->GetAnchors();

        for (int32 i = 1; i < SpawnCount; i++)
        {
            if (Anchors.Num() > 0)
            {
                // Pick a random anchor
                const auto AnchorIndex = FMath::RandRange(0, Anchors.Num() - 1);
                const UAnchor* SelectedAnchor = Anchors[AnchorIndex];

                // Spawn a new chunk
                const auto RandomChunkIndex = FMath::RandRange(0, ChunkClasses.Num() - 1);
                NewChunk = World->SpawnActor<AChunk>(ChunkClasses[RandomChunkIndex]);

                if (NewChunk)
                {
                    // Find an anchor in the new chunk to match the selected anchor
                    if (const TArray<UAnchor*> NewChunkAnchors = NewChunk->GetAnchors(); NewChunkAnchors.Num() > 0)
                    {
                        const auto SecondAnchorIndex = FMath::RandRange(0, NewChunkAnchors.Num() - 1);
                        const UAnchor* NewChunkAnchor = NewChunkAnchors[SecondAnchorIndex];

                        // Calculate the rotation so that the anchors face each other
                        const FRotator SelectedAnchorRotation = SelectedAnchor->GetComponentRotation();
                        const FRotator NewChunkAnchorRotation = NewChunkAnchor->GetComponentRotation();
                        const FRotator DesiredRotation = (SelectedAnchorRotation + FRotator(0, 180, 0)) - NewChunkAnchorRotation;
                        NewChunk->AddActorWorldRotation(DesiredRotation);

                        // Calculate the new chunk's position so that the anchors match
                        const FVector NewChunkAnchorOffset = NewChunkAnchor->GetComponentLocation() - NewChunk->GetActorLocation();
                        const FVector Offset = SelectedAnchor->GetComponentLocation() - NewChunkAnchorOffset;
                        NewChunk->SetActorLocation(NewChunk->GetActorLocation() + Offset);

                        // Remove the used anchor
                        Anchors.RemoveAt(AnchorIndex);

                        // Add new anchors from the newly spawned chunk, excluding the matched anchor
                        for (UAnchor* Anchor : NewChunkAnchors)
                        {
                            if (Anchor != NewChunkAnchor)
                            {
                                Anchors.Add(Anchor);
                            }
                        }
                    }
                }
            }
            else
            {
                // No more anchors to use
                break;
            }
        }
    }
}
