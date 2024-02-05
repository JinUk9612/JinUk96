#include "CEuipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Characters/ICharacter.h"

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
	//Set State Equip
	StateComp->SetEquipMode();

	Data.bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();

	//Play Equip Montage
	if (!!Data.AnimMontage)
	{
		OwnerCharacter->PlayAnimMontage(Data.AnimMontage, Data.PlayRate, Data.StartSection);
	}
	else
	{
		Begin_Equip();
		End_Equip();
	}
	//Look Forward
	if (Data.bLookForward == true)
	{
		OwnerCharacter->bUseControllerRotationYaw = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	//Set Equipment Color
	IICharacter* characterInterface = Cast<IICharacter>(OwnerCharacter);
	CheckNull(characterInterface);
	characterInterface->SetBodyColor(Color);

	
}

void ACEuipment::Begin_Equip_Implementation()
{
	if (OnEquipmentDelegate.IsBound())
		OnEquipmentDelegate.Broadcast();
}

void ACEuipment::End_Equip_Implementation()
{
	StateComp->SetIdleMode();

	StatusComp->SetMove();
}

void ACEuipment::UnEquip_Implementation()
{

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;

	if (OnUnequipmentDelegate.IsBound())
		OnUnequipmentDelegate.Broadcast();
}
