// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

// This will be another output pin for the CreateTargetDataUnderMouse function.
// To Execute this pin we have to broadcast this value.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FVector&, Data);

/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:
	/*
	 * This function will be called from the BP side. It will be latent function.
	 * We are using DefaultToSelf option because we will call this function from the ability that we are using
	 * DisplayName => name it will be available on the BP side.
	 * HidePin => To hide this relevant pin.
	 * DefaultToSelf => Pass self(this) as default for the input parameter.
	 */
	UFUNCTION(BlueprintCallable, Category="Ability", meta=(DisplayName = "Create Target Data Under Mouse", HidePin="OwningAbility", DefaultToSelf="OwningAbility"))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	// It is working as an extra execution pin. We have to use BlueprintAssignable to do that.
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;

private:
	// Called to trigger the actual task once the delegates have been set up.
	virtual void Activate() override;
};
