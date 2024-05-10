// Copyright Jack Wright. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MetasoundSource.h"
#include "Engine/DataAsset.h"
#include "WeatherState.generated.h"


UCLASS()
class AUDIOMECHANICS_API UWeatherState : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY()
	float State = 0;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMetaSoundSource> SoundFilter;
	
public:

	UFUNCTION(BlueprintCallable)
	FString GetName();

	UFUNCTION(BlueprintCallable)
	float GetState() const;

	UFUNCTION(BlueprintCallable)
	UMetaSoundSource* GetSoundFilter() const;

	UFUNCTION(BlueprintCallable)
	void SetState(float NewState);

	UFUNCTION(BlueprintCallable)
	void IncrementState(float Increment);
};
