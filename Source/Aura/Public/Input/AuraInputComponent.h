// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "AuraInputConfig.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	/*
	 * Bind our abilities for related functions. Each of our ability will be bound to 3 functions for
	 * Pressed, Held, Released functionalities. Therefore, we need function signatures too.
	 */
	template<class UserClass, typename PressedFuncType, typename HeldFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConf, UserClass* Object,
		PressedFuncType PressedFunc, HeldFuncType HeldFunc, ReleasedFuncType ReleasedFunc);
};

template <class UserClass, typename PressedFuncType, typename HeldFuncType, typename ReleasedFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConf, UserClass* Object,
	PressedFuncType PressedFunc, HeldFuncType HeldFunc, ReleasedFuncType ReleasedFunc)
{
	for (auto AbilityAction : InputConf->AbilityInputActions)
	{
		// Bind every action we have to related callback functions for the input types.(pressed etc.)
		// AbilityAction.InputTag will be input for the function that we are binding.
		// So the functions that we are created in the AuraPlayerController should accept Gametag as param.
		if (AbilityAction.InputAction && AbilityAction.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(AbilityAction.InputAction, ETriggerEvent::Started, Object, PressedFunc, AbilityAction.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(AbilityAction.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, AbilityAction.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(AbilityAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, AbilityAction.InputTag);
			}
		}
	}
}
