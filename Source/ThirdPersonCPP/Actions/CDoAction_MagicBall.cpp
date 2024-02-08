#include "CDoAction_MagicBall.h"
#include "CDoAction_MagicBall.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_MagicBall::BeginPlay()
{
	Super::BeginPlay();
}

void ACDoAction_MagicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACDoAction_MagicBall::DoAction()
{
	Super::DoAction();

	CheckFalse(Datas.Num() > 0);


	CheckFalse(StateComp->IsIdleMode());
	StateComp->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ACDoAction_MagicBall::Begin_Action()
{
	Super::Begin_Action();

	//Spawn Projectile Actor
}

void ACDoAction_MagicBall::End_Action()
{
	Super::End_Action();

	StateComp->SetIdleMode();
	StatusComp->SetMove();
}
