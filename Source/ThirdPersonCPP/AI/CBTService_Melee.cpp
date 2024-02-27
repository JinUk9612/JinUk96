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

	//Try to Get Target Player  //�÷��̾ �����ϰ� �÷��̾� Ű���� �ֱ����� �Լ�
	ACPlayer* player = behaviorComp->GetPlayerKey();

	//No Perceived Player    ������ ���� ���� ���
	if (player == nullptr)
	{

		if (patrolComp != nullptr && patrolComp->IsPathValid())
		{
			behaviorComp->SetPatrolMode();
			return;

		}

		behaviorComp->SetWaitMode();
		return;
	}

	//Perceived Player ������ �� ��� 
	float distance = enemy->GetDistanceTo(player);


	//InBehaviorRange ���� ���� �ȿ� ���������
	if (distance < controller->GetBehaviorRange())
	{
		behaviorComp->SetActionMode();
		return;
	}

	//InSight �þ߹��� �ȿ� ������ ��� 
	if (distance < controller->GetSightRadius())
	{
		behaviorComp->SetApproachMode();
		return;
	}



}