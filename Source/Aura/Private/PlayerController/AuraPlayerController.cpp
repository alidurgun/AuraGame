// Project has been managed by Ali Durgun


#include "PlayerController/AuraPlayerController.h"

#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <InputActionValue.h>

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Components/SplineComponent.h"
#include "GameplayAbilitySystem/AuraAbilitySystemComponent.h"
#include "GameplayAbilitySystem/GameplayTags/AuraGameplayTags.h"
#include "Input/AuraInputComponent.h"
#include "Interface/EnemyInterface.h"
#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	/* This will allow player to use inputs on multiplayer game. */
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	if (bAutoRunning)
	{
		AutoRun();
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag Tag)
{
	if (GetAuraASC() != nullptr)
	{
		bAutoRunning = false;
		AuraASC->AbilityInputTagPressed(Tag);
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag Tag)
{
	if ((CurrentActor == nullptr && !bShiftPressed) && Tag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_RMB))
	{
		// move
		FollowTime += GetWorld()->GetDeltaSeconds(); // update the followtime.
		FHitResult HitResult;
		if (GetHitResultUnderCursor(ECC_Visibility,false, HitResult))
		{
			CachedDestination = HitResult.ImpactPoint;
		}
		if (APawn* ControlledPawn = GetPawn())
		{
			// calculate the direction
			const FVector WorldDirection = (CachedDestination-ControlledPawn->GetActorLocation()).
												GetSafeNormal();

			// Go toward to that direction
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
	else if (GetAuraASC() != nullptr)
	{
		AuraASC->AbilityInputTagHeld(Tag);
	}
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag Tag)
{
	if ((CurrentActor == nullptr && !bShiftPressed) && Tag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_RMB))
	{
		// move
		APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			/*
			 * This function using for finds path instantly, in a FindPath Synchronously.
			 */
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(
				this,
				ControlledPawn->GetActorLocation(),
				CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (auto point : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(point, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), point, 8.f, 8, FColor::Yellow, false, 5.0f);
				}
				/*
				 * Get the latest closest location for the clicked position. To prevent a potential bug
				 * that might be occured when the player click to some place that navigation mesh is not
				 * available. (For ex: obstacle etc.)
				 */
				if (!NavPath->PathPoints.IsEmpty())
				{
					CachedDestination = NavPath->PathPoints.Last();
				}
				bAutoRunning = true;
			}
		}
		FollowTime = 0.0f; // reset followtime.
	}
	else if (GetAuraASC() != nullptr)
	{
		AuraASC->AbilityInputTagReleased(Tag);
	}
}

void AAuraPlayerController::ShowDamageComponent_Implementation(float Damage, ACharacter* TargetCharacter, bool IsBlocked, bool IsCrit)
{
	// IsValid is checking the input parameter is null or not. In addition to that it will also check the
	// if the parameter is pending to kill. Therefore, we have used IsValid for the TargetCharacter.
	if (IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		// It needs to construct that widget component. To do that we need widget component class.
		// Outer should be TargetCharacter hence we will use TargetCharacter to spawn component.
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);

		// If the component created dynamically, then it has to registered by calling register component.
		// CreateDefaultSubObject function is automatically registering. But if we do not use that we have to
		// do it manually.
		DamageText->RegisterComponent();

		// Attach it to component in order to spawn it on the correct location.
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

		// Detach it because it will play an animation, and we do not need to keep that on the component.
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		DamageText->SetDamageText(Damage, IsBlocked, IsCrit);
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(InputContext);

	// this is singleton object
	// we will use this to add mapping contexts.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputContext, 0);
	}
	
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

	// CastChecked will automatically check the if cast has succeeded or not.
	// In order to handle input data we need to cast InputComponent to UEnhancedInputComponent.
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	
	// ETriggerEvent::Triggered => while it is pressed.
	// MoveAction will receive data.(It will fill with given data.)
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityActions(InputConfig, this,
		&AAuraPlayerController::AbilityInputTagPressed,
		&AAuraPlayerController::AbilityInputTagHeld,
		&AAuraPlayerController::AbilityInputTagReleased);

	AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::ShiftPressed);
	AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::ShiftReleased);
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
		// with this usage we can be able to control our character.
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

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraASC()
{
	if (AuraASC == nullptr)
	{
		AuraASC = Cast<UAuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraASC;
}

void AAuraPlayerController::AutoRun()
{
	if (APawn* ControlledPawn = GetPawn())
	{
		/*
		 * Get the closest location to the actor. (Our first spline point may not be always the character's location)
		 * Hence the function will be called every frame this closest location will update frequently.
		 */
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(
			ControlledPawn->GetActorLocation(),
			ESplineCoordinateSpace::World);

		// Calculate direction to the closest point.
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(
			LocationOnSpline,
			ESplineCoordinateSpace::World);

		ControlledPawn->AddMovementInput(Direction);
		const float DistanceToDestination = (CachedDestination - LocationOnSpline).Length();
		if (DistanceToDestination<=AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}
