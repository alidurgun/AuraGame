// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/CombatInterface.h"
#include "BaseCharacter.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual const FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) const override;

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

	virtual void Die() override;

	/* To get whether the current actor is alive or not! */
	virtual bool IsAlive_Implementation() const override;

	// To get the current actor.
	virtual AActor* GetAvatar_Implementation() override;

	// Function to create a dynamic material instance. Then it will call the dissolvetimeline functions for body
	// and weapon to make them dissolve in time.
	void Dissolve();

	// Body dissolve function. It will work with a timeline.
	UFUNCTION(BlueprintImplementableEvent)
	void BodyDissolveTimeline(UMaterialInstanceDynamic* BodyDissolve);

	// Weapon dissolve function. It will work with a timeline.
	UFUNCTION(BlueprintImplementableEvent)
	void WeaponDissolveTimeline(UMaterialInstanceDynamic* WeaponDissolve);

	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	
protected:	
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere, Category="Combat")
	FName LeftHandSocketName;

	UPROPERTY(EditAnywhere, Category="Combat")
	FName RightHandSocketName;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	/* Function to initialize ability system component for the characters in the game. */
	virtual void InitAbilityComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> PrimaryDefaultAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> SecondaryDefaultAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> VitalDefaultAttributes;

	virtual void InitializeDefaultValues() const;

	void AddCharacterAbilities() const;

private:
	/* Apply given Gameplay Effect class to the self for given level. */
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const;

	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category="Animations")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastHandleDeath();

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category="Dissolve")
	TObjectPtr<UMaterialInstance> BodyDissolveMaterial;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category="Dissolve")
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterial;

	bool IsAlive;

	UPROPERTY(EditAnywhere, Category="Combat")
	TArray<FTaggedMontage> AttackMontages;
};
