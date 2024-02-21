#include "CAIController.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CEnemy_AI.h"
#include "BehaviorTree/BehaviorTree.h"

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent(this, &Blackboard, "Blackboard");
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerEnemy = Cast<ACEnemy_AI>(InPawn);
	UseBlackboard(OwnerEnemy->GetBehaviorTree()->BlackboardAsset, Blackboard);
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
