// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

class UInputAction;

/* We will bind inputs to some gameplay tags. As result, we will have some kind of map like;
 * key = InputAction
 * value = GameplayTag
 */
USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * To decide how to activate abilities in response to inputs. Enhanced input should be used for this.
 * Also, input-to ability map should be changed according to changes on the abilities.(Like Diablo series)
 * We will use array of input actions that linked to the gameplay tags.
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraInputAction> AbilityInputActions;

	const UInputAction* FindAbilityActionByTag(const FGameplayTag& Tag, bool bLogNotFound = false);
};
