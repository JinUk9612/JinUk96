#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActionData.h"
#include "CEuipment.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentDelegateSignatrue);

UCLASS()
class THIRDPERSONCPP_API ACEuipment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEuipment();

public:
	UFUNCTION(BlueprintNativeEvent)
		void Equip();
	void Equip_Implementation();    // Implementation 을 안만들면 c++ 언어를 벗어나서 인텔리센스가 안먹는다 이렇게 작성하면 인텔리센스가 먹는다.

	UFUNCTION(BlueprintNativeEvent)
		void Begin_Equip();
	void Begin_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void End_Equip();
	void End_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void UnEquip();
	void UnEquip_Implementation();

public:
	UPROPERTY(BlueprintAssignable)
		FEquipmentDelegateSignatrue OnEquipmentDelegate;

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE void SetData(const FEquipementData& InData) { Data = InData; }
	FORCEINLINE void SetColor(const FLinearColor& InColor) { Color = InColor; }

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* StateComp;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* StatusComp;


private:
	 FEquipementData Data;
	 FLinearColor Color;
};
