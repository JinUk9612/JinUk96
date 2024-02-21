#include "CActionData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CEuipment.h"
#include "CAttachment.h"
#include "CDoAction.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter, UCActionData_Spawned** OutSpawned)
{
	FTransform transform;

	ACAttachment* Attachment = nullptr;

	if (!!AttachmentClass)
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOwnerCharacter);
		Attachment->SetActorLabel(MakeLabelName(InOwnerCharacter, "Attachment"));
		UGameplayStatics::FinishSpawningActor(Attachment, transform);
	}


	ACEuipment* Equipment = nullptr;
	if (!!EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEuipment>(EquipmentClass, transform, InOwnerCharacter);
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		Equipment->SetActorLabel(MakeLabelName(InOwnerCharacter, "Equipment"));

		UGameplayStatics::FinishSpawningActor(Equipment, transform);

		if (!!Attachment)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
			Equipment->OnUnequipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnequip);
		}
	}

	ACDoAction* DoAction = nullptr;
	if (!!DoActionClass)
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, transform, InOwnerCharacter);
		DoAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		DoAction->SetActorLabel(MakeLabelName(InOwnerCharacter, "DoAction"));
		DoAction->SetDatas(DoActionDatas);
		UGameplayStatics::FinishSpawningActor(DoAction, transform);

		if (!!Attachment)
		{
			Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentEndOverlap);
		}
		if (!!Equipment)
		{
			DoAction->SetEquippedThis(Equipment->IsEquippedThis());
		}

	}

	*OutSpawned = NewObject<UCActionData_Spawned>();
	(*OutSpawned)->Attachment = Attachment;
	(*OutSpawned)->Equipment = Equipment;
	(*OutSpawned)->DoAction = DoAction;
}

FString UCActionData::MakeLabelName(ACharacter* InOwnerCharacter, FString InMiddleName)
{
	FString name;
	name.Append(InOwnerCharacter->GetActorLabel());
	name.Append("_");
	name.Append(InMiddleName);
	name.Append("_");
	name.Append(GetName().Replace(L"DA_", L""));

	return name;
}
