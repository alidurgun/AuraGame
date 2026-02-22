// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/CharacterAbilities/AuraProjectileSpell.h"

#include "GameplayAbilitySystem/CharacterAbilities/AuraProjectile.h"
#include "Interface/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileLocation)
{
	// only server can activate ability.
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;
	
	if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector ProjectileSpawnLocation = CombatInterface->GetCombatSocketLocation();

		FRotator Rotation{(ProjectileLocation - ProjectileSpawnLocation).Rotation()};
		Rotation.Pitch = 0.0f; // want that the projectile should go parallel to the ground.
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(ProjectileSpawnLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		// TODO: Set the Projectile Rotation.

		// Spawns given class and returns class T pointer. It gives opportunity to set parameters
		// beforehand. Caller must invoke FinishSpawningActor after this one.
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
