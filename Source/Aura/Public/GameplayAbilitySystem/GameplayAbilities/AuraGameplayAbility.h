// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * Gameplay Abilities are actions or skills that an actor can perform in the game.
 * It defines what an ability does and the conditions under which it can be used.
 * It's running asynchronously so multi-stage tasks can be performed like;
 * Character animation, particle and sound effects etc.
 * It has built in concept of costs and cooldown where attribute resources must be present
 * in a sufficient amount to pay for an ability activation.
 * It also tracks the cooldown periods to prevent an ability from being used again until the
 * cooldown period is over.
 *
 * Ability Task:
 * They perform asynchronous work during a gameplay abilities execution. They can affect
 * execution flow by broadcasting delegates. They can self-terminate by calling the EndTask
 * function, or it can wait to be terminated automatically when the Gameplay Ability that ran it ends.
 *
 * Granting Abilities:
 * To use a gameplay ability, the ability system component must be granted the ability.
 * So gameplay ability spec is created and the spec defines the details pertaining to that particular
 * ability, including the gameplay ability, class itself, level etc.
 * They granted on the server, then the ability spec replicates down to the owning client so they can
 * activate it from their gameplay abilities.
 * They have activated logic once they are activated. They will be considered as active until either
 * ability ended or canceled. (Cancel externally)
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
};
