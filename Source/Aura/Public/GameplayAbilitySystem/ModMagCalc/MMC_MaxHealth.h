// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

/**
 * This class will be responsible from calculating attribute values according to the attribute
 * related with this attribute and some additional properties such as level etc.
 * With Custom Calculations we will be able to calculate those kinds of calculations.
 * Independent of attribute.
 *
 * This class will be used for MaxHealth calculation.
 *
 * Disadvantage:
 * We can only apply to one kind of attribute. For the another attribute we have to create a new
 * ModMagnitudeCalculation class.
 */
UCLASS()
class AURA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_MaxHealth();

	/* Calculate the magnitude and apply it to the attribute. */
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	/* Attribute to be captured for the calculation. */
	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
