// Copyright Jack Wright. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BillboardComponent.h"
#include "GameFramework/Actor.h"
#include "WeatherManager.generated.h"

UCLASS()
class AUDIOMECHANICS_API AWeatherManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeatherManager();

	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

private:
};
