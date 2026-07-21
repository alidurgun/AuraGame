// Project has been managed by Ali Durgun


#include "UI/WidgetController/AuraOverlayWidgetController.h"

#include "GameplayAbilitySystem/AuraAbilitySystemComponent.h"
#include "GameplayAbilitySystem/AuraAttributeSet.h"

void UAuraOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// Use Broadcast function of delegate function to send relevant data to the widget that
	// uses this controller.
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UAuraOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	/*
	 * We will use AbilitySystemComponent's GetGameplayAttributeValueChangeDelegate function
	 * to bind our delegates. This function is Multicast Delegate. Because of it is not Dynamic
	 * we cannot use AddDynamic. We will use AddUObject to bind callback.
	 * This function requires an input(relevant attribute's FGameplayAttribute.)
	 * Therefore we used GetHealthAttribute version, this will return FGameplayAttribute.
	 */

	// Whenever Health attribute has changed it will call this callback function automatically.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Health)
			{
				OnHealthChanged.Broadcast(Health.NewValue);
			});

	// Whenever MaxHealth attribute has changed it will call this callback function automatically.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& MaxHealth)
			{
				OnMaxHealthChanged.Broadcast(MaxHealth.NewValue);
			});

	// Whenever Mana attribute has changed it will call this callback function automatically.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Mana)
			{
				OnManaChanged.Broadcast(Mana.NewValue);
			});

	// Whenever MaxMana attribute has changed it will call this callback function automatically.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this] (const FOnAttributeChangeData& MaxMana)
			{
				OnMaxManaChanged.Broadcast(MaxMana.NewValue);
			});

	if (UAuraAbilitySystemComponent* AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		/*
		 * Timing can be change in the game. So we cannot be sure about which one will occur first.
		 * Either broadcast or listening.
		 * If listening occurs first then there is no problem hence it will catch it.
		 * But if broadcast occurs first then we will loose the data. In order to catch that
		 * even in that condition we have used this boolean variable.
		 */
		if (AuraAbilitySystemComponent->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(AuraAbilitySystemComponent);
		}
		else
		{
			AuraAbilitySystemComponent->AbilitiesGivenDelegate.AddUObject(this, &UAuraOverlayWidgetController::OnInitializeStartupAbilities);
		}
		
		AuraAbilitySystemComponent->OnEffectTagApplied.AddLambda(
		[this](const FGameplayTagContainer& TagContainer)
		{
			for (const auto& Tag : TagContainer)
			{
				FGameplayTag RequiredTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				/* "Message.Health".MatchesTag("Message") will return True,
				 * "Message".MatchesTag("Message.Health") will return False */
				if (Tag.MatchesTag(RequiredTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					if (Row != nullptr)
					{
						OnMessageWidgetRow.Broadcast(*Row);
					}
				}
			}
		});
	}
}

void UAuraOverlayWidgetController::OnInitializeStartupAbilities(UAuraAbilitySystemComponent* AuraAbilitySystemComponent)
{
	// TODO! Get information about all given abilities, lookup their Ability Info, and broadcast it to widgets.

	if (!AuraAbilitySystemComponent->bStartupAbilitiesGiven) return;
}
