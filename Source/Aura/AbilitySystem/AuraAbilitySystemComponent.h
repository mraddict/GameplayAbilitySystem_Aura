// Golfzon mraddict

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectAssetTagsDelegate , const FGameplayTagContainer& FGameplayTagContainer /*AssetTags*/)
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	void SetAbilityActorInfo();
	
protected:

	void AppliedEffect(UAbilitySystemComponent* AbilitySystemComponent , const FGameplayEffectSpec& EffectSpec , FActiveGameplayEffectHandle ActiveEffectHandle);

public:

	FOnEffectAssetTagsDelegate OnEffectAssetTagsDelegate;
};
