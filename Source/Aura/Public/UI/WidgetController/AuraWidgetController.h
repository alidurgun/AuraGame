// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

// To initialize properties easy.
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}

	FWidgetControllerParams(UAbilitySystemComponent* ASC, UAttributeSet* AS, APlayerState* PS, APlayerController* PC)
		: AbilitySystemComponent(ASC), AttributeSet(AS), PlayerState(PS), PlayerController(PC) {}

	// Attributes should be initialized in the struct.
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController{nullptr};
};

/**
 * This class will be our widget controller. Its main responsibility will retrieve any relevant data from the
 * Model(System) (Health, Mana, Abilities etc.)
 * WidgetController will be depended on the model. It has no information about UserWidgets that bound
 * to this controller.
 * For now, we want to get data from 4 main classes.
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
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WcParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;
};
