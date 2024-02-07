#include "CMontagesComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"


UCMontagesComponent::UCMontagesComponent()
{

}


void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr)
	{
		CLog::Log("DataTable is not set!!");
		return;
	}

	TArray <FMontageData*> datas;

	DataTable->GetAllRows<FMontageData>("", datas);

	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for ( FMontageData* data : datas)
		{
			
			if (data->Type == (EStateType)i)
			{
				Datas[i] = data;
				break;
			}

		}

	}
	
}

void UCMontagesComponent::PlayRoll()
{
	PlayAimMontage(EStateType::Roll);
}

void UCMontagesComponent::PlayBackstep()
{
	PlayAimMontage(EStateType::Backstep);

}

void UCMontagesComponent::PlayHitted()
{
	PlayAimMontage(EStateType::Hitted);
}

void UCMontagesComponent::PlayAimMontage(EStateType InStateType)
{
	ACharacter* ownerCharacter= Cast<ACharacter>(GetOwner());
	CheckNull(ownerCharacter);

	FMontageData* data = Datas[(int32)InStateType];

	if (!!data && !!data->AnimMotage)
	{
		ownerCharacter->PlayAnimMontage(data->AnimMotage,data->PlayRate,data->StartSection);
	}
}



