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

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:

	/** Overridable native event for when play begins for this actor. */
	virtual void BeginPlay() override;
};
