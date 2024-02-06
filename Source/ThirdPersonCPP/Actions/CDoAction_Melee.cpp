#include "CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();

	//play montage

	//NullCheck
	CheckFalse(Datas.Num() > 0);

	CheckFalse(StateComp->IsIdleMode());
	StateComp->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}


void ACDoAction_Melee::Begin_Action()
{
	Super::Begin_Action();

	//play next combo montage
}

void ACDoAction_Melee::End_Action()
{
	Super::End_Action();
	StateComp->SetIdleMode();
	StatusComp->SetMove();

	//set State Idling
	//set move
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InCauser, InOtherCharacter);

	FDamageEvent damageEvent;

	InOtherCharacter->TakeDamage(Datas[ComboCount].Power, damageEvent, InAttacker->GetController(), InCauser);
}

void ACDoAction_Melee::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InCauser, InOtherCharacter);
}

