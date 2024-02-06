#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHealthWidget.generated.h"

UCLASS()
class THIRDPERSONCPP_API UCHealthWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:
	UFUNCTION(BlueprintNativeEvent)
		void UpdateHP(float InCurrentHealth, float MaxHealth);
	void UpdateHP_Implementation(float InCurrentHealth, float MaxHealth);
private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;
};
