// Golfzon mraddict


#include "AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::SetAbilityActorInfo()
{
	/** Called on server whenever a GE is applied to self. This includes instant and duration based GEs. */
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this , &UAuraAbilitySystemComponent::AppliedEffect);
}

void UAuraAbilitySystemComponent::AppliedEffect(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	OnEffectAssetTagsDelegate.Broadcast(TagContainer);	
}
