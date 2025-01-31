// Golfzon mraddict


#include "AttributeMenuWidgetController.h"
#include "../../AbilitySystem/AuraAttributeSet.h"
#include "../../AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AS);
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		FGameplayAttribute Attr = Pair.Value();
		BroadcastAttributeInfo(Pair.Key, Attr);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	for (auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this , Pair](const FOnAttributeChangeData& Data)
			{
				FGameplayAttribute Attr = Pair.Value();
				BroadcastAttributeInfo(Pair.Key, Attr);
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);

	OnAttributeInfoDelegate.Broadcast(Info);
}
