// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	// To create a new ability task we have to use NewAbilityTask function.
	UTargetDataUnderMouse* instance = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	
	return instance;
}

void UTargetDataUnderMouse::Activate()
{
	if (const APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get())
	{
		FHitResult HitResult;
		if (PC->GetHitResultUnderCursor(ECC_Visibility,false, HitResult))
		{
			ValidData.Broadcast(HitResult.ImpactPoint);
		}
	}
}
