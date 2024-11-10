// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/GameplayStatics.h"

#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (const ULocalPlayer* Player = (GEngine && GetWorld()) ? GEngine->GetFirstGamePlayer(GetWorld()) : nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
		if (DefaultMapping)
		{
			Subsystem->AddMappingContext(DefaultMapping, 0);
		}
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraComponent->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	CameraComponent->bUsePawnControlRotation = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->TargetArmLength = 300.0f;

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);


}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const ULocalPlayer* Player = (GEngine && GetWorld()) ? GEngine->GetFirstGamePlayer(GetWorld()) : nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
		if (DefaultMapping)
		{
			Subsystem->AddMappingContext(DefaultMapping, 0);
		}
	}
	// Enhanced Input System Settings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);

		EnhancedInputComponent->BindAction(PullAction, ETriggerEvent::Triggered, this, &AMainCharacter::Pull);
		EnhancedInputComponent->BindAction(PushAction, ETriggerEvent::Triggered, this, &AMainCharacter::Push);

		EnhancedInputComponent->BindAction(ShowTableAction, ETriggerEvent::Triggered, this, &AMainCharacter::ShowTable);
		EnhancedInputComponent->BindAction(ShowObjectUIAction, ETriggerEvent::Triggered, this, &AMainCharacter::ShowObjectUI);

		EnhancedInputComponent->BindAction(InstallAction, ETriggerEvent::Triggered, this, &AMainCharacter::InstallBluePrint);
	}
}

void AMainCharacter::Move(const FInputActionValue& value)
{
	FVector2D MoveVector = value.Get<FVector2D>();
	MoveVector = 0.6 * MoveVector;
	if (Controller)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FVector gravity = GetCharacterMovement()->GetGravityDirection();
		Rotation.Pitch *= 0;
		Rotation.Roll *= 0;
		GEngine->AddOnScreenDebugMessage(3, 5, FColor::Blue, gravity.ToString());
		const FVector ForwardDirection = GetCharacterMovement()->RotateGravityToWorld(FRotationMatrix(Rotation).GetUnitAxis(EAxis::X));
		const FVector RightDirection = GetCharacterMovement()->RotateGravityToWorld(FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y));

		AddMovementInput(ForwardDirection, MoveVector.X);
		AddMovementInput(RightDirection, MoveVector.Y);
	}
}


void AMainCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookVector = value.Get<FVector2D>();
	if (Controller) // character is under control
	{
		AddControllerYawInput(-LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void AMainCharacter::Pull(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, "Receive Pull");
		FCollisionQueryParams qpara;
		FHitResult LineHit;
		FVector Start = CameraComponent->GetComponentLocation();
		FRotator Rotation = CameraComponent->GetComponentRotation();
		GetWorld()->LineTraceSingleByChannel(LineHit, Start, Start + Rotation.Vector() * SearchRange, ECollisionChannel::ECC_GameTraceChannel1, qpara);
		if (LineHit.bBlockingHit)
		{
			LineHit.GetActor()->AddActorWorldOffset(-Rotation.Vector() * 50.0f);
			GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, "Hit Something");
		}
	}
}

void AMainCharacter::Push(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, "Receive pUSH");
		FCollisionQueryParams qpara;
		FHitResult LineHit;
		FVector Start = CameraComponent->GetComponentLocation();
		FRotator Rotation = CameraComponent->GetComponentRotation();
		GetWorld()->LineTraceSingleByChannel(LineHit, Start, Start + Rotation.Vector() * SearchRange, ECollisionChannel::ECC_GameTraceChannel1, qpara);
		if (LineHit.bBlockingHit)
		{
			LineHit.GetActor()->AddActorWorldOffset(Rotation.Vector() * 50.0f);
			GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, "Hit Something");
		}
	}
}

void AMainCharacter::Install(const FInputActionValue& value)
{
	// save for later
}

void AMainCharacter::Grab(const FInputActionValue& value)
{
	// save for later
}






