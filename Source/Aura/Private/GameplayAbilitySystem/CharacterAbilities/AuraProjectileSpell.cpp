// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/CharacterAbilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Projects.h"
#include "GameplayAbilitySystem/AuraAbilitySystemComponent.h"
#include "GameplayAbilitySystem/CharacterAbilities/AuraProjectile.h"
#include "GameplayAbilitySystem/GameplayTags/AuraGameplayTags.h"
#include "Interface/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogTemp, Warning, TEXT("ActivateAbility called at time: %f - Ability: %s - Role: %d"), 
		GetWorld()->GetTimeSeconds(), 
		*GetName(), 
		GetActorInfo().OwnerActor->GetLocalRole());
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileLocation)
{
	// only server can activate ability.
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;
	
	if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector ProjectileSpawnLocation = CombatInterface->GetCombatSocketLocation();

		// TODO: Set the Projectile Rotation.
		FRotator Rotation{(ProjectileLocation - ProjectileSpawnLocation).Rotation()};
		Rotation.Pitch = 0.0f; // want that the projectile should go parallel to the ground.
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(ProjectileSpawnLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		// End Set the Projectile Rotation.

		// Spawns given class and returns class T pointer. It gives opportunity to set parameters
		// beforehand. Caller must invoke FinishSpawningActor after this one.
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(), // Built in function that is using input param ActorInfo
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// TODO: Give the projectile a gameplay effect spec for causing damage.
		// create ASC.
		UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		// Create FGameplayEffectSpecHandle and set it for the AuraProjectile side.
		FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass,GetAbilityLevel(),SourceASC->MakeEffectContext());
		FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

		// This damage value will be evaluated according to ability level. Relevant damage value will retrieve
		// from the given CurveTable.
		const float CurrentDamage = Damage.GetValueAtLevel(GetAbilityLevel());
		
		// SetByCaller is a key value pair that will be used in the Gameplay Effect.
		// So the GameplayTag that we are using here is the key value and the Magnitude is the value.
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
			SpecHandle,
			GameplayTags.Ability_FireBolt_Damage,
			CurrentDamage);
		
		Projectile->DamageEffectSpecHandle = SpecHandle;
		// End Give the projectile a gameplay effect spec for causing damage.

		UE_LOG(LogTemp, Warning, TEXT("HasAuthority: %d"), GetAvatarActorFromActorInfo()->HasAuthority());
		Projectile->FinishSpawning(SpawnTransform);
	}
}
