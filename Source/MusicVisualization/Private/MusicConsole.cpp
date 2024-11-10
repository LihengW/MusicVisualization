// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicConsole.h"

// Sets default values
AMusicConsole::AMusicConsole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConsoleMeshComponent1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConsoleMeshComponent1"));
	ConsoleMeshComponent2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConsoleMeshComponent2"));
	ConsoleMeshComponent3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConsoleMeshComponent3"));
	RootComponent = ConsoleMeshComponent1;
	ConsoleMeshComponent2->AttachToComponent(ConsoleMeshComponent1, FAttachmentTransformRules::KeepRelativeTransform);
	ConsoleMeshComponent3->AttachToComponent(ConsoleMeshComponent1, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMusicConsole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicConsole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

