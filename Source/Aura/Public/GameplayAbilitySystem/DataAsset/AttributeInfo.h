// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

/**
 * From this class we will broadcast values to widget side. To achieve this purpose we will use
 * struct to hold related informations.(struct FAuraAttributeInfo)
 *
 * Data Asset:
 * It is an asset that stores data related to a particular system in an instance of its class.
 */


/* FAuraAttributeInfo will hold related data for the incoming attribute tag.
 * FText is using to show something on the widgets as a text. We want to show some
 * description for relevant tag. Value will only BPRO hence we don't want to set this value
 * directly. Instead, we will pull this information from the ASC.
 */
USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.0f;
};

UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	// This is list of Actor information.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;

	/* This function will accept Gameplay Tag and return to correct information for the given
	 * tag in the AuraAttributeInfo struct.
	 * @param[0] in Tag => input Tag to search this tag in the AttributeInformation array.
	 * @param[1] in bLogNotFound => To enable or disable logs if the given tag is not found in the array.
	 */
	FAuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag& Tag, bool bLogNotFound = false) const;
};
