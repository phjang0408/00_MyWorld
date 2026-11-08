// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYWORLD_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

};
