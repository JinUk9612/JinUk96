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
	Aim = NewObject<UCAim>();  // Aim = New Object �� ����.

	//Dangling Point = �����µ� �ٽ� ��� �ϴ� ���� ������� ������ ��� 
	//Memory Leak = ���������� ������ �ʾƼ� �޸𸮸� �����ϴ� �޸� ���� ��Ȳ
	// -> unique_ptr , shared_ptr, weak_ptr  ����Ʈ ������ ���°����� ���۷����� 1�� �������� 61�ʸ��� �˻縦 �Ͽ� ����ϴ°��� ������� �����Ѵ�.
	// ������ �ݷ��Ͱ� 61�ʸ��� �˻縦�Ͽ� ������ �ȴٸ� �� �� ���� ����  �� �־� Aim �̶�� �������ݷ��Ϳ� ����ؾ��Ѵ� . 

	Aim->BeginPlay(OwnerCharacter);

	ActionComp = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	ActionComp->OnActionTypeChanged.AddDynamic(this, &ACDoAction_MagicBall::AbortByActionTypeChanged);
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
	FVector handLocation = OwnerCharacter->GetMesh()->GetSocketLocation("middle_01_r");   //GetSocketLocation  ������� ���� ��ġ�� �������� �Լ� 


	//Get Camera Location&Rotation
	FVector location;
	FRotator rotation;
	OwnerCharacter->GetController()->GetPlayerViewPoint(location, rotation);

	location = location + rotation.Vector() * ((handLocation - location) | rotation.Vector());
	transform.AddToTranslation(location);
	transform.SetRotation(FQuat(rotation));
	
	//���� ��ġ = ���� ��ġ + ���� * ���� 


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

void ACDoAction_MagicBall::AbortByActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{

	//DoAction_MagicBall -> Aim -> Off
	CheckFalse(Aim->IsCanAim());
	CheckFalse(Aim->IsZooming());

	Aim->Off();

}