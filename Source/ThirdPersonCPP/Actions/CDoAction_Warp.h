#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Warp.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACDoAction_Warp : public ACDoAction
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void DoAction() override;
	virtual void Begin_Action() override;
	virtual void End_Action() override;

private:
	bool GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotation);
	bool IsPlayerControlled();

private:
	class UStaticMeshComponent* Preview;
	FVector Location;
};
