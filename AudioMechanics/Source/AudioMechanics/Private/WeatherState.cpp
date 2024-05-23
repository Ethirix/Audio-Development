// Copyright Jack Wright. All Rights Reserved.


#include "WeatherState.h"

FString UWeatherState::GetName()
{
	return Name;
}

float UWeatherState::GetMinimumState() const
{
	return MinimumState;
}

float UWeatherState::GetLinearVolumeLevel(float State) const
{
	return State;
	
	float CurrentLevel = State - MinimumState;
	float Multiplier = 1.0f / (1.0f - MinimumState);

	return FMath::Clamp(CurrentLevel * Multiplier, 0.0f, 1.0f);
}

USoundBase* UWeatherState::GetSound() const
{
	return Sound;
}