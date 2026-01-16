// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraAttributeMenuWC;
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
	/*
	 * This function will act like a singleton class for the Overlay Widget Controller.
	 * If this controller is valid then we will return this information.
	 * Otherwise, we will create this controller with parameters and return it.
	 */
	UAuraOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WcParams);

	/*
	 * This function will act like a singleton class for the Attribute Menu Widget Controller.
	 * If this controller is valid then we will return this information.
	 * Otherwise, we will create this controller with parameters and return it.
	 */
	UAuraAttributeMenuWC* GetAttributeMenuWidgetController(const FWidgetControllerParams& WcParams);

	/*
	 * This function is responsible from initialize widget & widget controller,
	 * bind them together, and show this widget in the screen.
	 */
	void InitOverlay(UAbilitySystemComponent* ASC, UAttributeSet* AS, APlayerState* PS, APlayerController* PC);

private:
	/* Overlay widget related properties */
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UAuraOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraOverlayWidgetController> OverlayWidgetControllerClass;
	/* End overlay widget related properties */
	
	/* Attribute menu related properties */
	UPROPERTY()
	TObjectPtr<UAuraAttributeMenuWC> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraAttributeMenuWC> AttributeMenuWidgetControllerClass;
	/* End Attribute menu widget controller */
};
