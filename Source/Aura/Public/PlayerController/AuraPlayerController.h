// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
struct FGameplayTag;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

	// Ability function that will be responsible from when the related input has been pressed.
	void AbilityInputTagPressed(FGameplayTag Tag);

	// Ability function that will be responsible from when the related input has been held down.
	void AbilityInputTagHeld(FGameplayTag Tag);

	// Ability function that will be responsible from when the related input has been released.
	void AbilityInputTagReleased(FGameplayTag Tag);

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction; // This input action will fill with the input data that we'll send.
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;
	
	/*
	 * This function will be binded to the MoveAction, and it'll be responsible from character movements.
	 * It will act like a callback function for our inputs.
	 */
	void Move(const FInputActionValue& InputActionValue);

	/*
	 * This function will be responsible of Tracing the cursor. We will use this function to
	 * track actors under our cursor.
	 */
	void CursorTrace();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> CurrentActor;
};
