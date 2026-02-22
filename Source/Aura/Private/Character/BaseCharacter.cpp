// Project has been managed by Ali Durgun


#include "Character/BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameplayAbilitySystem/AuraAbilitySystemComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// To disable camera change when there is another character nearby.
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));

	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

const FVector ABaseCharacter::GetCombatSocketLocation() const
{
	check(WeaponMesh)
	return WeaponMesh->GetSocketLocation(WeaponTipSocketName);
}

void ABaseCharacter::InitAbilityComponent()
{
}

void ABaseCharacter::InitializeDefaultValues() const
{
	ApplyEffectToSelf(PrimaryDefaultAttributes,1.0f);
	ApplyEffectToSelf(SecondaryDefaultAttributes, 1.0f);
	ApplyEffectToSelf(VitalDefaultAttributes,1.0f);
}

void ABaseCharacter::AddCharacterAbilities() const
{
	// Only server can grant ability. So if this is not server side then return immediately.
	if (!HasAuthority()) return;

	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	// Ability System Component should be responsible from giving abilities.

	AuraASC->AddCharacterAbilites(StartupAbilities);
}

void ABaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const
{
	check(GameplayEffect);
	check(IsValid(AbilitySystemComponent));
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, Level,EffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), AbilitySystemComponent);
}
