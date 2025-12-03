// Project has been managed by Ali Durgun


#include "Character/Aura/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerState/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	// to turn character's face to the direction that we are moving.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Turn speed to the new direction.
	GetCharacterMovement()->RotationRate = FRotator(0.0f,400.0f,0.0f);
	// Movement will be constrained to plane.
	GetCharacterMovement()->bConstrainToPlane = true;
	// Updated component will be snapped to the plane when first attached.
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::InitAbilityComponent()
{
	if (AAuraPlayerState* CurrentPlayerState = GetPlayerState<AAuraPlayerState>())
	{
		// owner will be PlayerState and avatar will be this.
		CurrentPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(CurrentPlayerState,this);
		AbilitySystemComponent = CurrentPlayerState->GetAbilitySystemComponent();
		AttributeSet = CurrentPlayerState->GetAttributeSet();
	}
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Actor info for the server side.
	InitAbilityComponent();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Actor info for the client side.
	InitAbilityComponent();
}
