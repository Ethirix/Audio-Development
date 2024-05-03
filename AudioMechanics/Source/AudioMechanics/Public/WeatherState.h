// Copyright Jack Wright. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WeatherState.generated.h"


UCLASS(BlueprintType, hidecategories=(Object))
class AUDIOMECHANICS_API UWeatherState : public UObject
{
	GENERATED_BODY()

	//The Name in which the State is referred to.
	//Keep to a unique name like WS_SNOW
	UPROPERTY(EditAnywhere)
	FString Name;

	//The activeness of the State - clamped between 0 and 1.
	UPROPERTY()
	float State;
public:
	UFUNCTION(BlueprintCallable)
	FString GetName();

	UFUNCTION(BlueprintCallable)
	float GetState() const;

	
	UFUNCTION(BlueprintCallable)
	void SetName(FString NewName);

	UFUNCTION(BlueprintCallable)
	void SetState(float NewState);

	UFUNCTION(BlueprintCallable)
	void IncrementState(float Increment);
};
