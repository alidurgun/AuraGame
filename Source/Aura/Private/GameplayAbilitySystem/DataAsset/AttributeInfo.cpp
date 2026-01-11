// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/DataAsset/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& Tag, bool bLogNotFound) const
{
	for (FAuraAttributeInfo AttributeInfo : AttributeInformation)
	{
		// == can also be used.
		if (AttributeInfo.AttributeTag.MatchesTagExact(Tag))
		{
			return AttributeInfo;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Attribute %s not found in the AttributeList"), *(Tag.ToString()));
	}
	return FAuraAttributeInfo();
}
