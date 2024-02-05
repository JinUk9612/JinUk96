

#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Melee.generated.h"


UCLASS()
class THIRDPERSONCPP_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()
public:
	virtual void DoAction() override;
	virtual void Begin_Action() override;
	virtual void End_Action() override;
	
};