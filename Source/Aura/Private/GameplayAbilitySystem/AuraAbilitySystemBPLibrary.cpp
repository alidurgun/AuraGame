// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/AuraAbilitySystemBPLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "PlayerState/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UAuraOverlayWidgetController* UAuraAbilitySystemBPLibrary::GetOverlayWidgetController(const UObject* WorldContext)
{
	// we need player controller to access hud.
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext,0))
	{
		// from hud we can access the overlay widget controller.
		if (AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>())
		{
			/* Required parameters to create overlay widget controller. */
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			/* end Required parameters to create overlay widget controller. */
			FWidgetControllerParams WCParams(ASC,AS,PS,PC);
			return AuraHUD->GetOverlayWidgetController(WCParams);
		}
	}
	return nullptr;
}
