// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "GameplayAbilitySystem/AuraAttributeSet.h"
#include "Interface/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float Intelligence;
	const FAggregatorEvaluateParameters EvaluateParams;
	
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluateParams, Intelligence);

	Intelligence = FMath::Max<float>(Intelligence, 0.0f);
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	
	return 65.0f + Intelligence * 3.3f + 8.0f * CombatInterface->GetPlayerLevel();
}
