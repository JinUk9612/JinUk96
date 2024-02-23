#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_DoAciton.generated.h"

UCLASS()
class THIRDPERSONCPP_API UCBTTaskNode_DoAciton : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskNode_DoAciton();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
		float Delay = 2.f;

private:
	float RunningTime;

};
