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

	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, Category="Vital Stats")
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth, Category="Vital Stats")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, Category="Vital Stats")
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, Category="Vital Stats")
	FGameplayAttributeData MaxMana;
	// Attributes

	// AttributeAccessors
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	// AttributeAccessors

	// Attribute Callback Functions
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	// Attribute Callback Functions

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
	 * causer of this effect. Target of this effect. Effect properties etc.
	 */
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
};
