// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyWorldCharacter.h"
#include "Game/MyGameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/MyInputConfig.h"
#include "Kismet/KismetSystemLibrary.h"

AMyWorldCharacter::AMyWorldCharacter()
{
	// 1. Capsule Size
	float CharacterHalfHeight = 90.f;
	float CharacterRadius = 40.f;
	GetCapsuleComponent()->InitCapsuleSize(CharacterRadius, CharacterHalfHeight);

	FVector PivotPosition(0.f, 0.f, -CharacterHalfHeight);
	FRotator PivotRotator(0.f, -90.f, 0.f); // Pitch, Yaw, Roll -> X is front
	GetMesh()->SetRelativeLocationAndRotation(PivotPosition, PivotRotator);

	// Camera
	My_SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	check(My_SpringArmComponent != nullptr);
	My_SpringArmComponent->bUsePawnControlRotation = true;	// SpringArm - Controller
	My_SpringArmComponent->SetupAttachment(RootComponent);
	My_SpringArmComponent->TargetArmLength = 300.f;
	My_SpringArmComponent->SetRelativeLocation(My_CameraOffset);
	
	My_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("My_Camera"));
	check(My_CameraComponent != nullptr);
	My_CameraComponent->SetupAttachment(My_SpringArmComponent);

	// features
	PrimaryActorTick.bCanEverTick = false;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;
	GetCharacterMovement()->JumpZVelocity = 500.f;
	
	bUseControllerRotationYaw = false; // Character - Controller
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character - 이동 방향
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f); // Yaw 2배(0.25second)
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

// 연결은 SetUpPlayerInputComponent
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
	const FVector2D MovementVector = InValue.Get<FVector2D>();
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, MovementVector.X);
	AddMovementInput(Right, MovementVector.Y);
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

