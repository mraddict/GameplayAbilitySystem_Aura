// Golfzon mraddict

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "../Interaction/EnemyInterface.h"
#include "AuraEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemyCharacter : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:

	AAuraEnemyCharacter();

	// ICombatInterface

	virtual int32 GetPlayerLevel() override;
	
	// IEnemyInterface

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:

	/** Overridable native event for when play begins for this actor. */
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

protected:

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Character Class Defaults")
	int32 Level = 1;
};
