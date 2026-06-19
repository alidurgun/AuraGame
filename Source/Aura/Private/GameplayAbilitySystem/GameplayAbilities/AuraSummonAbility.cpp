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
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, ChosenSpawnLocation + FVector(0.0f,0.0f,400.0f),
			ChosenSpawnLocation - FVector(0.0f,0.0f,400.0f), ECC_Visibility);

		if (HitResult.bBlockingHit)
		{
			ChosenSpawnLocation = HitResult.ImpactPoint;
		}
		SpawnLocations.Add(ChosenSpawnLocation);
	}

	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomSpawnClass()
{
	const int32 selection = FMath::RandRange(0, SpawnedClasses.Num() - 1);
	return SpawnedClasses[selection];
}
