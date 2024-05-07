// Copyright Jack Wright. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeatherManagerComponent.generated.h"


class UWeatherState;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUDIOMECHANICS_API UWeatherManagerComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UWeatherState>> WeatherStates;

	UPROPERTY(EditAnywhere)
	int BaseWeatherState = 0;
	
	UPROPERTY(EditAnywhere)
	float MaximumWeatherBudget = 1.0f;
public:	
	UWeatherManagerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	TArray<UWeatherState*>& GetStates();
	
	UFUNCTION(BlueprintCallable)
	void AddState(UWeatherState* State);

protected:
	virtual void BeginPlay() override;
};
