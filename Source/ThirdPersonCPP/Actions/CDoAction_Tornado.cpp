#include "CDoAction_Tornado.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "CAttachment.h"


void ACDoAction_Tornado::BeginPlay()
{
	Super::BeginPlay();

	//Attahcment->Box
	for (AActor* child : OwnerCharacter->Children) //Children 함수 나를 오너로 삼고있는 모든 액터를 배열로 가져온다.
	{
		if (child->IsA<ACAttachment>() && child->GetActorLabel().Contains("Tornado")) //Contains 이 문자열이 포함되어 있으면 True 이다.
		{
			Box = CHelpers::GetComponent<UBoxComponent>(child);
			break;
		}
	}
}


void ACDoAction_Tornado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector location = OwnerCharacter->GetActorLocation();

	CurrentYaw += AroundSpeed * DeltaTime;
	CurrentYaw = FMath::Fmod(CurrentYaw, 360.f); //Fmod : flaot 타입은 mod연산자를 쓸 수 없으나 저 함수를 사용시 mod연산자 사용 가능

	FVector awayFrom = FVector(Radius, 0, 0);
	FVector rotVector = awayFrom.RotateAngleAxis(CurrentYaw, FVector::UpVector); 

	location += rotVector;

	Box->SetWorldLocation(location);
}

void ACDoAction_Tornado::DoAction()
{
	Super::DoAction();

	CheckFalse(StateComp->IsIdleMode());
	CheckTrue(bActivating);

	bActivating = true;
	StateComp->SetActionMode();


	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ACDoAction_Tornado::Begin_Action()
{
	Super::Begin_Action();

	CurrentYaw = OwnerCharacter->GetActorForwardVector().Rotation().Yaw;

	//Spawn Particle
	Particle = UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, Box, "");
	Particle->SetRelativeLocation(Datas[0].EffcetTransform.GetLocation());
	Particle->SetRelativeScale3D(Datas[0].EffcetTransform.GetScale3D());


	//On Collision
	//Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 1번 방법

	
	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	if (!!attachment)
		attachment->OnCollision();

	//DamageTime Timer
	UKismetSystemLibrary::K2_SetTimer(this, "TickDamage", DamageTime, true );


}

void ACDoAction_Tornado::End_Action()
{
	Super::End_Action();

	StateComp->SetIdleMode();
	StatusComp->SetMove();

	FTimerDynamicDelegate onFinish;
	onFinish.BindUFunction(this, "Finish");

	UKismetSystemLibrary::K2_SetTimerDelegate(onFinish, ActiveTime, false);


}

void ACDoAction_Tornado::TickDamage()
{

	FDamageEvent damageEvent;

	// for문 반복 방법 
	// 1 . i를 이용한 방법 
	// 2 . RGB 방법 이 방법은 반복 중 사라지는 애들이 있으면 멈추고 다시 돌아가거나 Null값이 들어갈 수 있어서 이런경우 사용하면 안된다.

	for (int32 i = 0; i < HittedCharacters.Num(); i++)
	{
	
		UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(HittedCharacters[i]);

		bool bIgnore = false;
		bIgnore |= (stateComp == nullptr);						// Alredy Dead 이미 죽은 애들 
		bIgnore |= (HittedCharacters[i]->IsPendingKill());		// IsPendingKill GBC에서 삭제를 대기하는 중인지 알려주는 함수 
		bIgnore |= (HittedCharacters[i] == nullptr);			// Released from Memory 메모리에서 삭제된 애들 

		if (bIgnore) continue;
		
		//TakeDamage



		HittedCharacters[i]->TakeDamage(Datas[0].Power, damageEvent, OwnerCharacter->GetController(), this);
	}
}


void ACDoAction_Tornado::OnAttachmentBeginOverlap(UPrimitiveComponent* InOverlappedComponent, ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InOverlappedComponent, InAttacker, InCauser, InOtherCharacter);

	HittedCharacters.AddUnique(InOtherCharacter);
}

void ACDoAction_Tornado::OnAttachmentEndOverlap(UPrimitiveComponent* InOverlappedComponent, ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InOverlappedComponent, InAttacker, InCauser, InOtherCharacter);

	HittedCharacters.Remove(InOtherCharacter);
}

void ACDoAction_Tornado::Abort()
{
	Finish();
}

void ACDoAction_Tornado::Finish()
{
	if (!!Particle)
		Particle->DestroyComponent();


	bActivating = false;

	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	if (!!attachment)
		attachment->OffCollision();

	UKismetSystemLibrary::K2_ClearTimer(this, "TickDamage");

}