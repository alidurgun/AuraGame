// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;
/*
 * This enum class will represent different types of character classes that will be used in the game.
 */
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Elementalist, // Wizard
	Ranger, // Slingshot, arrow
	Warrior // Melee
};

/*
 * This will be associated with primary values for each class. Warrior will have its own primary attributes
 * ranger will own and elementalist will own different.
 * So the warrior and ranger will not start the game with same properties.
 */
USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryEffects;

	UPROPERTY( EditDefaultsOnly, Category="Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};

/**
 * Our data asset will have primary, secondary, and vital attributes for specified character type.
 * We will store those values in this class.
 */
UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;

	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	FCharacterClassDefaultInfo GetCharacterClassDefaultInfo(ECharacterClass CharacterClass);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Common Abilities")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Common Abilities")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;
};
