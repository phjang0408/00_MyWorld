#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyInputConfig.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class MYWORLD_API UMyInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> Look;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> Run;
};
