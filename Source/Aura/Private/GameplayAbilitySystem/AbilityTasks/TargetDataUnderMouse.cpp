// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	// To create a new ability task we have to use NewAbilityTask function.
	UTargetDataUnderMouse* instance = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	
	return instance;
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	/*
	 * Using this function because we have received the data now and no need to still keep them in the cache,
	 * So we will clear the cache after received it and we will free up the memory.
	 */
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderMouse::Activate()
{
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		// we are on client side, send the target data
		SendMouseCursorData();
	}
	else
	{
		// we are on server side. Listen for target data
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

		/*
		 * This function returns TargetDataSet delegate for a given Ability/PrecitionKey pair.
		 * It needs to know that prediction key associated with the specific task.
		 * bind OnTargetDataReplicatedCallback function to listen broadcast.
		 */
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(
			this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);

		// This will check if the data has already received or not. False means data has not arrived yet.
		if (!AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey))
		{
			// If it is false then we should wait for the data.
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	// Hence we will need current prediction Key we will use Scoped Prediction data.
	// This will tell the UE that we are going to Predict variables locally. Specifically inside of this Scope.
	FScopedPredictionWindow ScopedPrediction{AbilitySystemComponent.Get()};
	
	if (const APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get())
	{
		FHitResult HitResult;
		if (PC->GetHitResultUnderCursor(ECC_Visibility,false, HitResult))
		{
			FGameplayAbilityTargetDataHandle DataHandle;
			// Target Data with single hit result usage.
			FGameplayAbilityTargetData_SingleTargetHit* Data{new FGameplayAbilityTargetData_SingleTargetHit()};
			Data->HitResult = HitResult;
			DataHandle.Add(Data);

			// Send this information to the server side.
			// param[4] in => this will use the scoped key that we have created in this function.
			AbilitySystemComponent->ServerSetReplicatedTargetData(
				GetAbilitySpecHandle(),
				GetActivationPredictionKey(),
				DataHandle,
				FGameplayTag(),
				AbilitySystemComponent->ScopedPredictionKey);

			// To check if the broadcast still safe. If the ability is not active anymore we shouldn't broadcast it.
			if (ShouldBroadcastAbilityTaskDelegates())
			{
				ValidData.Broadcast(DataHandle);
			}
		}
	}
}
