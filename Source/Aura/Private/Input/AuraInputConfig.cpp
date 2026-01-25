// Project has been managed by Ali Durgun


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityActionByTag(const FGameplayTag& Tag, bool bLogNotFound)
{
	for (FAuraInputAction Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == Tag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Given tag cannot be found in the actions mapping."));
	}
	return nullptr;
}
