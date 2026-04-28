// Project has been managed by Ali Durgun


#include "Character/BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"
#include "GameplayAbilitySystem/AuraAbilitySystemComponent.h"
#include "GeometryCollection/GeometryCollectionParticlesData.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// To disable camera change when there is another character nearby.
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));

	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	IsAlive = true;
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

const FVector ABaseCharacter::GetCombatSocketLocation_Implementation() const
{
	check(WeaponMesh)
	return WeaponMesh->GetSocketLocation(WeaponTipSocketName);
}

UAnimMontage* ABaseCharacter::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void ABaseCharacter::Die()
{
	// detach weapon from the character.
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	MulticastHandleDeath_Implementation();
}

bool ABaseCharacter::IsAlive_Implementation() const
{
	return IsAlive;
}

AActor* ABaseCharacter::GetAvatar_Implementation()
{
	return this;
}

void ABaseCharacter::Dissolve()
{
	if (BodyDissolveMaterial)
	{
		UMaterialInstanceDynamic* BodyDynamicInstance = UMaterialInstanceDynamic::Create(BodyDissolveMaterial, this);
		GetMesh()->SetMaterial(0, BodyDynamicInstance);
		BodyDissolveTimeline(BodyDynamicInstance);
	}
	if (WeaponDissolveMaterial)
	{
		UMaterialInstanceDynamic* WeaponDynamicInstance = UMaterialInstanceDynamic::Create(WeaponDissolveMaterial, this);
		WeaponMesh->SetMaterial(0,WeaponDynamicInstance);
		WeaponDissolveTimeline(WeaponDynamicInstance);
	}

}

void ABaseCharacter::MulticastHandleDeath_Implementation()
{
	// To make weapon fell down and interact with the ground.
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	// Body also should fell down and interact with the gravity etc.
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	// Blocking WorldStatic so it won't ignore the pillars etc.
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	// Disable the capsule component too, so character won't get blocked.
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Call Dissolve for both client and server.
	Dissolve();

	IsAlive = false;
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


