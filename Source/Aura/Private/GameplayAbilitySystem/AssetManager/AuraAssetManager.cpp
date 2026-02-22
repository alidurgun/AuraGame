// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/AssetManager/AuraAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "GameplayAbilitySystem/GameplayTags/AuraGameplayTags.h"

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeNativeGameplayTags();

	/*
	 * This line required to use FGameplayAbilityTargetData!
	 * We are initializing the Target Data in here too.
	 */
	UAbilitySystemGlobals::Get().InitGlobalData();
}
