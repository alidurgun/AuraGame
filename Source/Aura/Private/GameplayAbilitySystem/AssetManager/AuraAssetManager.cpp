// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/AssetManager/AuraAssetManager.h"

#include "GameplayAbilitySystem/GameplayTags/AuraGameplayTags.h"

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeNativeGameplayTags();
}
