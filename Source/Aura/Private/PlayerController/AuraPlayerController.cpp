// Project has been managed by Ali Durgun


#include "PlayerController/AuraPlayerController.h"

#include <InputMappingContext.h>
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <InputActionValue.h>

#include "Interface/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(InputContext);

	// this is singleton object
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	// we will use this to add mapping contexts.

	check(Subsystem);
	Subsystem->AddMappingContext(InputContext, 0);
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Type::Default;

	// we will use this to interact with UI and widgets.
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// CastChecked will automatically check the if cast has succeed or not.
	UEnhancedInputComponent* Enhanced = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	// ETriggerEvent::Triggered => while it is pressed.
	Enhanced->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	// FRotationMatrix will return as unit vector for the specified axis.
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if ( APawn* ControlledPawn = GetPawn() )
	{
		// Then here we will add those directions into the AddMovementInput with corresponding axis,
		// with this usage we can able to control our character.
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = CursorHit.GetActor();

	if (CurrentActor == nullptr)
	{
		if (LastActor == nullptr)
		{
			// do nothing.
		}
		else
		{
			// unhighlight prev actor.
			LastActor->Unhighlight();
		}
	}
	else
	{
		if (LastActor == nullptr)
		{
			// highlight current actor
			CurrentActor->Highlight();
		}
		else
		{
			if (LastActor == CurrentActor)
			{
				// do nothing both are same actor already highlighted.
			}
			else
			{
				// unhighlight the last actor then highlight the current actor.
				LastActor->Unhighlight();
				CurrentActor->Highlight();
			}
		}
	}
}
