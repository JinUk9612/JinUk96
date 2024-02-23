#include "CBTTaskNode_Speed.h"
#include "Global.h"
#include "Characters/CAIController.h"


UCBTTaskNode_Speed::UCBTTaskNode_Speed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UCBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	UCStatusComponent* stateComp = CHelpers::GetComponent<UCStatusComponent>(controller->GetPawn());
	CheckNullResult(stateComp,EBTNodeResult::Failed);

	stateComp->SetSpeed(Type);

	return EBTNodeResult::Succeeded;
}
