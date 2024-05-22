// Copyright Jack Wright. All Rights Reserved.


#include "WeatherManagerComponent.h"

#include "ActiveSoundStruct.h"
#include "WeatherState.h"

UWeatherManagerComponent::UWeatherManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeatherManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	for (UWeatherState* State : Weathers)
	{
		WeatherStates.Add(State);
	}
}

void UWeatherManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UpdateStates(DeltaTime);

	DebugPrint();
}

void UWeatherManagerComponent::UpdateStates(float DeltaTime)
{
	for (TTuple<UWeatherState*, float>& State : WeatherStates)
	{
		UpdateBudget();

		int StateChange = FMath::RandRange(-1, 1);
		if (WeatherBudgetUsed >= MaximumWeatherBudget || State.Value >= 1)
		{
			StateChange = -1;
		}

		switch (StateChange)
		{
		case -1:
			State.Value -= DeltaTime;
			if (State.Value < 0)
			{
				State.Value = 0;
			}
			break;
		case 1:
			if (WeatherBudgetUsed + DeltaTime > MaximumWeatherBudget)
			{
				break;
			}
			
			State.Value += DeltaTime;
			if (State.Value > 1)
			{
				State.Value = 1;
			}
			break;
		default:
			break;
		}
	}
}

void UWeatherManagerComponent::UpdateBudget()
{
	WeatherBudgetUsed = 0;
	for (TTuple<UWeatherState*, float> State : WeatherStates)
	{
		WeatherBudgetUsed += State.Value;
	}
}

TArray<FActiveSoundStruct> UWeatherManagerComponent::GetActiveSounds()
{
	TArray<FActiveSoundStruct> Sounds;
	for (TTuple<UWeatherState*, float> State : WeatherStates)
	{
		if (State.Key->GetMinimumState() <= State.Value)
		{
			Sounds.Emplace(State.Key->GetSound(), State.Key->GetLinearVolumeLevel(State.Value));
		}
	}

	return Sounds;
}

TMap<UWeatherState*, float>& UWeatherManagerComponent::GetStates()
{
	return WeatherStates;
}

void UWeatherManagerComponent::AddState(UWeatherState* State)
{
	WeatherStates.Add(State);
}

void UWeatherManagerComponent::DebugPrint()
{
#if UE_BUILD_DEBUG | UE_BUILD_DEVELOPMENT
	for (const TTuple<UWeatherState*, float>& State : WeatherStates)
	{
		if (GEngine)
		{
			const int32 Id = State.Key->GetUniqueID();
			GEngine->AddOnScreenDebugMessage(Id,1.0f, FColor::White,
				FString::Printf(TEXT("%s: %f - %s"),
					*State.Key->GetName(),
					State.Value,
					State.Value > State.Key->GetMinimumState() ? TEXT("TRUE") : TEXT("FALSE")));
		}
	}
#endif
}