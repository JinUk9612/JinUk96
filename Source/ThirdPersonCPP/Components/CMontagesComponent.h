#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CStateComponent.h"
#include "CMontagesComponent.generated.h"
//===================================================================================================
//=================================Struct Table Row Based ===========================================
//===================================================================================================

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()   // �⺻ C++ ������ public ���� �Ǿ������� Generated body �� �ִ°�� �ݴ밡 �ȴ�.

public:
	UPROPERTY(EditAnywhere)
		EStateType Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMotage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove;

	//���漱�� ���� 
	//class, struct �Ǵ� ������

};
//===================================================================================================
//==================================Class MontageComponent===========================================
//===================================================================================================

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONCPP_API UCMontagesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMontagesComponent();

protected:
	virtual void BeginPlay() override;

public:
	void PlayRoll();
	void PlayBackstep();
	void PlayHitted();



private:
	void PlayAimMontage(EStateType InStateType);

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;

private:
	FMontageData* Datas[(int32)EStateType::Max];
		
};
