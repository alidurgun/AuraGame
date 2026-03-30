// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/AuraAbilitySystemComponent.h"

#include "GameplayAbilitySystem/GameplayAbilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::GameplayEffectApplied);
}

void UAuraAbilitySystemComponent::GameplayEffectApplied_Implementation(UAbilitySystemComponent* Source,
                                                        const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle) const
{
	FGameplayTagContainer TagContainer;
	SpecApplied.GetAllAssetTags(TagContainer);
	
	OnEffectTagApplied.Broadcast(TagContainer);
}

void UAuraAbilitySystemComponent::AddCharacterAbilites(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (auto ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(ability,1);
		/* Two-way to grant ability. */
		// GiveAbility can accept const parameter. Just giving the ability. Activation later.
		// GiveAbility(AbilitySpec);

		// GiveAbilityAndActivateOnce can only accept non const parameter. It'll activate the ability
		// once it gave.

		// We will activate the ability according to input.
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupAbilityTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagPressed(FGameplayTag Tag)
{
	if (!Tag.IsValid() || !AbilityActorInfo->IsLocallyControlled()) return;

	UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagPressed called for tag: %s at time: %f"), 
		*Tag.ToString(), GetWorld()->GetTimeSeconds());
	
	for (auto ActivatableAbility : GetActivatableAbilities())
	{
		if (ActivatableAbility.DynamicAbilityTags.HasTagExact(Tag))
		{
			// To keep track for its status. We can implement some functionality.
			AbilitySpecInputPressed(ActivatableAbility);
			if (!ActivatableAbility.IsActive())
			{
				// Don't manually activate it directly. Maybe some other ability or status can prevent
				// this ability to be active. Therefore, use TryActivateAbility.
				TryActivateAbility(ActivatableAbility.Handle);
			}
			break;
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(FGameplayTag Tag)
{
	
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(FGameplayTag Tag)
{
	if (!Tag.IsValid()) return;

	for (auto ActivatableAbility : GetActivatableAbilities())
	{
		if (ActivatableAbility.DynamicAbilityTags.HasTagExact(Tag))
		{
			AbilitySpecInputReleased(ActivatableAbility);
			// Don't cancel the ability yet. Maybe it will be canceled later. (For ex: When it reach to target)
			break;
		}
	}
}
