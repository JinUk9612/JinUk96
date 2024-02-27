#include "CPatrolComponent.h"
#include "Global.h"
#include "Components/SplineComponent.h"
#include "AI/CPatrolPath.h"

UCPatrolComponent::UCPatrolComponent()
{

}


bool UCPatrolComponent::GetMoveTo(FVector& OutLocation,float& OutAcceptanceRadius)
{
	OutLocation = GetOwner()->GetActorLocation();
	OutAcceptanceRadius = AcceptancRadius;
	CheckNullResult(Path, false);


	OutLocation = Path->GetSplineComp()->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
	return true;
}

void UCPatrolComponent::UpdateNextIndex()
{
	CheckNull(Path);

	int32 count = Path->GetSplineComp()->GetNumberOfSplinePoints(); //Spline �������� �ε��� �ѹ� �� �� �������� �Լ� 

	//Reverse
	if (bReverse)
	{
		if (Index > 0)
		{
			Index--;
			return;
		}

		if (Path->GetSplineComp()->IsClosedLoop())
		{
			Index = count - 1;
			return;
		}

		Index = 1;
		bReverse = false;

		return;
	}

	//Forward
	if (Index < count - 1)
	{
		Index++;
		return;
	}

	if (Path->GetSplineComp()->IsClosedLoop())
	{
		Index = 0;
		return;
	}
	
	Index = count - 2;
	bReverse = true;

}

void UCPatrolComponent::BeginPlay()
{
	Super::BeginPlay();


}
