#include "CDoor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

//#define VisibleDrawDebug

ACDoor::ACDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Box, "Box", Root);
	CHelpers::CreateSceneComponent(this, &DoorFrame, "DoorFrame",Root);
	CHelpers::CreateSceneComponent(this, &Door, "Door", DoorFrame);


	UStaticMesh* doorFrameMeshAsset, *doorMeshAsset;
	CHelpers::GetAsset<UStaticMesh>(&doorFrameMeshAsset, "StaticMesh'/Game/DoorMesh/Props/SM_DoorFrame.SM_DoorFrame'");
	CHelpers::GetAsset<UStaticMesh>(&doorMeshAsset, "StaticMesh'/Game/DoorMesh/Props/SM_Door.SM_Door'");

	DoorFrame->SetStaticMesh(doorFrameMeshAsset);
	Door->SetStaticMesh(doorMeshAsset);
	Door->SetRelativeLocation(FVector(0, 45, 0));

	Box->SetCollisionProfileName("Interact");
	Box->SetRelativeLocation(FVector(0, 0, 100));
	Box->SetBoxExtent(FVector(25, 60, 100));
	Box->bHiddenInGame = false;

}

void ACDoor::BeginPlay()
{
	Super::BeginPlay();

#ifdef VisibleDrawDebug
	DrawDebugDirectionalArrow
	(
		GetWorld(),
		GetActorLocation() + FVector(0, 0, 100),
		GetActorLocation() + FVector(0, 0, 100) + GetActorForwardVector() * 100.f,
		20,
		FColor::Red,
		true,
		-1,
		0,
		10
	);
#endif
}

void ACDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator currentRotation = Door->GetRelativeRotation();
	CLog::Print(currentRotation, 1);

	if (bOpen)
	{
		Door->SetRelativeRotation(FMath::Lerp(currentRotation, FRotator(0,MaxYawWithDirection,0), ConstantRatio));

		return;
	}
	else
	{
		Door->SetRelativeRotation(FMath::Lerp(currentRotation, FRotator(0, 0, 0), ConstantRatio));
	}

}


void ACDoor::Interact(ACharacter* InCharacter)
{
	FVector doorFoward = GetActorForwardVector();
	FVector characterForward = InCharacter->GetActorForwardVector();

	float bDirection = FMath::Sign(doorFoward | characterForward); // Sign 은 음수면 -1 로 양수면 +1로 만들어버린다 . 0.25 도 1 -0.25 는 -1로 바꾼다.

	MaxYawWithDirection = bDirection * MaxYaw;

	bOpen = !bOpen;
}
