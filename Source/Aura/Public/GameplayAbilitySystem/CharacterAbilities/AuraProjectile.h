// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraSystem;

/*
 * This class will be related with projectile spells.
 * This class will be used for casting spells.
 */
UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraProjectile();

	virtual void Destroyed() override;
	void CreateExplosion();

	/*
	 * ExposeOnSpawn = true:
	 * Adds that variable as an input pin on the BP Spawn Actor node.
	 * Give opportunity to set property's value at the moment the object is created.
	 * It means that the property will be editable when the object is spawned.
	 */
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	// This component used to give velocity to the actor.
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> TrailSound;

	// Audio Component is created from UGameplayStatics::SpawnSoundAttached to use looping sounds.
	TObjectPtr<UAudioComponent> TrailSoundComponent;

	// If server destroys the actor without we hit something we should play sound and effect too.
	bool bHit{false};

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan{5.0f}; // max time of Projectile can stay in the game.
};
