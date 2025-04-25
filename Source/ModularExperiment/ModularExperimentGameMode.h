// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ModularExperimentGameMode.generated.h"

UCLASS(minimalapi)
class AModularExperimentGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UAnchor*> SpawnedAnchors;

public:
	AModularExperimentGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Generator)
	int32 SpawnCount = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Generator)
	TArray<TSubclassOf<class AChunk>> ChunkClasses;
	
	void BeginPlay() override;
};