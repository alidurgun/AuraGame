// Project has been managed by Ali Durgun


#include "UI/WidgetController/AuraAttributeMenuWC.h"

#include "GameplayAbilitySystem/AuraAttributeSet.h"
#include "GameplayAbilitySystem/DataAsset/AttributeInfo.h"
#include "GameplayAbilitySystem/GameplayTags/AuraGameplayTags.h"

void UAuraAttributeMenuWC::BroadcastInitialValues()
{
	check(AttributeInfo);
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	for (auto& Pair : AS->TagsToAttribute)
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}

}

void UAuraAttributeMenuWC::BindCallbacksToDependencies()
{
	check(AttributeInfo);
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	for (auto& Pair : AS->TagsToAttribute)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, AS, Pair](const FOnAttributeChangeData& Data)
			{
				FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
				Info.AttributeValue = Pair.Value().GetNumericValue(AS);
				AttributeInfoDelegate.Broadcast(Info);
			});
	}
}
