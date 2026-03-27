// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/AuraAbilitySystemGlobals.h"

#include "Common/AuraGameplayEffectContext.h"

FGameplayEffectContext* UAuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraGameplayEffectContext(); // Custom FGameplayEffectContext that we have created to keep crit, block hit.
}
