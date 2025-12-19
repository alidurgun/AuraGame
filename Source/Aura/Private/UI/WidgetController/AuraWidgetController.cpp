// Project has been managed by Ali Durgun


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WcParams)
{
	AbilitySystemComponent = WcParams.AbilitySystemComponent;
	AttributeSet = WcParams.AttributeSet;
	PlayerState = WcParams.PlayerState;
	PlayerController = WcParams.PlayerController;
}

void UAuraWidgetController::BroadcastInitialValues()
{
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}
