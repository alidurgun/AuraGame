// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
/**
 * This will include all gameplay tags for the project. It's going to be singleton containing
 * native Gameplay Tags.
 * Native: created from C++ and available in both BP and C++ side.
 */
struct FAuraGameplayTags
{
public:
	FAuraGameplayTags();
	~FAuraGameplayTags();

	/* To get instance of this singleton class. */
	static const FAuraGameplayTags& Get() { return instance; }

	/* To initialize all Ability system component related gameplay tags in the game. */
	static void InitializeNativeGameplayTags();

	/* Primary Attributes */
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	/* End Primary Attributes */

	/* Secondary Attributes */
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	/* End Secondary Attributes */

	/* Input Tags */
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	/* End Input Tags */

private:
	static FAuraGameplayTags instance;
};
