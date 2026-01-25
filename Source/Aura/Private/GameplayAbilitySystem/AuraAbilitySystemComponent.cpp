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

void UAuraAbilitySystemComponent::AddCharacterAbilites(const TArray<TSubclassOf<UGameplayAbility>>& abilities)
{
	for (auto ability : abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(ability,1);
		/* Two-way to grant ability. */
		// GiveAbility can accept const parameter. Just giving the ability. Activation later.
		// GiveAbility(AbilitySpec);

		// GiveAbilityAndActivateOnce can only accept non const parameter. It'll activate the ability
		// once it gave.
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}
