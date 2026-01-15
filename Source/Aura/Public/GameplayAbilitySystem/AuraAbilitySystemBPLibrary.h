// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemBPLibrary.generated.h"

class UAuraOverlayWidgetController;
/**
 * To make some functions usable on the BP side without binding them to a specific gameplay object type we
 * will use BlueprintFunctionLibrary. We will use static functions in this class.
 * To expose it to the BP side we can use:
 * UFUNCTION(BlueprintCallable) notation.
 */
UCLASS()
class AURA_API UAuraAbilitySystemBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/* This function will return the valid Overlay Widget Controller.
	 * in param[0] UObject* WorldContex => The object's representation in the world context. Hence, the
	 * static functions may not exist in the world we need a world context to track or affect the
	 * object that is representing in the world.
	 */
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemBPLibrary|WidgetController")
	static UAuraOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContext);
};
