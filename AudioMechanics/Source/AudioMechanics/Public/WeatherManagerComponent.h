// Copyright Jack Wright. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeatherManagerComponent.generated.h"


struct FActiveSoundStruct;
class UWeatherState;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUDIOMECHANICS_API UWeatherManagerComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UWeatherManagerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	TMap<UWeatherState*, float>& GetStates();
	
	UFUNCTION(BlueprintCallable)
	void AddState(UWeatherState* State);

	UFUNCTION(BlueprintCallable)
	TArray<FActiveSoundStruct> GetActiveSounds();

protected:
	virtual void BeginPlay() override;

private:
	void DebugPrint();

	void UpdateBudget();

	void UpdateStates(float DeltaTime);
	
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UWeatherState>> Weathers;
	
	UPROPERTY(EditAnywhere)
	float MaximumWeatherBudget = 1.0f;

	UPROPERTY(VisibleInstanceOnly)
	float WeatherBudgetUsed = 0.0f;

	UPROPERTY(VisibleInstanceOnly)
	TMap<UWeatherState*, float> WeatherStates;
};
