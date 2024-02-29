#include "CBTService_Melee.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CPlayer.h"
#include "Characters/CEnemy_AI.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CPatrolComponent.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "Root_Melee";
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//GetComponents
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(controller);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	ACEnemy_AI* enemy = Cast<ACEnemy_AI>(controller->GetPawn());
	CheckNull(enemy);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(enemy);
	CheckNull(stateComp);

	UCPatrolComponent* patrolComp = CHelpers::GetComponent<UCPatrolComponent>(enemy);
	CheckNull(patrolComp);

	//Check Dead
	if (stateComp->IsDeadMode())
	{
		behaviorComp->SetWaitMode();
		return;
	}


	//Set Behavior Hitted
	if (stateComp->IsHittedMode())
	{
		behaviorComp->SetHittedMode();
		return;
	}

	//Try to Get Target Player  //플레이어를 감지하고 플레이어 키값에 넣기위한 함수
	ACPlayer* player = behaviorComp->GetPlayerKey();

	//No Perceived Player    감지가 되지 않은 경우
	if (player == nullptr)
	{

		controller->ClearFocus(EAIFocusPriority::LastFocusPriority); // 플레이어를 바라보다 플레이어의 감지가 없어지면 클리어 포커스로 마지막에 바라봤던 위치를 고정시키는 함수 

		if (patrolComp != nullptr && patrolComp->IsPathValid())
		{
			behaviorComp->SetPatrolMode();
			return;

		}

		behaviorComp->SetWaitMode();
		return;
	}

	//Perceived Player 감지가 된 경우 
	controller->SetFocus(player); // 플레이어를 계속 바라보게 하는 함수 
	float distance = enemy->GetDistanceTo(player);


	//InBehaviorRange 공격 범위 안에 들어왔을경우
	if (distance < controller->GetBehaviorRange())
	{
		behaviorComp->SetActionMode();
		return;
	}

	//InSight 시야범위 안에 들어왔을 경우 
	if (distance < controller->GetSightRadius())
	{
		behaviorComp->SetApproachMode();
		return;
	}



}