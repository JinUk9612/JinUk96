#include "CSelectActionWidget.h"
#include "Global.h"
#include "Components/GridPanel.h"
#include "CSelectActionItemWidget.h"


void UCSelectActionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CheckNull(ItemGrid);


	//Registry item widget to Map list
	TArray<UWidget*> children = ItemGrid->GetAllChildren();
	for (UWidget* child : children)
	{
		UCSelectActionItemWidget* itemWidget = Cast<UCSelectActionItemWidget>(child);
		if (!!itemWidget)
			ItemWidgets.Add(itemWidget->GetName(), itemWidget); // str std::map<keyT, valueT> mm; mm.insert
	}

	//Set Texture to item widget Image buttons
	for (int32 i = 0; i < ItemWidgets.Num(); i++)
	{
		FString key = Prefix;
		key.Append(FString::FromInt(i + 1));

		if(!!ItemWidgets[key] && !!Textures[i])
			ItemWidgets[key]->SetTextureToImageButton(Textures[i]);
	}

}

void UCSelectActionWidget::Pressed(FString InName)
{
	if (ItemWidgets[InName]->OnImageButtonPressed.IsBound())
		ItemWidgets[InName]->OnImageButtonPressed.Broadcast();
}
