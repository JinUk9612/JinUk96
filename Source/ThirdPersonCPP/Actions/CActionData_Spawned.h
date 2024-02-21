#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CActionData_Spawned.generated.h"


//=============================================================================
// Equipment(Struct)
//=============================================================================
USTRUCT(BlueprintType)
struct FEquipementData
{
	GENERATED_BODY()



public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bLookForward = true;
};

//=============================================================================
// DoAction(Struct)
//=============================================================================


USTRUCT(BlueprintType)
struct FDoActionData : public FEquipementData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Power = 1.f;

	UPROPERTY(EditAnywhere)
		float HitStop;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Effect;

	UPROPERTY(EditAnywhere)
		FTransform EffcetTransform;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> ShakeClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACMagicBall> ProjectileClass;
};


//=============================================================================
// DataAsset_Spawned(Class)
//=============================================================================


UCLASS()
class THIRDPERSONCPP_API UCActionData_Spawned : public UObject
{
	GENERATED_BODY()


public:
	friend class UCActionData;
	
public:

	FORCEINLINE class ACEuipment* GetEquipment() { return Equipment; }
	FORCEINLINE class ACAttachment* GetAttachMent() { return Attachment; }
	FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE FLinearColor GetEquipmentColor() { return EquipmentColor; }

private:
	class ACEuipment* Equipment;
	class ACAttachment* Attachment;
	class ACDoAction* DoAction;
	FLinearColor EquipmentColor;

};
