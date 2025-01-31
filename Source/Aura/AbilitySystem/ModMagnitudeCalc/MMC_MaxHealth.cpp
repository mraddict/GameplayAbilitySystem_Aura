// Golfzon mraddict


#include "MMC_MaxHealth.h"
#include "../AuraAttributeSet.h"
#include "../../Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigerDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigerDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigerDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigerDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Viger = 0.0f;
	GetCapturedAttributeMagnitude(VigerDef, Spec , EvaluateParameters , Viger);
	Viger = FMath::Max<float>(Viger, 0.0f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	// base + coef * Viger + post * player level

	return 80.0f + 2.5f * Viger + 10.0f * PlayerLevel;
}
