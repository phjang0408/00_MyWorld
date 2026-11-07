// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MyGameModeBase.h"

void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("NewGameMode!!"));

	UE_LOG(LogTemp, Warning, TEXT("HI!"));
}

AMyGameModeBase::AMyGameModeBase()
{
}
