// Project has been managed by Ali Durgun


#include "UI/WidgetController/AuraAttributeMenuWC.h"

#include "GameplayAbilitySystem/AuraAttributeSet.h"
#include "GameplayAbilitySystem/DataAsset/AttributeInfo.h"
#include "GameplayAbilitySystem/GameplayTags/AuraGameplayTags.h"

void UAuraAttributeMenuWC::BroadcastInitialValues()
{
	check(AttributeInfo);
	FAuraAttributeInfo info = AttributeInfo->FindAttributeInfoForTag(
		FAuraGameplayTags::Get().Attributes_Primary_Strength);
	
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	info.AttributeValue = AS->GetStrength();

	AttributeInfoDelegate.Broadcast(info);
}

void UAuraAttributeMenuWC::BindCallbacksToDependencies()
{

}
