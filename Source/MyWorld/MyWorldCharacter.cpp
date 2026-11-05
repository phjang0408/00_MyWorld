// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWorldCharacter.h"
#include "MyGameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyInputConfig.h"
#include "Kismet/KismetSystemLibrary.h"

AMyWorldCharacter::AMyWorldCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void AMyWorldCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// IMC Adding
	APlayerController* MyWorldController = Cast<APlayerController>(GetController());
	if (IsValid(MyWorldController) == true)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MyWorldController->GetLocalPlayer());
		if (IsValid(Subsystem) == true)
		{
			Subsystem->AddMappingContext(PlayerCharacterInputMappingContext, 0);
		}
	}

	// For InputRun
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void AMyWorldCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// ø¨∞·¿∫ SetUpPlayerInputComponent
void AMyWorldCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent) == true && IsValid(PlayerCharacterInputConfig))
	{
		// BindAction
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::InputLook);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Run, ETriggerEvent::Started, this, &ThisClass::InputRun);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Run, ETriggerEvent::Completed, this, &ThisClass::InputRun);
	}
}

void AMyWorldCharacter::InputMove(const FInputActionValue& InValue)
{
	FVector2D MovementVector = InValue.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MovementVector.X);
	AddMovementInput(GetActorRightVector(), MovementVector.Y);
}

void AMyWorldCharacter::InputLook(const FInputActionValue& InValue)
{
	FVector2D LookVector = InValue.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void AMyWorldCharacter::InputRun(const FInputActionValue& InValue)
{
	const bool runPressed = InValue.Get<bool>();
	if (runPressed == true) 
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed * 2.f;
	}
	else 
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

