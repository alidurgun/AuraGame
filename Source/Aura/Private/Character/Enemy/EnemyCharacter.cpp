// Project has been managed by Ali Durgun


#include "Character/Enemy/EnemyCharacter.h"


#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameplayAbilitySystem/AuraAbilitySystemBPLibrary.h"
#include "GameplayAbilitySystem/AuraAbilitySystemComponent.h"
#include "GameplayAbilitySystem/AuraAttributeSet.h"
#include "UI/Widget/AuraUserWidget.h"

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

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
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

	// Hence Ability System Control has been bound to pawn directly, set its owner and avatar in BeginPlay
	InitAbilityComponent();

	if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AuraUserWidget->SetWidgetController(this);
	}

	if (const UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& data)
			{
				OnHealthChanged.Broadcast(data.NewValue);
			});
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& data)
			{
				OnMaxHealthChanged.Broadcast(data.NewValue);
			});

		OnHealthChanged.Broadcast(AuraAS->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	}
}

void AEnemyCharacter::InitAbilityComponent()
{
	check(AbilitySystemComponent) // It should be already valid.
	
	// For the enemy pawn both owner and avatar should be same and equal to "this".
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultValues();
}

void AEnemyCharacter::InitializeDefaultValues() const
{
	UAuraAbilitySystemBPLibrary::InitializeDefaultAttributes(this, CharacterClass,
		CharacterLevel, AbilitySystemComponent);
}
