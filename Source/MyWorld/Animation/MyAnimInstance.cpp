// MyAnimInstance.cpp

#include "MyAnimInstance.h"
#include "Character/MyWorldCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<AMyWorldCharacter>(TryGetPawnOwner());
	if (IsValid(OwnerCharacter) == true)
	{
		OwnerCharacterMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float deltaseconds)
{
	Super::NativeUpdateAnimation(deltaseconds);

	if (IsValid(OwnerCharacter) != false && IsValid(OwnerCharacterMovementComponent) != false)
	{
		Velocity = OwnerCharacterMovementComponent->Velocity;
		GroundSpeed = Velocity.Size2D();	// Z 제외, XY 내적의 제곱근
		bisFalling = OwnerCharacterMovementComponent->IsFalling();
		// 3cm/s over
		bShouldMove = (GroundSpeed > 3.f) &&
			(OwnerCharacterMovementComponent->GetCurrentAcceleration() != FVector::ZeroVector);
	}
}
