// Golfzon mraddict

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplyPolicy
{
	ApplyOnOverlap ,
	ApplyOnEndOverLap ,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovePolicy
{
	RemoveOnEndOverLap ,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor , TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

protected:

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Applied Effect")
	bool bDestroyOnEffectRemoval = false;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Applied Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Applied Effect")
	EEffectApplyPolicy InstantEffectApplyPolicy = EEffectApplyPolicy::DoNotApply;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Applied Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Applied Effect")
	EEffectApplyPolicy DurationEffectApplyPolicy = EEffectApplyPolicy::DoNotApply;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Applied Effect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Applied Effect")
	EEffectApplyPolicy InfiniteEffectApplyPolicy = EEffectApplyPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Applied Effect")
	EEffectRemovePolicy InfinitEffectRemovePolicy = EEffectRemovePolicy::RemoveOnEndOverLap;

	TMap<FActiveGameplayEffectHandle , UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Applied Effect")
	float ActorLevel = 1.0f;
};
