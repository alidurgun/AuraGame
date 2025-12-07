// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * This class will be our widget controller. Its main responsibility will be retrieve any relevant data from the
 * Model(System) (Health, Mana, Abilities etc.)
 * WidgetController will be depend on the model. It has no information about UserWidgets that bound
 * to this controller.
 * For now we want to get data from 4 main classes.
 * 1-) Ability System Component
 * 2-) Attribute Set
 * 3-) Player State
 * 4-) Player Controller
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;
};
