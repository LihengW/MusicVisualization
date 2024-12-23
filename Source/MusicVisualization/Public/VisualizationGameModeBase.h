// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VisualizationGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MUSICVISUALIZATION_API AVisualizationGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
	TArray<USoundWave*> AudioAssets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
	FString AudioAssetsAddress = "../../../Content/Audio";
};
