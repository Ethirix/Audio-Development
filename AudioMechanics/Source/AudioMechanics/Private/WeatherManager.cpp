// Copyright Jack Wright. All Rights Reserved.


#include "WeatherManager.h"

#include "WeatherManagerComponent.h"


AWeatherManager::AWeatherManager()
{
	WeatherManagerComponent = CreateDefaultSubobject<UWeatherManagerComponent>(TEXT("Weather Manager Component"));
	WeatherManagerComponent->RegisterComponent();
}

void AWeatherManager::BeginPlay()
{
	Super::BeginPlay();
}