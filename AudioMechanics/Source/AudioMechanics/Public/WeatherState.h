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

	UPROPERTY(EditInstanceOnly)
	FString Name;

	UPROPERTY(EditInstanceOnly, meta=(ClampMin = 0, ClampMax = 1))
	float MinimumState = 0;
	
	UPROPERTY(EditInstanceOnly)
	TObjectPtr<UMetaSoundSource> SoundFilter;
	
public:

	UFUNCTION(BlueprintCallable)
	FString GetName();

	UFUNCTION(BlueprintCallable)
	float GetMinimumState() const;
	
	UFUNCTION(BlueprintCallable)
	UMetaSoundSource* GetSoundFilter() const;
};
