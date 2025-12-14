// Project has been managed by Ali Durgun


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AssetTypeCategories.h"

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
		FGameplayEffectSpecHandle GESpecHandle = TargetAsc->MakeOutgoingSpec(GameplayEffectClass, 1.0f,
			GEContextHandle);

		/** This function will aply the specified effect on the TargetAsc. According to the given
		* GameplayEffectClass; actor's ability will be effected.
		* @param[0] => Specify FGameplayEffectSpec. (This holds information for which attribute should be effected.)
		* @param[1] => FPredictionKey, this is for compansete the lag issue for the Multiplayer game.
		 */
		TargetAsc->ApplyGameplayEffectSpecToSelf(*GESpecHandle.Data.Get());
	}
}
