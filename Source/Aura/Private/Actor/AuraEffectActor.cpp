// Project has been managed by Ali Durgun


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// removed sphere, mesh and overlap related functions to give designer freedom to modify them
	// according to their needs.
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")));
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// Hence all enemies have this tag we can check it.
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bCanEnemyInteract) return;
	checkf(GameplayEffectClass, TEXT("AuraEffectActor should have valid GameplayEffect class to apply effect."));
	
	// UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent is a function that do cast and other
	// manuel operations that we are doing to create UAbilitySystemComponent. Can return nullptr!
	if (UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		/** GameplayEffectContext is closely related to GameplayEffects. It will contain some informations
		 * such as: Who is making this effect. What is the effect. What is the effect type etc.
		 * FGameplayEffectContextHandle is a lightweight version for this context. Handle is wrapper.
		 */
		FGameplayEffectContextHandle GEContextHandle = TargetAsc->MakeEffectContext();
		GEContextHandle.AddSourceObject(this);

		/** TargetAsc->MakeOutgoingSpec => To create a FGameplayEffectSpecHandle object.
		 * @param[0] => Specify the UGameplayEffect class to apply the effect.
		 * @param[1] => Specify the level of this effect. Game can have multiple levels. (1.0f for now)
		 * @param[2] => FGameplayEffectContextHandle.
		 * This is wrapper for the FGameplayEffectSpec. In order to access FGameplayEffectSpec use Data member.
		 */
		FGameplayEffectSpecHandle GESpecHandle = TargetAsc->MakeOutgoingSpec(GameplayEffectClass, ActorLevel,
			GEContextHandle);

		/** This function will aply the specified effect on the TargetAsc. According to the given
		* GameplayEffectClass; actor's ability will be effected.
		* @param[0] => Specify FGameplayEffectSpec. (This holds information for which attribute should be effected.)
		* @param[1] => FPredictionKey, this is for compansete the lag issue for the Multiplayer game.
		*/
		FActiveGameplayEffectHandle GameplayEffectHandle = TargetAsc->ApplyGameplayEffectSpecToSelf(*GESpecHandle.Data.Get());

		/*
		* FGameplayEffectSpecHandle has information about GameplayEffects. Also for the duration Policy.
		* Data.Get()->Def.Get() is representation of the real GameplayEffect.
		*/
		if (GESpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite
			&& InfiniteGameplayEffectRemoveType == EGameplayEffectRemoveType::RemoveOnEndOverlap)
		{
			// Current Gameplay effect is infinite with remove onendoverlap policy.
			// Store it for remove it in the onendoverlap function.
			ActiveGameplayEffects.Add(GameplayEffectHandle, TargetAsc);
		}

		if (GESpecHandle.Data.Get()->Def.Get()->DurationPolicy != EGameplayEffectDurationType::Infinite)
		{
			Destroy();
		}
	}
	
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bCanEnemyInteract) return;
	/*
	 * Multiple effects can be applied at the same time.
	 */
	if (InstantGameplayEffectApplyType == EGameplayEffectApplyType::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (HasDurationGameplayEffectApplyType == EGameplayEffectApplyType::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, HasDurationGameplayEffectClass);
	}
	if (InfiniteGameplayEffectApplyType == EGameplayEffectApplyType::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bCanEnemyInteract) return;
	/*
	* Multiple effects can be applied at the same time.
	*/
	if (InstantGameplayEffectApplyType == EGameplayEffectApplyType::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (HasDurationGameplayEffectApplyType == EGameplayEffectApplyType::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, HasDurationGameplayEffectClass);
	}
	if (InfiniteGameplayEffectApplyType == EGameplayEffectApplyType::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	if (InfiniteGameplayEffectRemoveType == EGameplayEffectRemoveType::RemoveOnEndOverlap)
	{
		RemoveInfiniteGameplayEffects(TargetActor);
	}
}

void AAuraEffectActor::RemoveInfiniteGameplayEffects(AActor* TargetActor)
{
	if (ActiveGameplayEffects.IsEmpty()) return;
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		/* Handles will be removed after. */
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (auto GameplayEffectHandle : ActiveGameplayEffects)
		{
			if (GameplayEffectHandle.Value == TargetASC)
			{
				HandlesToRemove.AddUnique(GameplayEffectHandle.Key);
				TargetASC->RemoveActiveGameplayEffect(GameplayEffectHandle.Key, 1);
			}
		}
		for (auto element : HandlesToRemove)
		{
			ActiveGameplayEffects.Remove(element);
		}
	}
	
}
