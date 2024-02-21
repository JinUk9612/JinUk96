#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData_Spawned.h"
#include "CActionData.generated.h"

UCLASS()
class THIRDPERSONCPP_API UCActionData : public UDataAsset
{
	GENERATED_BODY()


public:
	void BeginPlay(class ACharacter* InOwnerCharacter ,class UCActionData_Spawned** OutSpawned);

	FORCEINLINE  FEquipementData GetEquipmentData() { return EquipmentData; }

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
	



};
