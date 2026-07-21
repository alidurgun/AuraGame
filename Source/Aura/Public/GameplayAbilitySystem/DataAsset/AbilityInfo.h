// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInfo.generated.h"

/**
 * This struct will hold information related with ability.
 * It will contain gameplaytag to identify "AbilityTag", and "InputTag".
 * We won't expose InputTag, and it will be set from the code hence it can change.
 * Then it will also contain icon for that ability and material for that ability.
 */
USTRUCT(BlueprintType)
struct FAuraAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UTexture2D> AbilityIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UMaterialInterface> AbilityBackground = nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UAbilityInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAbilityInfo> Abilities;

	FAuraAbilityInfo FindAbilityByAbilityTag(const FGameplayTag& AbilityTag, const bool LogIfNotFound = false) const;
};
