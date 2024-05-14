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

UMetaSoundSource* UWeatherState::GetSoundFilter() const
{
	return SoundFilter;
}