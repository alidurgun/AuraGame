// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySystem/GameplayAbilities/AuraGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"

class AAuraProjectile;
/**
 * We will use this class for every projectile spell.
 * This class will act like a base for all projectile spells. So it must be generic.
 *
 * For the Spawning Projectiles:
 * Only server should be able to spawn projectile.
 * Projectile should be spawned from the tip of the weapon that character is using.
 * Projectile class should not be depend on the character class.
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& ProjectileLocation);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAuraProjectile> ProjectileClass;
};
