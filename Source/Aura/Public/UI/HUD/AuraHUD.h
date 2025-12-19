// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UAuraOverlayWidgetController;
class UAuraUserWidget;
struct FWidgetControllerParams;

/**
 * This class needed to show overlay in the Game Screen and draw widgets in this overlay.
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	/*
	 * This function will act like a singleton class for the Overlay Widget Controller.
	 * If this controller is valid then we will return this information.
	 * Otherwise we will create this controller with parameters and return it.
	 */
	UAuraOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WcParams);

	/*
	 * This function is responsible from initialize widget & widget controller,
	 * bind them together, and show this widget in the screen.
	 */
	void InitOverlay(UAbilitySystemComponent* ASC, UAttributeSet* AS, APlayerState* PS, APlayerController* PC);

private:
	// Class information will be needed also.
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UAuraOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraOverlayWidgetController> OverlayWidgetControllerClass;
};
