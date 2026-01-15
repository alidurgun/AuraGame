// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraAttributeMenuWC.generated.h"

/**
 * This class will be used by attribute menu widgets.
 */
UCLASS()
class AURA_API UAuraAttributeMenuWC : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
};
