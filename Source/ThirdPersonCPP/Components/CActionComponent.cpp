#include "CActionComponent.h"

UCActionComponent::UCActionComponent()
{

}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCActionComponent::SetUnarmedMode()
{
	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);

}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);

}

void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);

}

void UCActionComponent::SetMagicBallMode()
{
	SetMode(EActionType::MagicBall);

}

void UCActionComponent::SetTornadoMode()
{
	SetMode(EActionType::Tornado);

}

void UCActionComponent::SetMode(EActionType InType)
{
	if (Type == InType)
	{
		SetUnarmedMode();
		return;
	}
	
	ChangeType(InType);
}

void UCActionComponent::ChangeType(EActionType InNewType)
{

	EActionType prev = Type;
	Type = InNewType;


	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prev, InNewType);
}
