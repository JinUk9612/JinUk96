#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Fist, OneHand, TwoHand,Warp,MagicBall,Tornado,Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChangedSignature, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONCPP_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
		bool IsUnarmedMode() { return Type == EActionType::Unarmed; }

	UFUNCTION(BlueprintPure)
		bool IsFistMode() { return Type == EActionType::Fist; }

	UFUNCTION(BlueprintPure)
		bool IsOneHandMode() { return Type == EActionType::OneHand; }

	UFUNCTION(BlueprintPure)
		bool IsTwoHandMode() { return Type == EActionType::TwoHand; }

	UFUNCTION(BlueprintPure)
		bool IsWarpMode() { return Type == EActionType::Warp; }

	UFUNCTION(BlueprintPure)
		bool IsMagicBallMode() { return Type == EActionType::MagicBall; }

	UFUNCTION(BlueprintPure)
		bool IsTornadoMode() { return Type == EActionType::Tornado; }


public:
	void SetUnarmedMode();
	void SetFistMode();
	void SetOneHandMode();
	void SetTwoHandMode();
	void SetWarpMode();
	void SetMagicBallMode();
	void SetTornadoMode();

private:
	void SetMode(EActionType InType);
	void ChangeType(EActionType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChangedSignature OnActionTypeChanged;

private:
	EActionType Type;
		
};
