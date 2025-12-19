// Project has been managed by Ali Durgun


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraOverlayWidgetController.h"

UAuraOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WcParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UAuraOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WcParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(UAbilitySystemComponent* ASC, UAttributeSet* AS, APlayerState* PS, APlayerController* PC)
{
	checkf(OverlayWidgetClass, TEXT("No Overlay Widget Class has found. Set it in the BP!"));
	checkf(OverlayWidgetControllerClass, TEXT("No Overlay Widget Controller Class has found. Set it in the BP!"));

	if (UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass))
	{
		OverlayWidget = Cast<UAuraUserWidget>(Widget);
	}

	const FWidgetControllerParams WCParams(ASC,AS,PS,PC);
	GetOverlayWidgetController(WCParams);
	
	if (OverlayWidget && OverlayWidgetController)
	{
		OverlayWidget->SetWidgetController(OverlayWidgetController);
		OverlayWidgetController->BroadcastInitialValues();
	}

	OverlayWidget->AddToViewport();
}


