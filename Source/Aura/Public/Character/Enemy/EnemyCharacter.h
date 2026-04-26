// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "GameplayAbilitySystem/DataAsset/CharacterClassInfo.h"
#include "Interface/EnemyInterface.h"
#include "UI/WidgetController/AuraOverlayWidgetController.h"
#include "EnemyCharacter.generated.h"

class AAuraAIController;
class UBehaviorTree;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public ABaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	/* Enemy Interface */
	virtual void Highlight() override;

	virtual void Unhighlight() override;
	/* End Enemy Interface */

	/* Combat Interface */
	FORCEINLINE virtual int32 GetPlayerLevel() const override { return CharacterLevel; }
	/* End Combat Interface */

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void EnemyHitReaction(const FGameplayTag Tag, int32 NewTagCount);

	virtual void Die() override;

	// Override the PossessedBy function to get the AIController.
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor> CombatTarget;

	virtual void SetCombatTarget_Implementation(AActor* CombatTargetIn) override;
	virtual AActor* GetCombatTarget_Implementation() const override;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityComponent() override;

	virtual void InitializeDefaultValues() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Default")
	int32 CharacterLevel{1};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Default")
	ECharacterClass CharacterClass{ECharacterClass::Warrior};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
private:
	float BaseWalkSpeed{250.0f};

	bool bHitReacting{false};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float LifeSpan{5.0f};
};
