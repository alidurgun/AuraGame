// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySystem/GameplayAbilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * Summon ability that will be used in the game. Every character will have this summon ability.
 * Summoned thing will be either some pet or it will be enemies like demon or goblin or ghoul etc.
 */
UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:
	// To choose spawn locations.
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	// number of items going to be spawned.
	UPROPERTY(EditDefaultsOnly, Category="Summoning")
	int32 NumOfSpawned = 0;

	// which classes(Pawns) are going to be spawned.
	UPROPERTY(EditDefaultsOnly, Category="Summoning")
	TArray<TSubclassOf<APawn>> SpawnedClasses;

	// minimum distance for summoning
	UPROPERTY(EditDefaultsOnly, Category="Summoning")
	float MinSpawnDistance {50.0f};

	// maximum distance for summoning
	UPROPERTY(EditDefaultsOnly, Category="Summoning")
	float MaxSpawnDistance {250.0f};

	// Spawn spread for spawning items.
	UPROPERTY(EditDefaultsOnly, Category="Summoning")
	float SpawnSpread {90.0f};
};
