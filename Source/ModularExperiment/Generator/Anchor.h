// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Anchor.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MODULAREXPERIMENT_API UAnchor : public USceneComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE UAnchor() { PrimaryComponentTick.bCanEverTick = false; }
};
