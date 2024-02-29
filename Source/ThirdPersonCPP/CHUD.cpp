#include "CHUD.h"
#include "Global.h"
#include "Engine/Canvas.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Engine/Texture2D.h"


ACHUD::ACHUD()
{
	CHelpers::GetAsset<UTexture2D>(&CrossHairTexture, "Texture2D'/Game/Materials/T_Crosshair.T_Crosshair'");
}

void ACHUD::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	CheckNull(playerCharacter);

	StateComp = CHelpers::GetComponent<UCStateComponent>(playerCharacter);
	StateTypeAsUEnum = FindObject<UEnum>(ANY_PACKAGE, L"EStateType",true);
}


void ACHUD::DrawHUD()
{
	Super::DrawHUD();
	
	//Visible Player StateType
	CheckNull(StateComp);
	CheckNull(StateTypeAsUEnum);


	FString typeStr = StateTypeAsUEnum->GetNameStringByValue((int64)StateComp->GetType());
	DrawText(typeStr, FLinearColor::Red, 10, Canvas->ClipY - 70, nullptr, 3.f);

	typeStr = StateTypeAsUEnum->GetNameStringByValue((int64)StateComp->GetPrevType());
	DrawText(typeStr, FLinearColor::Green, 10, Canvas->ClipY - 150, nullptr, 3.f);



	FVector2D center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5);

	FVector2D imageHalfSize(CrossHairTexture->GetSizeX() * 0.5f, CrossHairTexture->GetSizeY() * 0.5f);

	center -= imageHalfSize;

	//Visible Aim(R-Button)
	CheckNull(CrossHairTexture);
	CheckFalse(bVisibleCrossHair);

	FCanvasTileItem imageItem(center, CrossHairTexture->Resource, FLinearColor::White);
	imageItem.BlendMode = ESimpleElementBlendMode::SE_BLEND_Translucent;
	Canvas->DrawItem(imageItem);

}