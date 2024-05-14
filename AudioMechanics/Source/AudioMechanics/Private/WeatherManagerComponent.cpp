// Copyright Jack Wright. All Rights Reserved.


#include "WeatherManagerComponent.h"
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

	if (WeatherBudgetUsed > MaximumWeatherBudget)
	{
		WeatherBudgetUsed = MaximumWeatherBudget;
	}
	
	for (TTuple<UWeatherState*, float>& State : WeatherStates)
	{
		if (const bool bChangeThisFrame = FMath::RandBool(); !bChangeThisFrame)
		{
			continue;
		}

		const bool bIncreaseThisFrame =
			WeatherBudgetUsed < MaximumWeatherBudget && FMath::RandBool();
		const float DeltaState = bIncreaseThisFrame ? DeltaTime : State.Value - DeltaTime >= 0 ? -DeltaTime : 0;
		WeatherBudgetUsed += DeltaState;
		State.Value += DeltaState;
	}

	DebugPrint();
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

