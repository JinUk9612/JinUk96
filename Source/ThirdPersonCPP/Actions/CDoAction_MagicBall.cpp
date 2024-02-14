#include "CDoAction_MagicBall.h"
#include "CDoAction_MagicBall.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "CAim.h"
#include "CMagicBall.h"

void ACDoAction_MagicBall::BeginPlay()
{
	Super::BeginPlay();
	Aim = NewObject<UCAim>();  // Aim = New Object 와 같다.

	//Dangling Point = 지웠는데 다시 써야 하는 곳이 있을경우 터지는 경우 
	//Memory Leak = 안지웠으나 쓰지도 않아서 메모리를 차지하는 메모리 누수 현황
	// -> unique_ptr , shared_ptr, weak_ptr  스마트 포인터 쓰는곳마다 래퍼런스를 1씩 증가시켜 61초마다 검사를 하여 사용하는곳이 없을경우 제거한다.
	// 가비지 콜렉터가 61초마다 검사를하여 삭제가 된다면 그 후 사용시 터질  수 있어 Aim 이라는 가비지콜렉터에 등록해야한다 . 

	Aim->BeginPlay(OwnerCharacter);
}

void ACDoAction_MagicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Aim->Tick(DeltaTime);
}

void ACDoAction_MagicBall::DoAction()
{
	Super::DoAction();

	CheckFalse(Datas.Num() > 0);
	CheckFalse(Aim->IsCanAim());
	CheckFalse(Aim->IsZooming());
	CheckFalse(StateComp->IsIdleMode());


	StateComp->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ACDoAction_MagicBall::Begin_Action()
{
	Super::Begin_Action();

	CheckNull(Datas[0].ProjectileClass);

	//Spawn Projectile Actor
	FTransform transform ;

	//Get Hand Socket Location 
	FVector handLocation = OwnerCharacter->GetMesh()->GetSocketLocation("middle_01_r");   //GetSocketLocation  월드상의 소켓 위치를 가져오는 함수 
	transform.AddToTranslation(handLocation);

	//Get Controller Rotation
	transform.SetRotation(FQuat(OwnerCharacter->GetControlRotation()));

	//Spawn MagicBall
	ACMagicBall* magicBall = GetWorld()->SpawnActorDeferred<ACMagicBall>(Datas[0].ProjectileClass, transform, OwnerCharacter, OwnerCharacter,ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	magicBall->SetData(Datas[0]);

	//Damage Event Bining
	magicBall->OnMagicBallOverlap.AddDynamic(this, &ACDoAction_MagicBall::OnMagicBallOverlap);

	UGameplayStatics::FinishSpawningActor(magicBall, transform);
}

void ACDoAction_MagicBall::End_Action()
{
	Super::End_Action();

	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ACDoAction_MagicBall::BeginSubAction()
{
	CheckNull(Aim);

	Aim->On();

}

void ACDoAction_MagicBall::EndSubAction()
{
	CheckNull(Aim);

	Aim->Off();

}


void ACDoAction_MagicBall::OnMagicBallOverlap(FHitResult InHitResult)
{
	FDamageEvent damageEvent;

	InHitResult.GetActor()->TakeDamage(Datas[0].Power, damageEvent,OwnerCharacter->GetController(),this);
}