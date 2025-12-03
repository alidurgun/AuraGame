// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	/* In order to set owner and avatar actors in the InitAbilityActorInfo we will need those 2 functions.*/
	/* It will be called when the actor has been possessed */
	virtual void PossessedBy(AController* NewController) override;
	/* It will be called when the player state has been bound with the character*/
	virtual void OnRep_PlayerState() override;

private:
	void InitAbilityComponent();
};
