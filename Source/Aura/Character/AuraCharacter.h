// Golfzon mraddict

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:

	AAuraCharacter();
	
	/** Called when this Pawn is possessed. Only called on the server (or in standalone). */
	virtual void PossessedBy(AController* NewController) override;
	/** PlayerState Replication Notification Callback */
	virtual void OnRep_PlayerState() override;

	// ICombatInterface

	virtual int32 GetPlayerLevel() override;

protected:

	virtual void InitAbilityActorInfo() override;
};
