// MyWorldCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyWorldCharacter.generated.h"

class UMyInputConfig;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

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

#pragma region Camera
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> My_SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<UCameraComponent> My_CameraComponent;

	UPROPERTY(EditAnywhere, Category = Camera)
	FVector My_CameraOffset = FVector(0.f,0.f,60.f);

	FORCEINLINE USpringArmComponent* GetSpringArm() const { return My_SpringArmComponent; }

#pragma endregion

#pragma region Input
private:
	void InputMove(const FInputActionValue& InValue);

	void InputLook(const FInputActionValue& InValue);

	void InputRun(const FInputActionValue& InValue);

	void InputAttack(const FInputActionValue& InValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess))
	TObjectPtr<UMyInputConfig> PlayerCharacterInputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess))
	TObjectPtr<UInputMappingContext> PlayerCharacterInputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	FVector2D AdjustLookVector = FVector2D(1.f, 1.f);

	float WalkSpeed = 0.f;

	bool bIsAttacking = false;
};
#pragma endregion
