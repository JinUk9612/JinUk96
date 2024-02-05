#include "CHUD.h"
#include "Global.h"
#include "Engine/Canvas.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"

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

	CheckNull(StateComp);
	CheckNull(StateTypeAsUEnum);


	FString typeStr = StateTypeAsUEnum->GetNameStringByValue((int64)StateComp->GetType());

	DrawText(typeStr, FLinearColor::Red, 10, Canvas->ClipY - 70, nullptr, 3.f);

}