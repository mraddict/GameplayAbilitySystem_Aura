// Golfzon mraddict


#include "AuraAbilitySystemLibrary.h"
#include "AuraAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/HUD/AuraHUD.h"
#include "../UI/WidgetController/AuraWidgetController.h"
#include "../Player/AuraPlayerState.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	check(PC);

	if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
	{
		AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		UAttributeSet* AS = PS->GetAttributeSet();

		const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

		return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
	}
	

	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	check(PC);

	if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
	{
		AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		UAttributeSet* AS = PS->GetAttributeSet();

		const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

		return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
	}

	return nullptr;
}
