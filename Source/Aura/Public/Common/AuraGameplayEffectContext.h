#pragma once

#include "GameplayEffectTypes.h"
#include "AuraGameplayEffectContext.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const override;

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

	virtual FAuraGameplayEffectContext* Duplicate() const;

	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsBlockedHit() const { return bIsBlockedHit; }

	void SetCriticalHit(const bool bIsCriticalHit_) { bIsCriticalHit = bIsCriticalHit_; }
	void SetBlockedHit(const bool bIsBlockedHit_) { bIsBlockedHit = bIsBlockedHit_; }
protected:
	// Our extra variables that we want to use in the EffectContext.
	UPROPERTY()
	bool bIsBlockedHit{false};

	UPROPERTY()
	bool bIsCriticalHit{false};
};

/*
 * Inside of this TStructOpsTypeTraits struct we can define what can be done with this particular struct
 * FAuraGameplayEffectContext and the quantities that set to true are important things like serialization
 * and for the reflection system.
 * WithNetSerializer => struct has a NetSerialize function for serializing its state to an FArchive used for network replication.
 * WithCopy => struct can be copied via its copy assignment operator.
 */
template<>
struct TStructOpsTypeTraits< FAuraGameplayEffectContext > : public TStructOpsTypeTraitsBase2< FAuraGameplayEffectContext >
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true		// Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};