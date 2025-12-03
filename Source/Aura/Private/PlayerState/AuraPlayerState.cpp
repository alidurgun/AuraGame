// Project has been managed by Ali Durgun


#include "PlayerState/AuraPlayerState.h"

#include "GameplayAbilitySystem/AuraAbilitySystemComponent.h"
#include "GameplayAbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	// this variable defines how often server will update clients.
	// server will try to catch this value.
	NetUpdateFrequency = 100.0f;

	// construct Ability System Component & Attribute Set in here for aura character.
	// Aura Character will be player controlled character therefore we will save the
	// ASC and AS for reuse even after pawn died or destroyed.
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	
	// PlayerState will be associated with player controlled class therefore set its replication mode to mixed.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
