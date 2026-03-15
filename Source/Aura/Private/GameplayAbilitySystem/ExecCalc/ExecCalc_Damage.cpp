// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "GameplayAbilitySystem/AuraAttributeSet.h"
#include "GameplayAbilitySystem/GameplayTags/AuraGameplayTags.h"
#include "UObject/FastReferenceCollector.h"

// Row struct that will be used for internal usage in cpp side for execution calculation.
// Static variable will be used to access this struct.
struct AuraDamageStatics
{
	/*
	 * This macro accepts parameter as token, so BlockChance do not need to be defined previously hence this macro will
	 * create a FProperty with given parameter name. In this example it will create a FProperty and
	 * FGameplayEffectAttributeCaptureDefinition with given parameter name.
	 * FProperty => BlockChanceProperty
	 * FGameplayEffectAttributeCaptureDefinition => BlockChanceDef
	 */
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);

	AuraDamageStatics()
	{
		/*
		 * This macro defines Property and Def for the given token.
		 * To define Property it will try to find the given token in the given attribute set.
		 * To define def it will construct a new FGameplayEffectAttributeCaptureDefinition with given token, enum and snapshot.
		 * param[0] => class for our AttributeSet
		 * param[1] => BlockChance(Created Capturing Def via DECLARE_ATTRIBUTE_CAPTUREDEF macro)
		 * param[2] => Enum for EGameplayEffectAttributeCaptureSource. It depends on the whichj side effecting the damage
		 * typedef. For example: BlockChance is effecting from Target side not the source side. Therefore Target has been
		 * used in the enum type.(Capture BlockChance of target)
		 * param[3] => bool value for snapshotting.
		 */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	// BlockChanceDef created via macro.
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceActor = SourceASC->GetAvatarActor();
	AActor* TargetActor = TargetASC->GetAvatarActor();

	FGameplayEffectSpec GESpec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = GESpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = GESpec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	float BlockChanceValue{0.0f};

	// To get the captured attribute, BlockChanceValue will be filled with captured attribute magnitude.
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluateParams, BlockChanceValue);
	BlockChanceValue = FMath::Max<float>(0.0f,BlockChanceValue); // to make sure it will never be negative value.

	BlockChanceValue = BlockChanceValue<10.0f ? 10.0f : BlockChanceValue;

	/*
	 * GetSetByCallerMagnitude function can have 3 parameters 2 of them is optional
	 * param[0] => name of the tag
	 * param[1] => to enable warning if given tag is not found. (true)
	 * param[2] => Default value for the tag when the tag is not found. (0)
	 */
	float Damage = GESpec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Ability_FireBolt_Damage);

	bool bAttackBlocked = FMath::RandRange(1,100) <= BlockChanceValue;
	Damage = bAttackBlocked ? Damage/2.0f : Damage;

	// use AttributeSet::GetIncomingDamageAttribute() to get incoming damage meta attribute.
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);

	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
