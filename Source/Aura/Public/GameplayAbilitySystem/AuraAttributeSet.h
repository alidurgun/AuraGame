// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

// Attribute Accessor to use getter setter and initter for the property.
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}

	FGameplayEffectContextHandle GameplayEffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC{nullptr};
	
	UPROPERTY()
	AActor* SourceAvatarActor{nullptr};
	
	UPROPERTY()
	AController* SourceController{nullptr};
	
	UPROPERTY()
	ACharacter* SourceCharacter{nullptr};

	UPROPERTY()
	UAbilitySystemComponent* TargetASC{nullptr};
	
	UPROPERTY()
	AActor* TargetAvatarActor{nullptr};
	
	UPROPERTY()
	AController* TargetController{nullptr};
	
	UPROPERTY()
	ACharacter* TargetCharacter{nullptr};
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	// Vital Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, Category="Vital Stats")
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, Category="Vital Stats")
	FGameplayAttributeData Mana;
	// Vital Attributes

	// Primary Attributes
	// Increases physical damage.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Strength, Category="Primary Stats")
	FGameplayAttributeData Strength;

	// Increases magical damage,
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Intelligence, Category="Primary Stats")
	FGameplayAttributeData Intelligence;

	// Increases Armor and Armor penetration.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Resilience, Category="Primary Stats")
	FGameplayAttributeData Resilience;

	// Increases health.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Vigor, Category="Primary Stats")
	FGameplayAttributeData Vigor;
	// Primary Attributes

	// Secondary Attributes
	// Reduces damage taken, improves Block Chance. Depends on Resilience.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Armor, Category="Secondary Attributes|Resilience")
	FGameplayAttributeData Armor;
	
	// Ignores percentage of enemy Armor, increases Crit Hit Chance. Depends on Resilience.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ArmorPenetration, Category="Secondary Attributes|Resilience")
	FGameplayAttributeData ArmorPenetration;

	// Chance to cut incoming damage in half. Depends on Armor.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BlockChance, Category="Secondary Attributes|Armor")
	FGameplayAttributeData BlockChance;
	
	// Chance to double damage plus critical hit bonus. Depends on Armor Penetration.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitChance, Category="Secondary Attributes|Armor Penetration")
	FGameplayAttributeData CriticalHitChance;
	
	// Bonus damage added when a critical hit is scored. Depends on Armor Penetration.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitDamage, Category="Secondary Attributes|Armor Penetration")
	FGameplayAttributeData CriticalHitDamage;
	
	// Reduces critical hit chance of attacking enemies. Depends on Armor.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitResistance, Category="Secondary Attributes|Armor")
	FGameplayAttributeData CriticalHitResistance;
	
	// Amount of health regenerated every 1 second. Depends on Vigor.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HealthRegeneration, Category="Secondary Attributes|Vigor")
	FGameplayAttributeData HealthRegeneration;
	
	// Amount of mana regenerated every 1 second. Depends on Intelligence.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ManaRegeneration, Category="Secondary Attributes|Intelligence")
	FGameplayAttributeData ManaRegeneration;

	// Maximum amount of Health obtainable. Depends on Vigor.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth, Category="Vital Stats")
	FGameplayAttributeData MaxHealth;

	// Maximum amount of Mana obtainable. Depends on Intelligence.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, Category="Vital Stats")
	FGameplayAttributeData MaxMana;
	// Secondary Attributes

	// Vital Attribute Accessors
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	// Vital Attribute Accessors

	// Primary Attribute Accessors
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);
	// Primary Attribute Accessors

	// Secondary Attribute Accessors
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	// Secondary Attribute Accessors

	// Attribute Callback Functions
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	// Attribute Callback Functions

	// Primary Attribute Callback Functions
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	// Primary Attribute Callback Functions

	// Secondary Attribute Callback Functions
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	// Secondary Attribute Callback Functions

	/* This function will be called everytime before any attribute has changed.
	 * @param[0] Attribute => Actual attribute that will be changed.
	 * @param[1] NewValue => New value for this attribute.
	 * Use this function to clamp values for the relevant attribute. No game logic should be
	 * implemented in this function.
	 * -> Later operations recalculate the current value from all modifiers. (Which means reclamp could
	 * be needed.)
	 * -> Does not change the modifier, just the value from querying the modifier.
	 * -> Not best function to clamp values.
	 */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	/* This function is better version for change and get control over the effected attribute.
	 * This function will kicked of after a Gameplay Effect changes an attribute.
	 * Data has a lot of information regarding with the change for example:
	 * causer of this effect. Target of this effect. Effect properties etc. */
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
};
