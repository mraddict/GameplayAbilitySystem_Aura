// Golfzon mraddict


#include "AuraEffectActor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "../AbilitySystem/AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (TargetActor)
	{
		check(GameplayEffectClass);

		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);

		const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass , ActorLevel , EffectContextHandle);
		const FGameplayEffectSpec* EffectSpec = EffectSpecHandle.Data.Get();
		const UGameplayEffect* Effect = EffectSpec->Def.Get();

		const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpec);

		if ((Effect->DurationPolicy == EGameplayEffectDurationType::Infinite) && (InfinitEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverLap))
		{
			ActiveEffectHandles.Add(ActiveGameplayEffectHandle , TargetASC);
		}
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplyPolicy == EEffectApplyPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor , InstantGameplayEffectClass);
	}

	if (DurationEffectApplyPolicy == EEffectApplyPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplyPolicy == EEffectApplyPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor , InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplyPolicy == EEffectApplyPolicy::ApplyOnEndOverLap)
	{
		ApplyEffectToTarget(TargetActor , InstantGameplayEffectClass);
	}

	if (DurationEffectApplyPolicy == EEffectApplyPolicy::ApplyOnEndOverLap)
	{
		ApplyEffectToTarget(TargetActor , DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplyPolicy == EEffectApplyPolicy::ApplyOnEndOverLap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	if (InfinitEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverLap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

		if (IsValid(TargetASC))
		{
			TArray<FActiveGameplayEffectHandle> HandlesToRemove;

			for (auto HandlePair : ActiveEffectHandles)
			{
				if (HandlePair.Value == TargetASC)
				{
					TargetASC->RemoveActiveGameplayEffect(HandlePair.Key);
					HandlesToRemove.Add(HandlePair.Key);
				}
			}

			for (auto& Handle : HandlesToRemove)
			{
				ActiveEffectHandles.FindAndRemoveChecked(Handle);
			}
		}
	}
}
