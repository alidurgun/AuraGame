// Project has been managed by Ali Durgun

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "AuraOverlayWidgetController.generated.h"

class UAuraUserWidget;
struct FOnAttributeChangeData;

/*
 * Inherited from FTableRowBase => In order to create DataTable from this struct.(Display name = UIWidgetRow)
 * This struct will be used to show some specific message according to tag retrieved.
 * MessageTag => Real tag that retrieved from gameplay effect applied.
 * Message => Will be used to display text to the user in the form of widget.
 * MessageWidget => Widget that the message will be displayed.
 * Image => Image that will be used for relevant tag.
 */
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

/*
 * FOnHealthChangedSignature => Delegate Name. F at beginning and Signature and ending is a common
 * signatures for creating delegate functions. Their corresponding callback functions will have name
 * without F and Signature.
 * float => Parameter type.
 * NewHealth => Parameter Name.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
/* Hence our MaxHealth, Health, Mana and MaxMana using same signature with one param float. We can
 * Combine them into one single delegate instead of creating 4 different delegate.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageWidgetRowSignature, FUIWidgetRow, MessageWidget);

/**
 * This widget controller will be used by overlay widget.
 * BlueprintType => It allows to use this class as a type in the BP side. (Such as Cast)
 * Blueprintable => It allows to create a BP class based on this class.
 * For the health and mana WBPs we're going to use this controller to set their percentages.
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAuraOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMessageWidgetRowSignature OnMessageWidgetRow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	/* We want to use this function to return any type of Row data. */
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UAuraOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
