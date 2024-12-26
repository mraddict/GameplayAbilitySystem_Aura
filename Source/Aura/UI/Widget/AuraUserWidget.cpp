// Golfzon mraddict


#include "AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;

	SetWidgetControllerFromBP();
}
