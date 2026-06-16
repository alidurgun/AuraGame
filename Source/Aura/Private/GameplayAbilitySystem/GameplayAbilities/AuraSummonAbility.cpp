// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/GameplayAbilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	// get the forward vector for the actor.
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();

	// Actor's location.
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();

	// Divide spread to identical based on how many item are going to be spawn.
	const float DeltaSpread = SpawnSpread / NumOfSpawned;

	// To make spread in front of the actor. (Z Axis)
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.0f, FVector::UpVector);

	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumOfSpawned; ++i) // Generalized way for number of minions. This could depend on the level of ability etc.
	{
		// choose direction for spreading.
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);

		// This is randomized spawn location between min and max distance
		const FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		SpawnLocations.Add(ChosenSpawnLocation);

		// just debug spheres and arrows to see visualization of our algorithm.
		DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 18.f, 12, FColor::Cyan, false, 3.f );
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + Direction * MaxSpawnDistance, 4.f, FLinearColor::Green, 3.f );
		DrawDebugSphere(GetWorld(), Location + Direction * MinSpawnDistance, 5.f, 12, FColor::Red, false, 3.f );
		DrawDebugSphere(GetWorld(), Location + Direction * MaxSpawnDistance, 5.f, 12, FColor::Red, false, 3.f );
	}

	return SpawnLocations;
}
