// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anchor.h"
#include "GameFramework/Actor.h"
#include "Chunk.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MODULAREXPERIMENT_API AChunk : public AActor
{
	GENERATED_BODY()

public:
	AChunk();

	UFUNCTION()
	TArray<UAnchor*> GetAnchors() const;

protected:

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
