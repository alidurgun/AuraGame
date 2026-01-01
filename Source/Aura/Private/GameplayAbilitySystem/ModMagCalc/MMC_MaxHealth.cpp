// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "GameplayAbilitySystem/AuraAttributeSet.h"
#include "Interface/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	// define which attribute should be captured.
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;
	/* Snapshot:
	 * It is about timing. When to capture this attribute.
	 * 1-) When the effect spec is created?
	 * 2-) When the effect spec is applied?
	 *
	 * In our case it does not matter. Because we are creating the effect and applying immediately.
	 *
	 * For ex: When the fireball created it should not effect anything. If the fireball hit something
	 * then we should apply the effect.
	 */
	
	// add this VigorDef to the relevant attributes.
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	/* We can retrieve tags from both source and target */
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	/* To capture an attribute and get the attribute magnitude value we need this variable. */
	FAggregatorEvaluateParameters EvaluateParams;

	// It has its own tags.
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	// Vigor will be output parameter for the function.
	float Vigor = 0;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParams, Vigor);
	// We are getting the value of the captured attribute via this function.

	// if the vigor returns negative value then we will accept 0.
	Vigor = FMath::Max<float>(Vigor, 0.0f);

	/* We need also level property. To retrieve the level of the relevant source we need to
	 * access its context and then the source object. */
	const ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());

	return 80.0f + 2.5f * Vigor + 10.0f * CombatInterface->GetPlayerLevel();
}
