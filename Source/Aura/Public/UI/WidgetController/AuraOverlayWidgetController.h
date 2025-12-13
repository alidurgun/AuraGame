// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraOverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
/*
 * FOnHealthChangedSignature => Delegate Name. F at beginning and Signature and ending is a common
 * signatures for creating delegate functions. Their corresponding callback functions will have name
 * without F and Signature.
 * float => Parameter type.
 * NewHealth => Parameter Name.
 */ 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

/**
 * This widget controller will be used by overlay widget.
 * BlueprintType => It allows to use this class as a type in the BP side. (Such as Cast)
 * Blueprintable => It allows to create a BP class based on this class.
 * For the health and mana WBPs we're going to use this controller to set their percentages.
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAuraOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

protected:
	/*
	 * This callback function will be called whenever the Health attribute has changed in Aura AttributeSet.
	 * This function has signature for GetGameplayAttributeValueChangeDelegate delegate.
	*/
	void HealthChanged(const FOnAttributeChangeData& Health) const;
	
	/*
	 * This callback function will be called whenever the MaxHealth attribute has changed in Aura AttributeSet.
	 * This function has signature for GetGameplayAttributeValueChangeDelegate delegate.
	*/
	void MaxHealthChanged(const FOnAttributeChangeData& MaxHealth) const;

	/*
	 * This callback function will be called whenever the Mana attribute has changed in Aura AttributeSet.
	 * This function has signature for GetGameplayAttributeValueChangeDelegate delegate.
	*/
	void ManaChanged(const FOnAttributeChangeData& Mana) const;

	/*
	 * This callback function will be called whenever the MaxMana attribute has changed in Aura AttributeSet.
	 * This function has signature for GetGameplayAttributeValueChangeDelegate delegate.
	*/
	void MaxManaChanged(const FOnAttributeChangeData& MaxMana) const;
};
