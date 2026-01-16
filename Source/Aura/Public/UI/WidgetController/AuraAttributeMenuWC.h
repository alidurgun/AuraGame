// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraAttributeMenuWC.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

/**
 * This class will be used by attribute menu widgets.
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAuraAttributeMenuWC : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
	/* Our delegate function to broadcast value to the widget. */
	UPROPERTY(BlueprintAssignable)
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	/* Attribute info class to access related tags. */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;
};
