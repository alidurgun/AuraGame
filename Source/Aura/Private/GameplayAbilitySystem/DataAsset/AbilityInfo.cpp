// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/DataAsset/AbilityInfo.h"

#include "Aura/AuraLog.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityByAbilityTag(const FGameplayTag& AbilityTag, const bool LogIfNotFound) const
{
	for (const FAuraAbilityInfo& AbilityInfo : Abilities)
	{
		if (AbilityInfo.AbilityTag == AbilityTag)
		{
			return AbilityInfo;
		}
	}

	if (LogIfNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can't find info for AbilityTag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}
	
	return FAuraAbilityInfo();
}
