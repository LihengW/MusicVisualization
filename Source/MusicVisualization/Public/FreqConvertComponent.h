// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Templates/Tuple.h"
#include "FreqConvertComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MUSICVISUALIZATION_API UFreqConvertComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFreqConvertComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MIDI")
	float StandardFrequency = 440.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MIDI")
	TArray<float> FreqArray = TArray<float>();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MIDI")
	TMap<FString, float> Note2FreqMap = TMap<FString, float>();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output")
	TArray<float> OutputArray = TArray<float>();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Output")
	TMap<FString, float> OutputMap = TMap<FString, float>();

	UFUNCTION(BlueprintCallable, Category = "MIDI")
	void GetNormalizedFreq(float LowerBound, float UpperBound);

};
