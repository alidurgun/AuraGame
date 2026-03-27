// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	// Override AllocGameplayEffectContext function to return custom FGameplayEffectContext.
	// This function is calling in MakeEffectContext function.
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
