// Fill out your copyright notice in the Description page of Project Settings.


#include "FreqConvertComponent.h"

// Sets default values for this component's properties
UFreqConvertComponent::UFreqConvertComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	FString notesname[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
	int notestage = 0;
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			float notefreq = (StandardFrequency / 32.0f) * FMath::Pow(2, (i * 12 + j - 9.0f) / 12.0f);
			FreqArray.Add(notefreq);
			FString name = notesname[j] + FString::FromInt(notestage);
			Note2FreqMap.Add(name, notefreq);
		}
		notestage++;
	}
	// ...
}


// Called when the game starts
void UFreqConvertComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFreqConvertComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFreqConvertComponent::GetNormalizedFreq(float LowerBound, float UpperBound)
{
	OutputArray.Empty();
	OutputMap.Empty();
	for (auto itr = Note2FreqMap.CreateConstIterator(); itr; ++itr)
	{
		if (itr->Value > LowerBound && itr->Value < UpperBound)
		{
			float normalized_value = (itr->Value - LowerBound) / (UpperBound - LowerBound);
			OutputArray.Add(normalized_value);
			OutputMap.Add(itr->Key, normalized_value);
		}
	}
}

