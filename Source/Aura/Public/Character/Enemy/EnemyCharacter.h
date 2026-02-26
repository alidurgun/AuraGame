// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interface/EnemyInterface.h"
#include "UI/WidgetController/AuraOverlayWidgetController.h"
#include "EnemyCharacter.generated.h"

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
	FORCEINLINE virtual int32 GetPlayerLevel() const override { return PlayerLevel; }
	/* End Combat Interface */

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Default")
	int32 PlayerLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
