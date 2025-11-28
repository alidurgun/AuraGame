// Project has been managed by Ali Durgun


#include "Character/Aura/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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
