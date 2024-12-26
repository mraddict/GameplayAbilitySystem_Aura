// Golfzon mraddict


#include "AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	TraceCursor();
}

void AAuraPlayerController::TraceCursor()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit)
	{
		return;
	}

	LastEnemyActor = ThisEnemyActor;
	//ThisEnemyActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	ThisEnemyActor = CursorHit.GetActor();

	/**
	 * Line trace from cursor. There are several scenarios.
	 *	A. LastEnemyActor is null && ThisEnemyActor is null
	 *		- Do nothing
	 *	B. LastEnemyActor is null && ThisEnemyActor is valid
	 *		- Highlight ThisEnemyActor
	 *	C. LastEnemyActor is valid && ThisEnemyActor is null
	 *		- UnHighlight LastEnemyActor
	 *	D. Both actors are valid, but LastEnemyActor != ThisEnemyActor
	 *		- UnHighlight LastEnemyActor, and Highlight ThisEnemyActor
	 *	E. Both actors are valid, but are the same actor
	 *		- Do nothing
	 */

	if (LastEnemyActor == nullptr)
	{
		if (ThisEnemyActor != nullptr)
		{
			// Case B
			ThisEnemyActor->HighlightActor();
		}
		else
		{
			// Case A
		}
	}
	else
	{
		if (ThisEnemyActor != nullptr)
		{
			if (LastEnemyActor != ThisEnemyActor)
			{
				// Case D
				LastEnemyActor->UnHighlightActor();
				ThisEnemyActor->HighlightActor();
			}
			else
			{
				// Case E
			}
		}
		else
		{
			// Case C
			LastEnemyActor->UnHighlightActor();
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraInputContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraInputContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Project setting > Input > Default Classes > Default Player Input Class
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(AuraMoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
