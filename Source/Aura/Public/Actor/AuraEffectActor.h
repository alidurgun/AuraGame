// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActiveGameplayEffectHandle.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EGameplayEffectApplyType
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EGameplayEffectRemoveType
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAuraEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// This function will be called from BP side, and it will affect the given TargetActor with specified effect.
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	// GameplayEffects
	// Gameplay Effect class to specify which effect should be applied.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS|Gameplay Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS|Gameplay Effects")
	EGameplayEffectApplyType InstantGameplayEffectApplyType{EGameplayEffectApplyType::DoNotApply};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS|Gameplay Effects")
	TSubclassOf<UGameplayEffect> HasDurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS|Gameplay Effects")
	EGameplayEffectApplyType HasDurationGameplayEffectApplyType{EGameplayEffectApplyType::DoNotApply};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS|Gameplay Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS|Gameplay Effects")
	EGameplayEffectApplyType InfiniteGameplayEffectApplyType{EGameplayEffectApplyType::DoNotApply};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS|Gameplay Effects")
	EGameplayEffectRemoveType InfiniteGameplayEffectRemoveType{EGameplayEffectRemoveType::DoNotRemove};
	// GameplayEffects

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS|Gameplay Effects")
	float ActorLevel{ 1.0f };

private:
	/* This map will fill with information of infinite GameplayEffect and targeted ASC. */
	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveGameplayEffects;

	/* Function to remove infinite gameplay effects. */
	void RemoveInfiniteGameplayEffects(AActor* TargetActor);
};
