// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class USplineComponent;
class UAuraAbilitySystemComponent;
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

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraASC{nullptr};

	UAuraAbilitySystemComponent* GetAuraASC();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> CurrentActor;

	/*
	 * Click To Move Functionality
	 */
	FVector CachedDestination{FVector::ZeroVector}; // To cache the location of where the mouse clicked.

	float FollowTime{0.0f}; // To track the passing time while we are moving with mouse held down.

	float ShortPressThreshold{0.5f}; // To determine what is the single click in seconds.

	bool bAutoRunning{false}; // Track the kind of movement we are doing now.

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius{50.0f};

	// To generate a line from our pathfind points.(instead of sharp turns it will be smooth line)
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();
};
