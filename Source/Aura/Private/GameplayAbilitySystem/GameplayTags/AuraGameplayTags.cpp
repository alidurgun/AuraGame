// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/GameplayTags/AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::instance;

FAuraGameplayTags::FAuraGameplayTags()
{
}

FAuraGameplayTags::~FAuraGameplayTags()
{
}

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	/* Primary Attributes initialization */
	instance.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increases physical damage."));

	instance.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Increases magical damage."));

	instance.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),
		FString("Increases Armor and Armor Penetration."));

	instance.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		FString("Increases Health."));
	/* End Primary Attributes initialization */

	/* Secondary Attributes initialization */
	instance.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken, improves Block Chance."));

	instance.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("Ignores percentage of enemy Armor, increases Crit Hit Chance."));

	instance.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("Chance to cut incoming damage in half."));

	instance.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("Chance to double damage plus critical hit bonus."));

	instance.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),
		FString("Bonus damage added when a critical hit is scored."));

	instance.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"),
		FString("Reduces critical hit chance of attacking enemies."));

	instance.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("Amount of health regenerated every 1 second."));

	instance.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("Amount of mana regenerated every 1 second."));

	instance.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Maximum amount of Health obtainable."));

	instance.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("Maximum amount of Mana obtainable."));
	/* End Secondary Attributes initialization */

	/* Input Tags initialization */
	instance.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input for mouse left click button."));

	instance.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input for mouse right click button."));

	instance.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input for Keyboard 1 button."));

	instance.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input for Keyboard 2 button."));

	instance.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input for Keyboard 3 button."));

	instance.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input for Keyboard 4 button."));
	/* End Input Tags initialization */

	/* Ability Damage Tags initialization */
	instance.Ability_FireBolt_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.FireBolt.Damage"),
		FString("FireBolt Damage Tag"));
	/* End Ability Damage Tags initialization */

	/* Ability Damage Types */
	instance.DamageTypes_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("DamageTypes.Arcane"),
		FString("Arcane Type Damage"));
	instance.DamageTypes_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("DamageTypes.Fire"),
		FString("Fire Type Damage"));
	instance.DamageTypes_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("DamageTypes.Lightning"),
		FString("Lightning Type Damage"));
	instance.DamageTypes_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("DamageTypes.Physical"),
		FString("Physical Type Damage"));
	/* End Ability Damage Types */

	/* Ability Damage Resistances */
	instance.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Arcane"),
		FString("Resistance to Arcane Damage"));
	instance.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"),
		FString("Resistance to Fire Damage"));
	instance.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"),
		FString("Resistance to Lightning Damage"));
	instance.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Physical"),
		FString("Resistance to Physical Damage"));
	/* End Ability Damage Resistances */

	// Associate damage type with resistance.
	instance.DamageTypesToResistances.Add(instance.DamageTypes_Arcane, instance.Attributes_Resistance_Arcane);
	instance.DamageTypesToResistances.Add(instance.DamageTypes_Fire, instance.Attributes_Resistance_Fire);
	instance.DamageTypesToResistances.Add(instance.DamageTypes_Lightning, instance.Attributes_Resistance_Lightning);
	instance.DamageTypesToResistances.Add(instance.DamageTypes_Physical, instance.Attributes_Resistance_Physical);

	/* Hit React Tags Initialization */
	instance.HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"),
		FString("Effect for Hit Reaction"));
	/* End Hit React Tags Initialization */

	/* Abilities Tags Initialization */
	instance.Abilities_MeleeAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.MeleeAttack"),
		FString("Melee Attack Ability Tag"));
	/* End Abilities Tags Initialization */

	/* Montage Tags Initialization */
	instance.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.1"),
		FString("Attack montages number 1"));

	instance.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.2"),
		FString("Attack montages number 2"));

	instance.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.3"),
		FString("Attack montages number 3"));

	instance.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.4"),
	FString("Attack montages number 4"));
	/* End Montage Tags Initialization */

	/* Combat Socket Tags initialization*/
	instance.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.Weapon"),
		FString("Combat socket location for weapon"));

	instance.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.LeftHand"),
		FString("Combat socket location for left hand"));

	instance.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.RightHand"),
		FString("Combat socket location for right hand"));

	instance.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.Tail"),
		FString("Combat socket location for tail"));
	/* End Combat Socket Tags initialization*/
}
