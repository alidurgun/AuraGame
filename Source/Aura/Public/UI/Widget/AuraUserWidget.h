// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * This class will act like a base class for the widgets. Widgets will depend on the Widget Controller.
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	/* This function will serve as a callback function for the widget controller.
	 * It will be called when the WidgetController has been set.
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
