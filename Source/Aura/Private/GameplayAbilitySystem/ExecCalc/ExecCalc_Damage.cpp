// Project has been managed by Ali Durgun


#include "GameplayAbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "GameplayAbilitySystem/AuraAbilitySystemBPLibrary.h"
#include "GameplayAbilitySystem/AuraAttributeSet.h"
#include "GameplayAbilitySystem/DataAsset/CharacterClassInfo.h"
#include "GameplayAbilitySystem/GameplayTags/AuraGameplayTags.h"
#include "Interface/CombatInterface.h"
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
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);

	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;

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
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArcaneResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PhysicalResistance, Target, false);

		const FAuraGameplayTags Tags = FAuraGameplayTags::Get();
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_BlockChance, BlockChanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor, ArmorDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance, CriticalHitResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration, ArmorPenetrationDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance, CriticalHitChanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitDamage, CriticalHitDamageDef);

		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane, ArcaneResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Fire, FireResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning, LightningResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical, PhysicalResistanceDef);
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
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);

	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
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


	float ArmorValue{0.0f};
	float ArmorPenetrationValue{0.0f};

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParams, ArmorValue);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluateParams, ArmorPenetrationValue);

	// To get the player levels for both source and target. To get the correct value from CT.
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceActor);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetActor);

	// Get the character class info. To retrieve CT from it.
	UCharacterClassInfo* CharInfo = UAuraAbilitySystemBPLibrary::GetCharacterClassInfo(SourceActor);

	// Get the relevant tables from the CT by using curve name.
	const FRealCurve* ArmorPenetrationCurve = CharInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const FRealCurve* EffectiveArmorCurve = CharInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());

	// Get the coefficients for current levels.
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	float Damage{0.0f};
	// Damage type related calculations.
	for (const auto& Pair: FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		checkf(AuraDamageStatics().TagsToCaptureDefs.Contains(Pair.Value),
			TEXT("TagsToCaptureDefs does not contains [%s]"), *Pair.Value.ToString());
		FGameplayEffectAttributeCaptureDefinition ResistanceDef = AuraDamageStatics().TagsToCaptureDefs[Pair.Value];

		/*
		* GetSetByCallerMagnitude function can have 3 parameters 2 of them is optional
		* param[0] => name of the tag
		* param[1] => to enable warning if given tag is not found. (true)
		* param[2] => Default value for the tag when the tag is not found. (0)
		*/
		// Calculate damage type bonus.
		float DamageTypeValue = GESpec.GetSetByCallerMagnitude(Pair.Key);
		
		// Calculate damage resistance value.
		float Resistance { 0.0f };
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ResistanceDef, EvaluateParams, Resistance);

		DamageTypeValue *= ( 100.f - Resistance ) / 100.f;
		
		Damage += DamageTypeValue;
	}

	// Calculation relevant with Armor Penetration and Armor
	const float EffectiveArmor = ArmorValue * (100-ArmorPenetrationValue * ArmorPenetrationCoefficient) / 100.0f;

	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.0f;
	
	float BlockChanceValue{0.0f};

	// To get the captured attribute, BlockChanceValue will be filled with captured attribute magnitude.
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluateParams, BlockChanceValue);
	BlockChanceValue = FMath::Max<float>(0.0f,BlockChanceValue); // to make sure it will never be negative value.

	BlockChanceValue = BlockChanceValue<10.0f ? 10.0f : BlockChanceValue;

	const bool bAttackBlocked = FMath::RandRange(1,100) <= BlockChanceValue;
	Damage = bAttackBlocked ? Damage/2.0f : Damage;

	FGameplayEffectContextHandle EffectContextHandle = GESpec.GetContext();
	UAuraAbilitySystemBPLibrary::SetBlockedHit(EffectContextHandle, bAttackBlocked);

	// If attack is not blocked then crit can occur. Calculate crit chance and implement the crit logic.
	if (!bAttackBlocked)
	{
		float CritHitChanceVal{0.0f};
		float CritHitDamageVal{0.0f};
		float CritHitResVal{0.0f};

		// Retrieve crit related props.
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluateParams, CritHitChanceVal);
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluateParams, CritHitDamageVal);
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaluateParams, CritHitResVal);
		
		CritHitChanceVal -=  (CritHitResVal * 0.85f);
		const bool bCriticalHit = FMath::RandRange(1,100) <= CritHitChanceVal;

		UAuraAbilitySystemBPLibrary::SetCriticalHit(EffectContextHandle, bCriticalHit);

		Damage = bCriticalHit ? Damage*2.0f + CritHitDamageVal : Damage;
	}

	// use AttributeSet::GetIncomingDamageAttribute() to get incoming damage meta attribute.
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);

	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
