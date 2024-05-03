// Copyright Jack Wright. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherManager.generated.h"

class UWeatherManagerComponent;

UCLASS()
class AUDIOMECHANICS_API AWeatherManager : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWeatherManagerComponent> WeatherManagerComponent;

public:	
	AWeatherManager();

protected:
	virtual void BeginPlay() override;
};
