// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyWorldCharacter.generated.h"

UCLASS()
class MYWORLD_API AMyWorldCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyWorldCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


#pragma region Input
private:
	void InputMove(const FInputActionValue& InValue);

	void InputLook(const FInputActionValue& InValue);

	void InputJump(const FInputActionValue& InValue);

	void InputRun(const FInputActionValue& InValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UMyInputConfig> PlayerCharacterInputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UInputMappingContext> PlayerCharacterInputMappingContext;
};
