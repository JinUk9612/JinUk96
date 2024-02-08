#include "CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionData.h"
#include "Actions/CAttachment.h"
#include "Actions/CDoAction_Melee.h"


FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);
	UCActionData* actionData = actionComp->GetCurrentData();
	CheckNull(actionData);
	ACAttachment* attachment = actionData->GetAttachMent();
	CheckNull(attachment);

	attachment->OnCollision();

}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UCActionData* actionData = actionComp->GetCurrentData();
	CheckNull(actionData);

	ACAttachment* attachment = actionData->GetAttachMent();
	CheckNull(attachment);

	attachment->OffCollision();
	
	ACDoAction_Melee* doAction_melee = Cast<ACDoAction_Melee>(actionData->GetDoAction());
	CheckNull(doAction_melee);

	doAction_melee->ClearHittedCharacter();

}