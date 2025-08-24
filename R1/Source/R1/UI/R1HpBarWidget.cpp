


#include "UI/R1HPBarWidget.h"
#include "Components/Progressbar.h"

UR1HpBarWidget::UR1HpBarWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UR1HpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UR1HpBarWidget::SetHpRatio(float Ratio)
{
	if (HpBar)
	{
		HpBar->SetPercent(Ratio);
	}
}
