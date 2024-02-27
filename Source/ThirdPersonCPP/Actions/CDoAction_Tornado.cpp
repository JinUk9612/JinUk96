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
	for (AActor* child : OwnerCharacter->Children) //Children �Լ� ���� ���ʷ� ����ִ� ��� ���͸� �迭�� �����´�.
	{
		if (child->IsA<ACAttachment>() && child->GetActorLabel().Contains("Tornado")) //Contains �� ���ڿ��� ���ԵǾ� ������ True �̴�.
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
	CurrentYaw = FMath::Fmod(CurrentYaw, 360.f); //Fmod : flaot Ÿ���� mod�����ڸ� �� �� ������ �� �Լ��� ���� mod������ ��� ����

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
	//Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 1�� ���

	
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

	// for�� �ݺ� ��� 
	// 1 . i�� �̿��� ��� 
	// 2 . RGB ��� �� ����� �ݺ� �� ������� �ֵ��� ������ ���߰� �ٽ� ���ư��ų� Null���� �� �� �־ �̷���� ����ϸ� �ȵȴ�.

	for (int32 i = 0; i < HittedCharacters.Num(); i++)
	{
	
		UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(HittedCharacters[i]);

		bool bIgnore = false;
		bIgnore |= (stateComp == nullptr);						// Alredy Dead �̹� ���� �ֵ� 
		bIgnore |= (HittedCharacters[i]->IsPendingKill());		// IsPendingKill GBC���� ������ ����ϴ� ������ �˷��ִ� �Լ� 
		bIgnore |= (HittedCharacters[i] == nullptr);			// Released from Memory �޸𸮿��� ������ �ֵ� 

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