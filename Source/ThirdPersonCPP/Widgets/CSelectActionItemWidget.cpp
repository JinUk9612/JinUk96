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

	//buffer -> 4096*16 ->65536바이트를 넘겨서 보낼 수 없다.
	//buffer로 넘길 수 없는 바이트의 크기는 Texture로 넘긴다.
	//Resource는 cpu 에서 gpu로 보내는 함수 buffer와 비슷함

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
	// 바인드가 아닌 WidgetFormName을 사용하면 이 위젯안에 저 이름을 찾아서 리턴해준다.
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

