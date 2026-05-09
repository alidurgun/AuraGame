// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySystem/GameplayAbilities/AuraGameplayAbility.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Damage")
	FScalableFloat Damage; // This will be showed as CT in the Editor Side.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Damage|Damage Types")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
};
