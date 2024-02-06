#include "CHealthWidget.h"
#include "Global.h"
#include "Components/ProgressBar.h"


void UCHealthWidget::UpdateHP_Implementation(float InCurrentHealth, float MaxHealth)
{
	HealthBar->SetPercent(InCurrentHealth / MaxHealth);
}
