#include "CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	GetComponents<UShapeComponent>(Collisions);
	for (UShapeComponent* collsion : Collisions)
	{
		collsion->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);
		collsion->OnComponentEndOverlap.AddDynamic(this, &ACAttachment::OnComponentEndOverlap);
	}

	OffCollision();

	Super::BeginPlay(); //Super콜은 블루프린트에서 비긴 플레이 까지 호출한다 . 즉 오너캐릭터를 먼저 캐스팅 해서 받아야 블루프린트에서 오너캐릭터가 인식된다.
}

void ACAttachment::AttachTo(FName InSocketName)
{
	CheckNull(OwnerCharacter);
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::AttachToScene(USceneComponent* InComponent, FName InSocketName)
{
	CheckNull(OwnerCharacter);
	InComponent->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::OnCollision()
{
	for (UShapeComponent* collisions : Collisions)
	{
		collisions->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ACAttachment::OffCollision()
{
	for (UShapeComponent* collisions : Collisions)
	{
		collisions->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor == OwnerCharacter);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());

	if (OnAttachmentBeginOverlap.IsBound())
	{
		ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);

		if(!!otherCharacter)
			OnAttachmentBeginOverlap.Broadcast(OverlappedComponent,OwnerCharacter, this, otherCharacter);
	}
}

void ACAttachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OnAttachmentEndOverlap.IsBound())
	{
		ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);


		OnAttachmentEndOverlap.Broadcast(OverlappedComponent,OwnerCharacter, this, otherCharacter);
	}
}



