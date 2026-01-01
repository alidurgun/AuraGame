// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

/**
 * This class will be used for MaxMana calculation.
 * MaxMana will depend on the level and intelligence.
 */
UCLASS()
class AURA_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_MaxMana();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	// Max mana will related with Intelligence.
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
};
