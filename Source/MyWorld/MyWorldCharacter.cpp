// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWorldCharacter.h"

// Sets default values
AMyWorldCharacter::AMyWorldCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyWorldCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyWorldCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyWorldCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

