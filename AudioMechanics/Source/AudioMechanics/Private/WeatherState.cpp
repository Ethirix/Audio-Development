// Copyright Jack Wright. All Rights Reserved.


#include "WeatherState.h"

FString UWeatherState::GetName()
{
	return Name;
}

float UWeatherState::GetState() const
{
	return State;
}

UMetaSoundSource* UWeatherState::GetSoundFilter() const
{
	return SoundFilter;
}

void UWeatherState::SetState(float NewState)
{
	State = FMath::Clamp(NewState, 0.0f, 1.0f);
}

void UWeatherState::IncrementState(float Increment)
{
	State = FMath::Clamp(State + Increment, 0.0f, 1.0f);
}