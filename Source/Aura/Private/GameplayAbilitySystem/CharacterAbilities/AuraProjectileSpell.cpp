// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/CharacterAbilities/AuraProjectileSpell.h"

#include "GameplayAbilitySystem/CharacterAbilities/AuraProjectile.h"
#include "Interface/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// only server can activate ability.
	if (!HasAuthority(&ActivationInfo)) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector ProjectileSpawnLocation = CombatInterface->GetCombatSocketLocation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(ProjectileSpawnLocation);

		// TODO: Set the Projectile Rotation.

		// Spawns given class and returns class T pointer. It gives opportunity to set parameters beforehand.
		// caller must invoke FinishSpawningActor after this one.
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(), // Built in function that is using input param ActorInfo
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// TODO: Give the projectile a gameplay effect spec for causing damage.

		Projectile->FinishSpawning(SpawnTransform);
	}
}
