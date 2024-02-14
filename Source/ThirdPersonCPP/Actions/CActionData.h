#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"



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
// DataAsset(Class)
//=============================================================================


UCLASS()
class THIRDPERSONCPP_API UCActionData : public UDataAsset
{
	GENERATED_BODY()


public:
	void BeginPlay(class ACharacter* InOwnerCharacter);

	FORCEINLINE class ACEuipment* GetEquipment() { return Equipment; }

	FORCEINLINE class ACAttachment* GetAttachMent() { return Attachment; }


	FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }


private:
	FString MakeLabelName(class ACharacter* InOwnerCharacter, FString InMiddleName);


public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Equipment")
		TSubclassOf<class ACEuipment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Equipment")
		FEquipementData EquipmentData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Equipment")
		FLinearColor EquipmentColor;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attachment")
		TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DoAction")
		TSubclassOf<class ACDoAction> DoActionClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DoAction")
		TArray<FDoActionData> DoActionDatas;
	

private:
	class ACEuipment* Equipment;
	class ACAttachment* Attachment;
	class ACDoAction* DoAction;

};
