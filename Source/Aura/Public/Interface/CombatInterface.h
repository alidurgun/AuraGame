// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// BlueprintType => In order to cast to CombatInterface in the BP side.
// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual int32 GetPlayerLevel() const { return 0; }
	// To get the location for the tip of the weapon.
	virtual const FVector GetCombatSocketLocation() const { return FVector::ZeroVector; }

	// When we use BlueprintImplementableEvent we don't use virtual keyword.
	// It will show as "Event Update Facing Target" in BP side.(BlueprintImplementableEvent used)
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);
};
