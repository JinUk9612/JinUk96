#include "CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	Super::BeginPlay(); //Super콜은 블루프린트에서 비긴 플레이 까지 호출한다 . 즉 오너캐릭터를 먼저 캐스팅 해서 받아야 블루프린트에서 오너캐릭터가 인식된다.
}

void ACAttachment::AttachTo(FName InSocketName)
{
	CheckNull(OwnerCharacter);
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}



