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
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UAuraOverlayWidgetController::HealthChanged);

	// Whenever MaxHealth attribute has changed it will call this callback function automatically.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UAuraOverlayWidgetController::MaxHealthChanged);

	// Whenever Mana attribute has changed it will call this callback function automatically.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UAuraOverlayWidgetController::ManaChanged);

	// Whenever MaxMana attribute has changed it will call this callback function automatically.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UAuraOverlayWidgetController::MaxManaChanged);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->OnEffectTagApplied.AddLambda(
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
		}
		);
}

void UAuraOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Health) const
{
	// Use Broadcast to send data to the widget.
	OnHealthChanged.Broadcast(Health.NewValue);
}

void UAuraOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& MaxHealth) const
{
	// Use Broadcast to send data to the widget.
	OnMaxHealthChanged.Broadcast(MaxHealth.NewValue);
}

void UAuraOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Mana) const
{
	// Use Broadcast to send data to the widget.
	OnManaChanged.Broadcast(Mana.NewValue);
}

void UAuraOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& MaxMana) const
{
	// Use Broadcast to send data to the widget.
	OnMaxManaChanged.Broadcast(MaxMana.NewValue);
}
