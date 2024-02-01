#include "CEuipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

ACEuipment::ACEuipment()
{

}

void ACEuipment::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	StateComp = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	StatusComp = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
}

void ACEuipment::Equip_Implementation()
{

	StateComp->SetEquipMode();


	if (!!Data.AnimMontage)
	{
		OwnerCharacter->PlayAnimMontage(Data.AnimMontage, Data.PlayRate, Data.StartSection);
	}
	else
	{
		Begin_Equip();
		End_Equip();
	}

}

void ACEuipment::Begin_Equip_Implementation()
{
	if (OnEquipmentDelegate.IsBound())
		OnEquipmentDelegate.Broadcast();
}

void ACEuipment::End_Equip_Implementation()
{
	StateComp->SetIdleMode();
}

void ACEuipment::UnEquip_Implementation()
{
}

