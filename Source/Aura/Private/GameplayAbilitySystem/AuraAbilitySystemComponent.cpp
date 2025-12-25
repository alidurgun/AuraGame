// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::GameplayEffectApplied);
}

void UAuraAbilitySystemComponent::GameplayEffectApplied(UAbilitySystemComponent* Source,
                                                        const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle) const
{
	FGameplayTagContainer TagContainer;
	SpecApplied.GetAllAssetTags(TagContainer);
	
	OnEffectTagApplied.Broadcast(TagContainer);
}
