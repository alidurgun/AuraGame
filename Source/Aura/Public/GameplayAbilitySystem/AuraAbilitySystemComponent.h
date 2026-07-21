// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

/* Delegates are perfect for send data to the previous layer in the topology.
 * It can be associated with Notifiers and Listeners.
 * In here we will broadcast tags that we have retrieved from the gameplay effect.
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectTagAppliedSignature, const FGameplayTagContainer&);

/*
 * This delegate will be responsible from ability given mechanism. It will be broadcasted whenever
 * the ability has been given to the character.
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven, UAuraAbilitySystemComponent*);

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	/* This function will be called when the ability actor has been initialized with necessary properties.
	 * This function will bind to the OnGameplayEffectAppliedDelegateToSelf delegate to listen any
	 * gameplay effect applied to the Ability System Component.
	 */
	void AbilityActorInfoSet();
	
	FOnEffectTagAppliedSignature OnEffectTagApplied;

	/*
	 * Client => this is client RPC.
	 * Reliable => Guaranteed to reach the client even in the case of packet loss. It will keep sending
	 * until it receives the confirmation.
	 */
	UFUNCTION(Client,Reliable)
	void GameplayEffectApplied(UAbilitySystemComponent* Source, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle) const;

	void AddCharacterAbilites(const TArray<TSubclassOf<UGameplayAbility>>& abilities);

	void AbilityInputTagPressed(FGameplayTag Tag);

	void AbilityInputTagHeld(FGameplayTag Tag);

	void AbilityInputTagReleased(FGameplayTag Tag);

	FAbilitiesGiven AbilitiesGivenDelegate;
	bool bStartupAbilitiesGiven = false; // to check if the broadcast occurs first.
};
