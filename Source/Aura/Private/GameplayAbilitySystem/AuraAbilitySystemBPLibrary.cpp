// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/AuraAbilitySystemBPLibrary.h"

#include "ToolContextInterfaces.h"
#include "Common/AuraGameplayEffectContext.h"
#include "GameMode/AuraGameModeBase.h"
#include "GameplayAbilitySystem/AuraAttributeSet.h"
#include "GameplayAbilitySystem/DataAsset/CharacterClassInfo.h"
#include "Interface/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerState/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "Widgets/Text/ISlateEditableTextWidget.h"

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

UAuraAttributeMenuWC* UAuraAbilitySystemBPLibrary::GetAttributeMenuWidgetController(const UObject* WorldContext)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext,0))
	{
		if (AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>())
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			FWidgetControllerParams WCParams(ASC,AS,PS,PC);
			return AuraHUD->GetAttributeMenuWidgetController(WCParams);
		}
	}
	return nullptr;
}

void UAuraAbilitySystemBPLibrary::InitializeDefaultAttributes(const UObject* WorldContext,
	ECharacterClass CharacterClass, int32 Level, UAbilitySystemComponent* ASC)
{
	// Get the GameMode
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContext));
	if (AuraGameMode == nullptr) return;

	UCharacterClassInfo* CharClassInfo = AuraGameMode->CharacterClassInfo;
	FCharacterClassDefaultInfo ClassDefaultInfo = CharClassInfo->GetCharacterClassDefaultInfo(CharacterClass);

	ApplyEffectToSelf(ClassDefaultInfo.PrimaryEffects, Level, ASC);
	ApplyEffectToSelf(CharClassInfo->SecondaryAttributes, Level, ASC);
	ApplyEffectToSelf(CharClassInfo->VitalAttributes, Level, ASC);
}

void UAuraAbilitySystemBPLibrary::GiveCommonAbilities(const UObject* WorldContext, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	// first get the AAuraGameModeBase.
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContext));
	if (AuraGameMode == nullptr) return;

	// then we can retrieve the characterclassinfo.
	UCharacterClassInfo* CharacterClassInfo = AuraGameMode->CharacterClassInfo;
	for (auto AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		// Then we can give this ability to ASC.
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		ASC->GiveAbility(AbilitySpec);
	}

	// Give startup abilities
	FCharacterClassDefaultInfo DefaultInfo = CharacterClassInfo->GetCharacterClassDefaultInfo(CharacterClass);
	for (auto abilities : DefaultInfo.StartupAbilities)
	{
		// Hence the enemies will have different level during the game. We need a CombatInterface to get the
		// player level to give ability in correct level.
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor()))
		{
			FGameplayAbilitySpec spec = FGameplayAbilitySpec(abilities, CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(spec);
		}
	}
}

UCharacterClassInfo* UAuraAbilitySystemBPLibrary::GetCharacterClassInfo(const UObject* WorldContext)
{
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContext));
	if (AuraGameMode == nullptr) return nullptr;
	return AuraGameMode->CharacterClassInfo;
}

bool UAuraAbilitySystemBPLibrary::IsBlockedHit(const FGameplayEffectContextHandle& ContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(ContextHandle.Get()))
	{
		return AuraEffectContext->IsBlockedHit();
	}
	return false;
}

bool UAuraAbilitySystemBPLibrary::IsCriticalHit(const FGameplayEffectContextHandle& ContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(ContextHandle.Get()))
	{
		return AuraEffectContext->IsCriticalHit();
	}
	return false;
}

void UAuraAbilitySystemBPLibrary::SetBlockedHit(FGameplayEffectContextHandle& ContextHandle, const bool IsInBlock)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(ContextHandle.Get()))
	{
		AuraEffectContext->SetBlockedHit(IsInBlock);
	}
}

void UAuraAbilitySystemBPLibrary::SetCriticalHit(FGameplayEffectContextHandle& ContextHandle, const bool IsInCrit)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(ContextHandle.Get()))
	{
		AuraEffectContext->SetCriticalHit(IsInCrit);
	}
}

void UAuraAbilitySystemBPLibrary::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, int32 Level, UAbilitySystemComponent* ASC)
{
	// Hence MMC is using source object from context handle we have to define that in here too.
	// Otherwise, it will lead to crash.
	AActor* AvatarActor = ASC->GetAvatarActor();
	FGameplayEffectContextHandle PrimaryContextHandle = ASC->MakeEffectContext();
	PrimaryContextHandle.AddSourceObject(AvatarActor);
	FGameplayEffectSpecHandle PrimarySpecHandle = ASC->MakeOutgoingSpec(Effect, Level, PrimaryContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimarySpecHandle.Data.Get());
}
