#include "CSelectActionItemWidget.h"
#include "Global.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Styling/SlateBrush.h"
#include "CSelectActionWidget.h"
#include "Characters/CPlayer.h"

void UCSelectActionItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CheckNull(ImageButton);
	ImageButton->OnPressed.AddDynamic(this, &UCSelectActionItemWidget::OnPressed);
	ImageButton->OnHovered.AddDynamic(this, &UCSelectActionItemWidget::OnHover);
	ImageButton->OnUnhovered.AddDynamic(this, &UCSelectActionItemWidget::OnUnhover);

}



void UCSelectActionItemWidget::SetTextureToImageButton(class UTexture2D* InTexture)
{

	//buffer -> 4096*16 ->65536����Ʈ�� �Ѱܼ� ���� �� ����.
	//buffer�� �ѱ� �� ���� ����Ʈ�� ũ��� Texture�� �ѱ��.
	//Resource�� cpu ���� gpu�� ������ �Լ� buffer�� �����

	CheckNull(ImageButton);
	ImageButton->WidgetStyle.Normal.SetResourceObject(InTexture);
	ImageButton->WidgetStyle.Hovered.SetResourceObject(InTexture);
	ImageButton->WidgetStyle.Pressed.SetResourceObject(InTexture);
}


void UCSelectActionItemWidget::OnPressed()
{
	GetParentWidget()->Pressed(GetName());
}

void UCSelectActionItemWidget::OnHover()
{
	// ���ε尡 �ƴ� WidgetFormName�� ����ϸ� �� �����ȿ� �� �̸��� ã�Ƽ� �������ش�.
	UBorder* border = Cast<UBorder>(GetWidgetFromName("ItemBorder")); 
	CheckNull(border);

	border->SetBrushColor(FLinearColor::Red);

}

void UCSelectActionItemWidget::OnUnhover()
{
	UBorder* border = Cast<UBorder>(GetWidgetFromName("ItemBorder"));
	CheckNull(border);

	border->SetBrushColor(FLinearColor::White);

}

UCSelectActionWidget* UCSelectActionItemWidget::GetParentWidget()
{
	ACPlayer* player = Cast<ACPlayer>(GetOwningPlayer()->GetPawn());
	CheckNullResult(player,nullptr);

	return player->GetSelectActionWidget();
	
}
