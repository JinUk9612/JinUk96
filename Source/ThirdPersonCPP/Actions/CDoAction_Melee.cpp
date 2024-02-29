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


	//Combo Attack
	if (bCanCombo == true)
	{
		bCanCombo = false;
		bSucceed = true;
	}



	CheckFalse(StateComp->IsIdleMode());
	StateComp->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}


void ACDoAction_Melee::Begin_Action()
{
	Super::Begin_Action();

	//play next combo montage
	CheckFalse(bSucceed);
	bSucceed = false;

	ComboCount++;
	ComboCount = FMath::Clamp(ComboCount, 0, Datas.Num() - 1);

	OwnerCharacter->StopAnimMontage();
	
	OwnerCharacter->PlayAnimMontage(Datas[ComboCount].AnimMontage, Datas[ComboCount].PlayRate, Datas[ComboCount].StartSection);
	Datas[ComboCount].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ACDoAction_Melee::End_Action()
{
	Super::End_Action();

	OwnerCharacter->StopAnimMontage();
	ComboCount = 0;

	StateComp->SetIdleMode();
	StatusComp->SetMove();

	//set State Idling
	//set move
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(UPrimitiveComponent* InOverlappedComponent ,ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InOverlappedComponent, InAttacker, InCauser, InOtherCharacter);

	//다단히트 체크 / Register HittedCharacters Array for Multiple Hit
	int32 prevHittedCharactersNum = HittedCharacters.Num();
	HittedCharacters.AddUnique(InOtherCharacter);

	CheckFalse(prevHittedCharactersNum < HittedCharacters.Num());
	
	FDamageEvent damageEvent;
	InOtherCharacter->TakeDamage(Datas[ComboCount].Power, damageEvent, InAttacker->GetController(), InCauser);
	

	// HitStop
	float hitStop = Datas[ComboCount].HitStop;
	if (FMath::IsNearlyZero(hitStop)==false && UGameplayStatics::GetGlobalTimeDilation(GetWorld()) >= 1.f)    // FMath:: IsNearlyZero(hitStop)  hitstop이 0이 아닌 값이라면 . 
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 2e-2f); 
		UKismetSystemLibrary::K2_SetTimer(this, "ResetGlobalTimeDilation", hitStop * 2e-2f, false);
	}

	//Spawn Particle
	UParticleSystem* effect = Datas[ComboCount].Effect;
	if (!!effect)
	{
		FTransform trasnform = Datas[ComboCount].EffcetTransform;
		

		trasnform.AddToTranslation(InOverlappedComponent->GetComponentLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), effect, trasnform);
	}

	//CameraShake
	TSubclassOf<UCameraShake> shakeClass = Datas[ComboCount].ShakeClass;
	if (!!shakeClass)
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (!!controller)
			controller->PlayerCameraManager->PlayCameraShake(shakeClass);
	}

	
}

void ACDoAction_Melee::OnAttachmentEndOverlap(UPrimitiveComponent* InOverlappedComponent,ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InOverlappedComponent,InAttacker, InCauser, InOtherCharacter);
}

void ACDoAction_Melee::ResetGlobalTimeDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
}

