// Project has been managed by Ali Durgun


#include "Character/Enemy/EnemyCharacter.h"

#include "NavigationSystemTypes.h"
#include "Components/CapsuleComponent.h"
#include "GameplayAbilitySystem/AuraAbilitySystemComponent.h"
#include "GameplayAbilitySystem/AuraAttributeSet.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// We don't need to carry ASC to newly created enemies. They will have basic functionality.
	// Therefore, bind it directly in the Pawn.
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	
	// This will be AI controlled character therefore set it's replicated mode to minimal.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AEnemyCharacter::Highlight()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);

	if (WeaponMesh)
	{
		WeaponMesh->SetRenderCustomDepth(true);
		WeaponMesh->SetCustomDepthStencilValue(250);
	}
}

void AEnemyCharacter::Unhighlight()
{
	GetMesh()->SetRenderCustomDepth(false);
	if (WeaponMesh)
	{
		WeaponMesh->SetRenderCustomDepth(false);
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Hence Ability System Control has been bound to pawn directly, set it's owner and avatar in BeginPlay
	if (AbilitySystemComponent) // It should be already valid but just to be in the safe side.
	{
		// For the enemy pawn both owner and avatar should be same and equal to "this".
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}
}
