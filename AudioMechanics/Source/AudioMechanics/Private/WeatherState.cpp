// Copyright Jack Wright. All Rights Reserved.


#include "WeatherState.h"

FString UWeatherState::GetName()
{
	return Name;
}

float UWeatherState::GetState() const
{
	return FMath::Clamp(State, 0.0f, 1.0f);
}

void UWeatherState::SetName(FString NewName)
{
	Name = NewName;
}

void UWeatherState::SetState(const float NewState)
{
	State = FMath::Clamp(NewState, 0.0f, 1.0f);
}

void UWeatherState::IncrementState(const float Increment)
{
	State = FMath::Clamp(State + Increment, 0.0f, 1.0f);;
}



