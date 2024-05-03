// Copyright Jack Wright. All Rights Reserved.


#include "WeatherManagerComponent.h"

UWeatherManagerComponent::UWeatherManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeatherManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeatherManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

TArray<UWeatherState*>& UWeatherManagerComponent::GetStates()
{
	return WeatherStates;
}

void UWeatherManagerComponent::AddState(UWeatherState* State)
{
	WeatherStates.Add(State);
}
